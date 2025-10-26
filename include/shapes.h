//
// Created by halet on 10/25/2025.
//

#ifndef SHAPES_H
#define SHAPES_H
#include <QWidget.h>

class Shapes {
public:
    static QWidget* CreateBar(QWidget *parent, int x, int y, int width, int height,
        int opacity, const QColor &colour);
};

#endif //SHAPES_H
