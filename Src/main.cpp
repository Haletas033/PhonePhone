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

    const Time lockScreenDate(Time::DATE);
    const Time lockScreenTime(Time::pTIME24);

    auto* layout = new QVBoxLayout(&window);

    layout->addWidget(lockScreenDate.label, 0);
    layout->addWidget(lockScreenTime.label, 0);
    layout->addStretch();

    window.show();

    auto* timer = new QTimer(&window);
    QObject::connect(timer, &QTimer::timeout, [&]() {
        lockScreenTime.SetTime();
    });
    timer->start(1000);

    return QApplication::exec();
}