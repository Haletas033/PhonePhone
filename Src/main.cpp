#include <QApplication>
#include "../include/screens/lockscreen.h"
#include "../include/screens/setupScreen.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    LockScreen window;

    window.show();

    return QApplication::exec();
}
