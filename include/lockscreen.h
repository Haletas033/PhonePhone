//
// Created by halet on 10/25/2025.
//

#ifndef LOCKSCREEN_H
#define LOCKSCREEN_H
#include <QWidget.h>
#include <QTimer.h>
#include <QVBoxLayout>
#include "../include/time.h"
#include "../include/pin.h"
#include "../include/wallpaper.h"

class LockScreen final : public QWidget {
private:
    Time* lockScreenDate;
    Time* lockScreenTime;
public:
    explicit LockScreen(QWidget* parent = nullptr);
};

#endif //LOCKSCREEN_H
