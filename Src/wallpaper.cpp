//
// Created by halet on 10/24/2025.
//

#include "../include/wallpaper.h"

Wallpaper::Wallpaper(const char *im, QWidget &window) {
    image = new QLabel(&window);
    image->setPixmap(QPixmap(im));
    image->setScaledContents(true);
    image->setGeometry(0, 0, window.width(), window.height());
    image->lower();
}
