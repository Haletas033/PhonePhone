//
// Created by halet on 10/25/2025.
//

#include "../include/styleManager.h"

std::string StyleManager::LoadStyles(const char *path) {
    const std::ifstream file(path);

    std::ostringstream sstr;
    sstr << file.rdbuf();
    return sstr.str();
}
