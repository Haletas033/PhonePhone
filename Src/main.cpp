#include <QApplication>
#include <QLabel>
#include <QBoxLayout>
#include <QMainWindow>
#include <QTimer>
#include "../include/time.h"
#include <QPixmap>

#include "../include/pin.h"
#include "../include/wallpaper.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QWidget window;
    window.setFixedSize(300, 575);
    Wallpaper lockScreenWallpaper("../textures/defaultWallpaper.jpg", window);

    auto* layout = new QVBoxLayout(&window);

    QFont dateFont("Arial", 12);
    dateFont.setWeight(QFont::Bold);
    QFont timeFont("Arial", 24);
    timeFont.setWeight(QFont::DemiBold);


    const Time lockScreenDate(Time::DATE, layout, dateFont);
    const Time lockScreenTime(Time::TIME24, layout, timeFont);

    Pin::ShowPinInput(layout);

    layout->addStretch();

    window.show();

    auto* timer = new QTimer(&window);
    QObject::connect(timer, &QTimer::timeout, [&]() {
        lockScreenTime.SetTime();
        lockScreenDate.SetTime();
    });
    timer->start(1000);

    return QApplication::exec();
}