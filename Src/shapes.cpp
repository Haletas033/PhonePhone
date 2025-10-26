//
// Created by halet on 10/25/2025.
//

#include "../include/shapes.h"

QWidget *Shapes::CreateBar(QWidget *parent, const int x, const int y, const int width, const int height,
    const int opacity, const QColor &colour)
{
    auto* bar = new QWidget(parent);
    bar->setGeometry(x, y, width, height);
    bar->setStyleSheet(QString("background-color: rgba(%1, %2, %3, %4); border-radius: %5px;")
        .arg(colour.red())
        .arg(colour.green())
        .arg(colour.blue())
        .arg(opacity)
        .arg(height / 2)
    );
    return bar;
}

