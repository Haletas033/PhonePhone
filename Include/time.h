//
// Created by halet on 10/23/2025.
//

#ifndef TIME_H
#define TIME_H

#include <QLabel>

class Time {
public:
    enum TimeFlags {
        TIME12,
        TIME24,
        pTIME12,
        pTIME24,
        DATE,
        sDATE,
        TIME_STRING
    };

    QLabel* label;
    explicit Time(TimeFlags flag);

    explicit Time(const char *time);

    void SetTime() const;
private:
    TimeFlags timeFlag;
    const char* timeString;
};


#endif //TIME_H
