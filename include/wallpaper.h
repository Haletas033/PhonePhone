//
// Created by halet on 10/24/2025.
//

#ifndef WALLPAPER_H
#define WALLPAPER_H

#include <QLabel>

class Wallpaper {
private:
    QLabel* image;
public:
    Wallpaper(const char* im, QWidget &window);
};

#endif //WALLPAPER_H
