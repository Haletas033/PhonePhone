#ifndef PERMISSIONS_H
#define PERMISSIONS_H

#include "types.h"
#include <cstdint>
#include <expected>
#include <shared_mutex>
#include <unordered_map>

struct ProcessPermissions {
	HotPermissionMap hotMap = {0};
	ColdPermissionMap coldMap = {0};
};

class PermissionStore {
private:
	std::unordered_map<ProcessId, ProcessPermissions> processPermissions;
	//Thread Safety: shared lock for check/hasMinimumLevel/isKilledGlobally
	//unique_lock for grant/revoke/setKillSwitch
	std::shared_mutex processMutex;
	KillSwitchMap killSwitch;
public:
	std::expected<void, KernelError> grant(ProcessId pid, Permission permission, PermissionLevel level);
	std::expected<void, KernelError> revoke(ProcessId pid, Permission permission);
	std::expected<PermissionLevel, KernelError> check(ProcessId pid, Permission permission);
	std::expected<bool, KernelError> hasMinimumLevel(ProcessId pid, Permission permission, PermissionLevel level);
	void setKillSwitch(Permission permission, bool shouldKill);
	std::expected<bool, KernelError> isKilledGlobally(Permission permission);
};

#endif //PERMISSIONS_H
