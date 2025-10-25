#include "../include/pin.h"

#include "../include/styleManager.h"

QWidget* Pin::gridWidget = nullptr;

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
                               const char *styles = textButtonTransparentStyles.c_str())
{
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
            CreateButton(grid, r, c, digit++);
        }
    }

    //0 Button
    CreateButton(grid, 3, 1, 0);

    //CancelButton
    const auto cancelButton = CreateButton(grid, 3, 2, "Cancel");
    QObject::connect(cancelButton, &QPushButton::clicked, [=]() {
        HidePinInput();
        swipeBar->show();
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

