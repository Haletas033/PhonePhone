//
// Created by halet on 10/23/2025.
//

#ifndef TIME_H
#define TIME_H

#include <qboxlayout.h>
#include <QLabel>
#include <QVBoxLayout>

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

    void SetupTime(QVBoxLayout *layout, const QFont &font) const;

    void Show() const;

    void Hide() const;

    explicit Time(TimeFlags flag, QVBoxLayout* layout, const QFont& font);

    explicit Time(const char *time, QVBoxLayout* layout, const QFont& font);

    void SetTime() const;
private:
    QLabel* label;
    TimeFlags timeFlag;
    const char* timeString;
};


#endif //TIME_H
