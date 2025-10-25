//
// Created by halet on 10/25/2025.
//

#ifndef LOCKSCREEN_H
#define LOCKSCREEN_H
#include <QWidget.h>
#include <QTimer.h>
#include <QVBoxLayout>
#include <QMouseEvent>
#include "../include/time.h"
#include "../include/pin.h"
#include "../include/wallpaper.h"

class LockScreen final : public QWidget {
private:
    QPoint startPos;
    bool dragging;

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
