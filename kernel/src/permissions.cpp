#include "../include/types.h"
#include "../include/permissions.h"
#include <cstdint>
#include <expected>
#include <mutex>
#include <shared_mutex>

PermissionLevel PermissionStore::getBits(ProcessPermissions& permissions, Permission permission){
	uint_fast64_t map = permission >= Permission::COLD_START ? permissions.coldMap : permissions.hotMap;
	
	//Offset index if the permission is cold
	uint8_t index = static_cast<int>(permission);
	if (permission >= Permission::COLD_START)
		index -= static_cast<int>(Permission::COLD_START);

	uint64_t permissionBits = map >> (3 * index);
	//Remove extra bits
	return static_cast<PermissionLevel>(permissionBits & 0b111);
}

void PermissionStore::setBits(ProcessPermissions& permissions, Permission permission, PermissionLevel level){
	uint_fast64_t map = permission >= Permission::COLD_START ? permissions.coldMap : permissions.hotMap;
	
	//Offset index if the permission is cold
	uint8_t index = static_cast<int>(permission);
	if (permission >= Permission::COLD_START)
		index -= static_cast<int>(Permission::COLD_START);

	map &= ~(static_cast<uint_fast64_t>(0b111) << (index * 3));
	map |= static_cast<uint_fast64_t>(level) << (index * 3);
	
	if (permission >= Permission::COLD_START)
		permissions.coldMap = map;
	else
		permissions.hotMap = map;
}

std::expected<void, KernelError> PermissionStore::grant(ProcessId pid, Permission permission, PermissionLevel level){
	std::unique_lock<std::shared_mutex> lock(processMutex);
	auto it = processPermissions.find(pid);
	if (it == processPermissions.end())
		return std::unexpected(KernelError::PROCESS_NOT_FOUND);
	setBits(it->second, permission, level);
	return {};
}

std::expected<void, KernelError> PermissionStore::revoke(ProcessId pid, Permission permission){
	return grant(pid, permission, PermissionLevel::DENIED);
}

std::expected<PermissionLevel, KernelError> PermissionStore::check(ProcessId pid, Permission permission){
	std::shared_lock<std::shared_mutex> lock(processMutex);
	auto it = processPermissions.find(pid);
	if (it == processPermissions.end())
		return std::unexpected(KernelError::PROCESS_NOT_FOUND);
	if (isKilledGloballyInternal(permission))
		return PermissionLevel::DENIED;
	return getBits(it->second, permission);
}


std::expected<bool, KernelError> PermissionStore::hasMinimumLevel(ProcessId pid, Permission permission, PermissionLevel level){
	std::shared_lock<std::shared_mutex> lock(processMutex);
	auto it = processPermissions.find(pid);
	if (it == processPermissions.end())
		return std::unexpected(KernelError::PROCESS_NOT_FOUND);
	return getBits(it->second, permission) >= level;
}

void PermissionStore::setKillSwitch(Permission permission, bool shouldKill){
	std::unique_lock<std::shared_mutex> lock(processMutex);
	if (shouldKill)
		killSwitch |= (static_cast<uint_fast64_t>(1) << static_cast<uint_fast64_t>(permission));
	else
	 	killSwitch &= ~(static_cast<uint_fast64_t>(1) << static_cast<uint_fast64_t>(permission));
}

bool PermissionStore::isKilledGloballyInternal(Permission permission){
	return killSwitch & (static_cast<uint_fast64_t>(1) << static_cast<uint_fast64_t>(permission));		
}

bool PermissionStore::isKilledGlobally(Permission permission){
	std::shared_lock<std::shared_mutex> lock(processMutex);
	return isKilledGloballyInternal(permission);
}

std::expected<ProcessId, KernelError> PermissionStore::registerProcess(){
	std::unique_lock<std::shared_mutex> lock(processMutex);
	ProcessId newId = nextProcessId.fetch_add(1);
	processPermissions[newId] = ProcessPermissions{};
	return newId;
}

std::expected<void, KernelError> PermissionStore::unregisterProcess(ProcessId pid){
	std::unique_lock<std::shared_mutex> lock(processMutex);
	auto it = processPermissions.find(pid);
	if (it == processPermissions.end())
		return std::unexpected(KernelError::PROCESS_NOT_FOUND);
	processPermissions.erase(it);
	return {};
}
