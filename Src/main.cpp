#include <QApplication>
#include <QLabel>
#include <QBoxLayout>
#include <QMainWindow>
#include <QTimer>
#include "../include/time.h"
#include <QPixmap>

#include "../include/pin.h"
#include "../include/wallpaper.h"

#include "../include/lockscreen.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    LockScreen window;

    window.show();

    return QApplication::exec();
}