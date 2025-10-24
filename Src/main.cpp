#include <QApplication>
#include "../include/lockscreen.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    LockScreen window;

    window.show();

    return QApplication::exec();
}