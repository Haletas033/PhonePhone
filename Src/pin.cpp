#include "../include/pin.h"

const char* Pin::buttonStyles = R"(
    QPushButton {
        background-color: rgba(255, 255, 255, 50);
        border: none;
        border-radius: 25px;
        color: white;
        font-size: 18px;
        font-weight: bold;
    }
    QPushButton:hover {
        background-color: rgba(255, 255, 255, 120);
    }
    QPushButton:pressed {
        background-color: rgba(255, 255, 255, 150);
    }
)";

void Pin::CreateButton(QGridLayout* grid, const int r, const int c, const int digit) {
    QPushButton *button = new QPushButton(QString::number(digit));
    button->setFixedSize(50, 50);

    button->setStyleSheet(buttonStyles);

    grid->addWidget(button, r, c);
}

void Pin::ShowPinInput(QVBoxLayout* layout) {
    QWidget* gridWidget = new QWidget();
    QGridLayout* grid = new QGridLayout(gridWidget);

    grid->setSpacing(5);

    constexpr int rows = 3;
    constexpr int cols = 3;
    int digit = 1;

    //Create main 9 buttons
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            CreateButton(grid, r, c, digit++);
        }
    }

    //0 Button
    CreateButton(grid, 3, 1, 0);

    layout->addStretch(1);
    layout->addWidget(gridWidget, 0, Qt::AlignCenter);
    layout->addStretch(2);
}
