#include "../include/pin.h"

QWidget* Pin::gridWidget = nullptr;

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

const char* Pin::textButtonTransparentStyles = R"(
    QPushButton {
        background-color: rgba(255, 255, 255, 0);
        border: none;
        border-radius: 25px;
        color: white;
        font-size: 14px;
    }
    QPushButton:hover {
        background-color: rgba(255, 255, 255, 10);
    }
    QPushButton:pressed {
        background-color: rgba(255, 255, 255, 20);
    }
)";

QPushButton* Pin::CreateButton(QGridLayout *grid, const int r, const int c, const int digit,
                               const char *styles = buttonStyles)
{
    const auto button = new QPushButton(QString::number(digit));
    button->setFixedSize(50, 50);

    button->setStyleSheet(styles);

    grid->addWidget(button, r, c);

    return button;
}

QPushButton* Pin::CreateButton(QGridLayout *grid, const int r, const int c, const char *text,
                               const char *styles = textButtonTransparentStyles)
{
    const auto button = new QPushButton(text);
    button->setFixedSize(50, 50);

    button->setStyleSheet(styles);

    grid->addWidget(button, r, c);

    return button;
}

void Pin::CreatePinInput(QVBoxLayout* layout) {
    gridWidget = new QWidget();
    const auto grid = new QGridLayout(gridWidget);

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

    //CancelButton
    const auto cancelButton = CreateButton(grid, 3, 2, "Cancel");
    QObject::connect(cancelButton, &QPushButton::clicked, [=]() {
        HidePinInput();
    });

    layout->addStretch(1);
    layout->addWidget(gridWidget, 0, Qt::AlignCenter);
    layout->addStretch(2);
}

void Pin::HidePinInput() {
    gridWidget->hide();
}
void Pin::ShowPinInput() {
    gridWidget->show();
}

