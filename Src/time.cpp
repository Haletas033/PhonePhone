//
// Created by halet on 10/23/2025.
//

#include "../Include/time.h"

Time::Time(const TimeFlags flag) {
    label = new QLabel("??:??");
    timeFlag = flag;
    SetTime();
    label->setAlignment(Qt::AlignTop | Qt::AlignHCenter);
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
        case DATE: oss << std::put_time(localTime, "%a %d %b"); break;
        case HOUR: oss << std::put_time(localTime, "%H"); break;
        case MINUTE: oss << std::put_time(localTime, "%M"); break;
        case SECOND: oss << std::put_time(localTime, "%S"); break;
    }

    this->label->setText(QString::fromStdString(oss.str()));
}