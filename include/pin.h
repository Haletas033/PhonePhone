//
// Created by halet on 10/24/2025.
//

#ifndef PIN_H
#define PIN_H

#include <QEventLoop.h>
#include <QPushButton>
#include <QPropertyAnimation>
#include <QGraphicsEffect>
#include <QLayout>

#include "styleManager.h"

class Pin {
private:
    QWidget* gridWidget = nullptr;
    QPushButton* digits[10] = {nullptr};
    QEventLoop* eventLoop = nullptr;
    int remainingDigits = 0;
    std::vector<int> digitsBuffer;
public:
    static std::string buttonStyles;
    static std::string textButtonTransparentStyles;

    QPushButton* CreateButton(QGridLayout *grid, int r, int c, int digit, const char *styles);
    QPushButton* CreateButton(QGridLayout *grid, int r, int c, const char *text, const char *styles) const;

    void CreatePinInput(QVBoxLayout *layout, QWidget *swipeBar = nullptr);

    void DigitPressed(int digit);

    uint16_t GetNDigits(int digits);

    void HidePinInput();
    void ShowPinInput();
};

#endif //PIN_H
