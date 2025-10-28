#include <QApplication>
#include "../include/screens/lockscreen.h"
#include "../include/screens/setupScreen.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    SetupScreen setup;

    setup.show();


    return QApplication::exec();
}
