//
// Created by halet on 10/25/2025.
//

#ifndef LOCKSCREEN_H
#define LOCKSCREEN_H
#include <QWidget.h>
#include <QTimer.h>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <locale>

#include "setupScreen.h"
#include "../time.h"
#include "../pin.h"
#include "../wallpaper.h"
#include "../shapes.h"
#include "../commonElements.h"
#include "../systemInfo.h"

class LockScreen final : public QWidget {
    Q_OBJECT
private:
    QPoint startPos;
    bool dragging;

    SetupScreen* setupScreen = nullptr;
    QWidget* lockScreenWidget = nullptr;

    QWidget* swipeBar;
    QLabel* lockScreenCharging;
    Time* lockScreenDate;
    Time* lockScreenTime;
public:
    explicit LockScreen(QWidget* parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif //LOCKSCREEN_H
