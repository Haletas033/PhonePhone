//
// Created by halet on 10/25/2025.
//

#include "../include/systemInfo.h"

uint8_t SystemInfo::GetBatteryPercent() {
    SYSTEM_POWER_STATUS powerLevel;
    if (GetSystemPowerStatus(&powerLevel)) return powerLevel.BatteryLifePercent;
    return 0;
}

uint8_t SystemInfo::GetWifiStrength() {
    HANDLE hClient = nullptr;
    constexpr DWORD dwMaxClient = 2;
    DWORD dwCurVersion = 0;
    DWORD result = WlanOpenHandle(dwMaxClient, nullptr, &dwCurVersion, &hClient);
    if (result != ERROR_SUCCESS) {
        return 0;
    }

    PWLAN_INTERFACE_INFO_LIST pIfList = nullptr;
    result = WlanEnumInterfaces(hClient, nullptr, &pIfList);
    if (result != ERROR_SUCCESS) {
        WlanCloseHandle(hClient, nullptr);
        return 0;
    }

    uint8_t signalQuality = 0;

    for (unsigned int i = 0; i < pIfList->dwNumberOfItems; ++i) {
        PWLAN_INTERFACE_INFO pIfInfo = &pIfList->InterfaceInfo[i];

        PWLAN_CONNECTION_ATTRIBUTES pConnectInfo = NULL;
        DWORD connectInfoSize = sizeof(WLAN_CONNECTION_ATTRIBUTES);
        WLAN_OPCODE_VALUE_TYPE opCode = wlan_opcode_value_type_invalid;

        result = WlanQueryInterface(hClient,
                                    &pIfInfo->InterfaceGuid,
                                    wlan_intf_opcode_current_connection,
                                    nullptr,
                                    &connectInfoSize,
                                    reinterpret_cast<PVOID *>(&pConnectInfo),
                                    &opCode);
        if (result == ERROR_SUCCESS && pConnectInfo) {
            //signalQuality is 1-100
            signalQuality = static_cast<uint8_t>(pConnectInfo->wlanAssociationAttributes.wlanSignalQuality);
            WlanFreeMemory(pConnectInfo);
        }
    }

    if (pIfList)
        WlanFreeMemory(pIfList);
    if (hClient)
        WlanCloseHandle(hClient, nullptr);

    return signalQuality;
}

bool SystemInfo::IsCharging() {
    SYSTEM_POWER_STATUS powerLevel;
    if (GetSystemPowerStatus(&powerLevel)) return powerLevel.ACLineStatus == 1;
    return false;
}