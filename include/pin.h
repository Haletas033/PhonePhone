//
// Created by halet on 10/24/2025.
//

#ifndef PIN_H
#define PIN_H

#include <QPushButton>
#include <QPropertyAnimation>
#include <QGraphicsEffect>
#include <QLayout>

class Pin {
private:
    static QWidget* gridWidget;
public:
    static const char* buttonStyles;

    static const char *textButtonTransparentStyles;

    static QPushButton* CreateButton(QGridLayout *grid, int r, int c, int digit, const char *styles);
    static QPushButton* CreateButton(QGridLayout *grid, int r, int c, const char *text, const char *styles);

    static void CreatePinInput(QVBoxLayout *layout);

    static void HidePinInput();
    static void ShowPinInput();
};

#endif //PIN_H
