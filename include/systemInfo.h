//
// Created by halet on 10/25/2025.
//

#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H

#include <cstdint>
#include <windows.h>
#include <wlanapi.h>

class SystemInfo {
public:
    static uint8_t GetBatteryPercent();
    static uint8_t GetWifiStrength();

    static bool IsCharging();
};

#endif //SYSTEMINFO_H
