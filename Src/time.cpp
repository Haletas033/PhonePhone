//
// Created by halet on 10/23/2025.
//

#include "../include/time.h"

void Time::SetupTime(QVBoxLayout* layout, const QFont& font) const {
    SetTime();
    label->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    label->setFont(font);
    layout->setContentsMargins(0, 50, 0, 0);
    layout->addWidget(label, 0);
}


Time::Time(const TimeFlags flag, QVBoxLayout* layout, const QFont& font) {
    label = new QLabel("??:??");
    timeFlag = flag;
    timeString = "";
    SetupTime(layout, font);
}

Time::Time(const char* time, QVBoxLayout* layout, const QFont& font) {
    label = new QLabel("??:??");
    timeString = time;
    timeFlag = TIME_STRING;
    SetupTime(layout, font);
}

void Time::SetTime() const {
    const auto now = std::chrono::system_clock::now();
    const std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    const std::tm* localTime = std::localtime(&currentTime);

    std::ostringstream oss;

    switch (timeFlag) {
        case TIME12: oss << std::put_time(localTime, "%I:%M %p"); break;
        case TIME24: oss << std::put_time(localTime, "%H:%M"); break;
        case pTIME12: oss << std::put_time(localTime, "%I:%M:%S %p"); break;
        case pTIME24: oss << std::put_time(localTime, "%H:%M:%S"); break;
        case DATE: oss << std::put_time(localTime, "%A, %d %B"); break;
        case sDATE: oss << std::put_time(localTime, "%a %d %b"); break;
        case TIME_STRING: oss << std::put_time(localTime, timeString); break;
    }

    this->label->setText(QString::fromStdString(oss.str()));
}
