//
// Created by halet on 10/25/2025.
//

#ifndef COMMONELEMENTS_H
#define COMMONELEMENTS_H

#include <QLabel>
#include <QPixmap>
#include "../include/shapes.h"
#include "../include/systemInfo.h"

class CommonElements {
public:
    static void WiFi(QWidget *parent, int x, int y, int w, int h);

    static void UpdateWiFi();

    static void Battery(QWidget *parent, int x, int y, int w, int h);

    static void UpdateBatteryFill();

    static void UpdateSystemInfoCorner();

    static void SystemInfoCorner(QWidget *parent);
private:
    static QLabel* WiFiIcon;
    static QLabel* batteryText;
    static QWidget* batteryFill;
    static int batteryX, batteryY, batteryW, batteryH;
};

#endif //COMMONELEMENTS_H
