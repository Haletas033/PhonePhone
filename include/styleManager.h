//
// Created by halet on 10/25/2025.
//

#ifndef STYLEMANAGER_H
#define STYLEMANAGER_H

#include <string>
#include <fstream>
#include <sstream>

#define CIRCULAR_BUTTON "../styles/circularButton.css"
#define CIRCULAR_BUTTON_TRANSPARENT "../styles/circularButtonTransparent.css"

class StyleManager {
public:
    static std::string LoadStyles(const char* path);
};

#endif //STYLEMANAGER_H
