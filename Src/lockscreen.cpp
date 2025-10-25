//
// Created by halet on 10/25/2025.
//

#include "../include/lockscreen.h"

#include "../include/systemInfo.h"

LockScreen::LockScreen(QWidget *parent) : QWidget(parent) {
    setFixedSize(300, 575);

    Wallpaper lockScreenWallpaper("../textures/defaultWallpaper.jpg", *this);

    auto* layout = new QVBoxLayout(this);

    QFont dateFont("Arial", 12);
    dateFont.setWeight(QFont::Bold);
    QFont timeFont("Arial", 24);
    timeFont.setWeight(QFont::DemiBold);

    //Display quick charging info
    const std::string isCharging = SystemInfo::IsCharging() ? "Charging, " : "";
    const std::string chargeInfo = isCharging + std::to_string(SystemInfo::GetBatteryPercent()) + "% Charged";
    lockScreenCharging = new QLabel(chargeInfo.data());
    lockScreenCharging->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    lockScreenCharging->setFont(dateFont);

    layout->addWidget(lockScreenCharging);

    lockScreenDate = new Time(Time::DATE, layout, dateFont);
    lockScreenTime = new Time(Time::TIME24, layout, timeFont);
    lockScreenDate->Hide();

    //Which chargingInfo out for dateTime after 4 seconds
    QTimer::singleShot(4000, this, [&]() {
        lockScreenCharging->hide();
        lockScreenDate->Show();
    });

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
