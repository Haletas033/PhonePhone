//
// Created by halet on 10/24/2025.
//

#ifndef PIN_H
#define PIN_H

#include <QPushButton>
#include <QLayout>

class Pin {
private:
    static QWidget* gridWidget;
public:
    static const char* buttonStyles;

    static void CreateButton(QGridLayout *grid, int r, int c, int digit);

    static void CreatePinInput(QVBoxLayout *layout);

    static void HidePinInput();
    static void ShowPinInput();
};

#endif //PIN_H
