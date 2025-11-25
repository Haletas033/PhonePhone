//
// Created by halet on 10/25/2025.
//

#include "../../include/screens/lockscreen.h"

#include "../../include/languages.h"

LockScreen::LockScreen(QWidget *parent) : QWidget(parent) {
    setFixedSize(300, 575);

    setupScreen = new SetupScreen(this);
    setupScreen->setGeometry(0, 0, width(), height());
    setupScreen->show();

    lockScreenWidget = new QWidget(this);
    lockScreenWidget->setGeometry(0, 0, width(), height());
    lockScreenWidget->hide();

    Wallpaper lockScreenWallpaper("../textures/defaultWallpaper.jpg", *lockScreenWidget);

    auto* layout = new QVBoxLayout(lockScreenWidget);

    QFont dateFont("Arial", 12);
    dateFont.setWeight(QFont::Bold);
    QFont timeFont("Arial", 24);
    timeFont.setWeight(QFont::DemiBold);

    //Display quick charging info
    const std::string isCharging = SystemInfo::IsCharging() ? translation["Charging"][1] : "";
    const std::string chargeInfo = isCharging + std::to_string(SystemInfo::GetBatteryPercent()) + translation["Charging"][1];
    lockScreenCharging = new QLabel(chargeInfo.data());
    lockScreenCharging->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    lockScreenCharging->setFont(dateFont);

    layout->addWidget(lockScreenCharging);

    lockScreenDate = new Time(Time::DATE, layout, dateFont);
    lockScreenTime = new Time(Time::TIME24, layout, timeFont);
    lockScreenDate->Hide();

    swipeBar = Shapes::CreateBar(lockScreenWidget, 25, 550, 250, 5, 255, Qt::white);

    CommonElements::SystemInfoCorner(lockScreenWidget);

    pin.CreatePinInput(layout, swipeBar);
    pin.HidePinInput();

    layout->addStretch();

    auto* timer = new QTimer(lockScreenWidget);
    connect(setupScreen, &SetupScreen::SetupFinished, this, [this]() {
        setupScreen->hide();
        lockScreenWidget->show();

        //Show charging info when setup is finished
        const std::string isCharging = SystemInfo::IsCharging() ? translation["Charging"][setupScreen->lang] : "";
        const std::string chargeInfo = isCharging + std::to_string(SystemInfo::GetBatteryPercent()) + translation["Charged"][setupScreen->lang];
        lockScreenCharging->setText(chargeInfo.data());
        lockScreenCharging->show();

        //Switch charging info out for date after 4 seconds
        QTimer::singleShot(4000, lockScreenWidget, [this]() {
            lockScreenCharging->hide();
            lockScreenDate->Show();
        });
    });

    connect(timer, &QTimer::timeout, [&]() {
        lockScreenTime->SetTime();
        lockScreenDate->SetTime();
        CommonElements::UpdateSystemInfoCorner();

        const std::string isCharging = SystemInfo::IsCharging() ? translation["Charging"][setupScreen->lang] : "";
        const std::string chargeInfo = isCharging + std::to_string(SystemInfo::GetBatteryPercent()) + translation["Charged"][setupScreen->lang];
        lockScreenCharging->setText(chargeInfo.data());
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

    //Trigger if mouse travels more than 1 travelDistance of height
    constexpr int travelDistance = 3;
    if (distance > height() / travelDistance) {
        pin.ShowPinInput();
        swipeBar->hide();

        const uint16_t pinCode = pin.GetNDigits(4);
        qDebug() << "LockScreen PIN entered:" << pinCode;

        pin.HidePinInput();
        swipeBar->show();

        dragging = false;
    }
}

void LockScreen::mouseReleaseEvent(QMouseEvent* event) {
    dragging = false;
}
