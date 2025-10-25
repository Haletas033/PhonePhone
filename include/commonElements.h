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
    static void Battery(QWidget *parent, int x, int y, int w, int h);

    static void UpdateBatteryFill();

    static void SystemInfoCorner(QWidget *parent);
private:
    static QWidget* batteryFill;
    static int batteryX, batteryY, batteryW, batteryH;
};

#endif //COMMONELEMENTS_H
