#include <QApplication>
#include <QLabel>
#include <QBoxLayout>
#include <QMainWindow>
#include <QTimer>
#include "../Include/time.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QWidget window;
    window.setFixedSize(300, 600);

    const Time homeScreenDate(Time::DATE);
    const Time homeScreenTime(Time::TIME24);

    auto* layout = new QVBoxLayout(&window);

    layout->addWidget(homeScreenDate.label, 0);
    layout->addWidget(homeScreenTime.label, 0);
    layout->addStretch();

    window.show();

    auto* timer = new QTimer(&window);
    QObject::connect(timer, &QTimer::timeout, [&]() {
        homeScreenTime.SetTime();
    });
    timer->start(1000);

    return QApplication::exec();
}