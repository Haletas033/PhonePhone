#ifndef PERMISSIONS_H
#define PERMISSIONS_H

#include "types.h"
#include <atomic>
#include <expected>
#include <shared_mutex>
#include <unordered_map>

struct ProcessPermissions {
	HotPermissionMap hotMap = {0};
	ColdPermissionMap coldMap = {0};
};

class PermissionStore {
private:
	std::atomic<ProcessId> nextProcessId;
	std::unordered_map<ProcessId, ProcessPermissions> processPermissions;
	//Thread Safety: shared lock for check/hasMinimumLevel/isKilledGlobally
	//unique_lock for grant/revoke/setKillSwitch
	std::shared_mutex processMutex;
	KillSwitchMap killSwitch;
private:
	PermissionLevel getBits(ProcessPermissions& permissions, Permission permission);
	void setBits(ProcessPermissions& permissions, Permission permission, PermissionLevel level);
public:
	//Permission Management
	std::expected<void, KernelError> grant(ProcessId pid, Permission permission, PermissionLevel level);
	std::expected<void, KernelError> revoke(ProcessId pid, Permission permission);
	std::expected<PermissionLevel, KernelError> check(ProcessId pid, Permission permission);
	std::expected<bool, KernelError> hasMinimumLevel(ProcessId pid, Permission permission, PermissionLevel level);
	void setKillSwitch(Permission permission, bool shouldKill);
	bool isKilledGloballyInternal(Permission permission);
	bool isKilledGlobally(Permission permission);

	//Process Management
	std::expected<ProcessId, KernelError> registerProcess();
	std::expected<void, KernelError> unregisterProcess(ProcessId pid);
	
};

#endif //PERMISSIONS_H
