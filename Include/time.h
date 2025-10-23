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
        HOUR,
        MINUTE,
        SECOND
    };

    QLabel* label;
    explicit Time(TimeFlags flag);
    void SetTime() const;
private:
    TimeFlags timeFlag;
};


#endif //TIME_H
