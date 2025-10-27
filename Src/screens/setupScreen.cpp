//
// Created by halet on 10/27/2025.
//

#include "../../include/screens/setupScreen.h"

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
    "환영합니다!",
    "Selamat datang!"
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

SetupScreen::SetupScreen(QWidget *parent) : QWidget(parent) {
    setFixedSize(300, 575);

    //Black background
    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::black);
    this->setPalette(palette);

    auto* layout = new QVBoxLayout(this);

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

    auto* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [welcome]() {
        ChangeText(welcome, welcomes);
    });
    timer->start(3000);
}
