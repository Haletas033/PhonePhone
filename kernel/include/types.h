#include <cstdint>
using HotPermissionMap = uint_fast64_t;
using ColdPermissionMap = uint_least64_t;

enum class PermissionLevel {
	DENIED,
	ASK,
	WHEN_FOCUSED,
	WHEN_RUNNING,
	ALWAYS
};

enum class Permission {
	//HOT
	CAMERA,
	MICROPHONE,
	FILE_READ_MEDIA,
	FILE_WRITE_MEDIA,
	NETWORK,
	LOCATION,
	SETTINGS,

	//COLD
	FILE_READ_ROOT,
	FILE_WRITE_ROOT,
	CLIPBOARD,
	NOTIFICATIONS,
	APP_LIST,
	CONTACTS,
	RUN_ON_STARTUP,
	RUN_IN_BACKGROUND,
	RUN_HEADLESS,
	INTER_APP
};
