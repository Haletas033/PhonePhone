//
// Created by halet on 10/27/2025.
//

#ifndef SETUPSCREEN_H
#define SETUPSCREEN_H

#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDialog>
#include <QComboBox>
#include <QLabel>
#include <QFont>
#include <QWidget>
#include <QTimer>
#include <random>

class SetupScreen final : public QWidget {
    Q_OBJECT
private:
    static std::vector<std::string> welcomes;
    static std::vector<std::string> bag;
    static size_t currentIndex;
    static std::mt19937 gen;
    static uint8_t lang;
public:
    static void FadeText(QLabel *text, const QString &newText);

    static void RefillBag(const std::vector<std::string> &options);

    static void ChangeText(QLabel *text, const std::vector<std::string> &options);

    QLabel *Welcome(QLayout *layout);

    uint8_t LangaugeSelection(QVBoxLayout *layout);

    explicit SetupScreen(QWidget* parent = nullptr);
signals:
    void SetupFinished();
};

#endif //SETUPSCREEN_H
