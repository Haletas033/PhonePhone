//
// Created by halet on 10/27/2025.
//

#include "../../include/screens/setupScreen.h"

#include "../../include/languages.h"

uint8_t SetupScreen::lang = 0;
std::mt19937 SetupScreen::gen{std::random_device{}()};
std::vector<std::string> SetupScreen::bag = {};
size_t SetupScreen::currentIndex = 0;
std::vector<std::string> SetupScreen::welcomes = {
    "Welcome!",
    "Bienvenue!",
    "Willkommen!",
    "Bienvenido!",
    "Benvenuto!",
    "ようこそ!",
    "欢迎!",
    "добро пожаловать!",
    "환영합니다!"
};

void SetupScreen::FadeText(QLabel* text, const QString& newText) {\
    auto* effect = static_cast<QGraphicsOpacityEffect*>(text->graphicsEffect());

    auto* fadeOut = new QPropertyAnimation(effect, "opacity");
    fadeOut->setDuration(500);
    fadeOut->setStartValue(1.0);
    fadeOut->setEndValue(0.0);

    auto* fadeIn = new QPropertyAnimation(effect, "opacity");
    fadeIn->setDuration(500);
    fadeIn->setStartValue(0.0);
    fadeIn->setEndValue(1.0);

    connect(fadeOut, &QPropertyAnimation::finished, [=]() {
        text->setText(newText);
        fadeIn->start(QAbstractAnimation::DeleteWhenStopped);
    });

    fadeOut->start(QAbstractAnimation::DeleteWhenStopped);
}

void SetupScreen::RefillBag(const std::vector<std::string> &options) {
    bag = options;
    std::ranges::shuffle(bag, gen);
    currentIndex = 0;
}

void SetupScreen::ChangeText(QLabel* text, const std::vector<std::string> &options) {
    if (currentIndex >= bag.size())
        RefillBag(welcomes);

    const QString nextText = QString::fromStdString(bag[currentIndex]);
    currentIndex++;

    FadeText(text, nextText);
}

QLabel* SetupScreen::Welcome(QLayout* layout) {
    const QFont welcomeFont("Segoe Script", 20);

    auto* welcome = new QLabel(this);

    welcome->setText("Welcome!");
    welcome->setFont(welcomeFont);
    welcome->setAlignment(Qt::AlignCenter);
    layout->addWidget(welcome);

    auto* effect = new QGraphicsOpacityEffect(welcome);
    welcome->setGraphicsEffect(effect);
    effect->setOpacity(1.0);
    welcome->show();

    return welcome;
}

uint8_t SetupScreen::LangaugeSelection(QVBoxLayout* layout) {

    layout->addStretch();

    auto* selectionText = new QLabel(this);
    selectionText->setText("Please select your language");
    layout->addWidget(selectionText, 0, Qt::AlignCenter);

    auto* selectionCombo = new QComboBox(this);

    for (const auto &language : languages) {
        selectionCombo->addItem(language.data());
    }

    layout->addWidget(selectionCombo, 0, Qt::AlignCenter);

    auto* selectionConfirm = new QPushButton("Confirm", this);
    layout->addWidget(selectionConfirm, 0, Qt::AlignCenter);

    layout->addStretch();
    layout->setSpacing(5);

    QEventLoop loop;
    uint8_t result = 0;

    connect(selectionConfirm, &QPushButton::clicked, this, [&]() {
        result = selectionCombo->currentIndex();
        loop.quit();
    });

    loop.exec();

    return result;
}

SetupScreen::SetupScreen(QWidget *parent) : QWidget(parent) {
    setFixedSize(300, 575);

    //Black background
    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::black);
    this->setPalette(palette);

    auto* layout = new QVBoxLayout(this);

    auto* welcome= Welcome(layout);

    auto* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [welcome]() {
        ChangeText(welcome, welcomes);
    });
    timer->start(3000);

    QTimer::singleShot(15000, this, [this, welcome, layout]() {
        if (!welcome || !layout)
            return;
        welcome->hide();
        lang = LangaugeSelection(layout);
    });

}
