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

class Pin {
private:
    static QWidget* gridWidget;
    static QPushButton* digits[10];
    static std::vector<int> digitsBuffer;
    static QEventLoop* eventLoop;
    static int remainingDigits;
public:
    static std::string buttonStyles;

    static std::string textButtonTransparentStyles;

    static QPushButton* CreateButton(QGridLayout *grid, int r, int c, int digit, const char *styles);
    static QPushButton* CreateButton(QGridLayout *grid, int r, int c, const char *text, const char *styles);

    static void CreatePinInput(QVBoxLayout *layout, QWidget *swipeBar = nullptr);

    static void DigitPressed(int digit);

    static uint16_t GetNDigits(int digits);

    static void HidePinInput();
    static void ShowPinInput();
};

#endif //PIN_H
