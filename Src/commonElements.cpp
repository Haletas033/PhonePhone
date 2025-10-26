//
// Created by halet on 10/25/2025.
//

#include "../include/commonElements.h"

QLabel* CommonElements::WiFiIcon = nullptr;
QWidget* CommonElements::batteryFill = nullptr;
int CommonElements::batteryX = 0, CommonElements::batteryY = 0, CommonElements::batteryW = 0, CommonElements::batteryH = 0;
QLabel* CommonElements::batteryText = nullptr;

void CommonElements::WiFi(QWidget *parent, const int x, const int y, const int w, const int h) {
    uint8_t WiFiState = 1;
    if (SystemInfo::GetWifiStrength() > 75) WiFiState = 4;
    else if (SystemInfo::GetWifiStrength() > 50) WiFiState = 3;
    else if (SystemInfo::GetWifiStrength() > 25) WiFiState = 2;

    const QString WiFiPath = "../textures/WiFiStates/WiFi-" + QString::number(WiFiState) + ".png";

    WiFiIcon = new QLabel(parent);
    WiFiIcon->setPixmap(QPixmap(WiFiPath));
    WiFiIcon->setScaledContents(true);
    WiFiIcon->setGeometry(x,y,w,h);
    WiFiIcon->show();
}

void CommonElements::UpdateWiFi() {
    uint8_t WiFiState = 1;
    if (SystemInfo::GetWifiStrength() > 75) WiFiState = 4;
    else if (SystemInfo::GetWifiStrength() > 50) WiFiState = 3;
    else if (SystemInfo::GetWifiStrength() > 25) WiFiState = 2;

    const QString WiFiPath = "../textures/WiFiStates/WiFi-" + QString::number(WiFiState) + ".png";
    WiFiIcon->setPixmap(QPixmap(WiFiPath));
}

void CommonElements::Battery(QWidget *parent, const int x, const int y, const int w, const int h) {
    auto* batteryOutline = new QLabel(parent);
    batteryOutline->setPixmap(QPixmap("../textures/battery-icon.png"));
    batteryOutline->setScaledContents(true);
    batteryOutline->setGeometry(x,y,w,h);
    batteryOutline->show();

    constexpr int MARGIN = 3;

    uint8_t powerLevel = SystemInfo::GetBatteryPercent();
    double fillPercent = std::clamp(powerLevel / 100.0, 0.0, 1.0);
    double fillBarWidth = (w-2 * (MARGIN+1)) * fillPercent;

    QColor colour;
    if (powerLevel < 15) colour = Qt::red;
    else if (SystemInfo::IsCharging()) colour = Qt::green;
    else colour = Qt::white;

    batteryFill = Shapes::CreateBar(parent, x+MARGIN-1, y+MARGIN*2,
        fillBarWidth+MARGIN, h-(MARGIN*4)+1, 1, colour);

    batteryFill->show();

    //Save for update
    batteryX = x;
    batteryY = y;
    batteryW = w;
    batteryH = h;
}

void CommonElements::UpdateBatteryFill() {
    constexpr int MARGIN = 3;

    uint8_t powerLevel = SystemInfo::GetBatteryPercent();
    double fillPercent = std::clamp(powerLevel / 100.0, 0.0, 1.0);
    double fillBarWidth = (batteryW-2 * (MARGIN+1)) * fillPercent;

    QColor colour;
    if (powerLevel < 15) colour = Qt::red;
    else if (SystemInfo::IsCharging()) colour = Qt::green;
    else colour = Qt::white;

    batteryFill->setGeometry(batteryX+MARGIN-1, batteryY+MARGIN*2,
        fillBarWidth+MARGIN, batteryH-(MARGIN*4)+1);
    batteryFill->setStyleSheet(QString("background-color: %1; border-radius: %4px;")
                                .arg(colour.name())
                                .arg((batteryH-(MARGIN*4)+1) / 4));

}

void CommonElements::UpdateSystemInfoCorner() {
    UpdateWiFi();
    batteryText->setText(QString::number(SystemInfo::GetBatteryPercent()) + "%");
    UpdateBatteryFill();
}

void CommonElements::SystemInfoCorner(QWidget* parent) {
    //Wi-Fi strength
    WiFi(parent, 228, 15, 10, 10);

    //Battery %
    batteryText = new QLabel(parent);
    batteryText->setText(QString::number(SystemInfo::GetBatteryPercent()) + "%");
    batteryText->setGeometry(240, 10, 30, 20);
    batteryText->show();

    //Battery charge
    Battery(parent, 270, 10, 20, 20);

    //Underline
    Shapes::CreateBar(parent, 235, 30, 50, 2, 80, Qt::gray);
}
