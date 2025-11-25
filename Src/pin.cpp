#include "../include/pin.h"

#include "../include/styleManager.h"

std::string Pin::buttonStyles = StyleManager::LoadStyles(CIRCULAR_BUTTON);
std::string Pin::textButtonTransparentStyles = StyleManager::LoadStyles(CIRCULAR_BUTTON_TRANSPARENT);

QPushButton* Pin::CreateButton(QGridLayout *grid, const int r, const int c, const int digit,
                               const char *styles = buttonStyles.c_str())
{
    const auto button = new QPushButton(QString::number(digit));
    button->setFixedSize(50, 50);

    button->setStyleSheet(styles);

    grid->addWidget(button, r, c);

    return button;
}

QPushButton* Pin::CreateButton(QGridLayout *grid, const int r, const int c, const char *text,
                               const char *styles = textButtonTransparentStyles.c_str()) const {
    const auto button = new QPushButton(text);
    button->setFixedSize(50, 50);

    button->setStyleSheet(styles);

    grid->addWidget(button, r, c);

    return button;
}

void Pin::CreatePinInput(QVBoxLayout* layout, QWidget* swipeBar) {
    gridWidget = new QWidget();
    const auto grid = new QGridLayout(gridWidget);

    grid->setSpacing(5);

    constexpr int rows = 3;
    constexpr int cols = 3;
    int digit = 1;

    //Create main 9 buttons
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            digits[digit] = CreateButton(grid, r, c, digit++);
        }
    }

    //0 Button
    digits[0] = CreateButton(grid, 3, 1, 0);

    //Connect every digit
    for (int d = 0; d < 11; ++d) {
        QObject::connect(digits[d], &QPushButton::clicked, [d, this]() {
            DigitPressed(d-1);
        });
    }

    //Connect Cancel Button
    const auto cancelButton = CreateButton(grid, 3, 2, "Cancel");
    QObject::connect(cancelButton, &QPushButton::clicked, [=]() {
        HidePinInput();
        if (swipeBar) swipeBar->show();
    });

    layout->addStretch(1);
    layout->addWidget(gridWidget, 0, Qt::AlignCenter);
    layout->addStretch(2);
}

void Pin::DigitPressed(const int digit) {
    digitsBuffer.push_back(digit);
    if (eventLoop && static_cast<int>(digitsBuffer.size()) >= remainingDigits) {
        eventLoop->quit();
    }
}

uint16_t Pin::GetNDigits(const int digits) {
    digitsBuffer.clear();
    remainingDigits = digits;

    QEventLoop loop;
    eventLoop = &loop;
    loop.exec();

    eventLoop = nullptr;

    uint16_t result = 0;
    for (const int d : digitsBuffer) {
        result = result * 10 + d;
    }

    qDebug() << result;
    return result;
}

void Pin::HidePinInput() {
    gridWidget->hide();
}
void Pin::ShowPinInput() {
    gridWidget->show();
}

