//
// Created by halet on 10/25/2025.
//

#include "../include/lockscreen.h"

LockScreen::LockScreen(QWidget *parent) : QWidget(parent) {
    setFixedSize(300, 575);

    Wallpaper lockScreenWallpaper("../textures/defaultWallpaper.jpg", *this);

    auto* layout = new QVBoxLayout(this);

    QFont dateFont("Arial", 12);
    dateFont.setWeight(QFont::Bold);
    QFont timeFont("Arial", 24);
    timeFont.setWeight(QFont::DemiBold);


    lockScreenDate = new Time(Time::DATE, layout, dateFont);
    lockScreenTime = new Time(Time::TIME24, layout, timeFont);

    Pin::CreatePinInput(layout);
    Pin::HidePinInput();

    layout->addStretch();

    auto* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [&]() {
        lockScreenTime->SetTime();
        lockScreenDate->SetTime();
    });
    timer->start(1000);
}

void LockScreen::mousePressEvent(QMouseEvent* event) {
    startPos = event->pos();
    dragging = true;
}

void LockScreen::mouseMoveEvent(QMouseEvent* event) {
    if (!dragging) return;

    int distance = startPos.y() - event->pos().y();
    if (distance > height() / 2) {
        Pin::ShowPinInput();
        dragging = false;
    }
}

void LockScreen::mouseReleaseEvent(QMouseEvent* event) {
    dragging = false;
}
