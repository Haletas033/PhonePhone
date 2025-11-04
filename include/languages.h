//
// Created by halet on 10/28/2025.
//

#ifndef LANGUAGES_H
#define LANGUAGES_H

#define ENGLISH 0
#define CHINESE 1
#define GERMAN 2
#define ITALIAN 3
#define FRENCH 4
#define SPANISH 5
#define RUSSIAN 6
#define JAPANESE 7
#define KOREAN 8
#include <string>
#include <vector>

inline std::vector<std::string> languages = {
    "English",
    "中文",
    "Deutsch",
    "Italiano",
    "Français",
    "Español",
    "Русский",
    "日本語",
    "한국어"
};

inline std::unordered_map<std::string, std::vector<std::string>> translation = {
    {"Charging", {
        "Charging, ",
        "充电中, ",
        "Wird geladen, ",
        "In carica, ",
        "En charge, ",
        "Cargando, ",
        "Заряжается, ",
        "充電中 ,",
        "충전 중 ,"
    }},
    {"Charged", {
        "% Charged",
        "% 已充电",
        "% Aufgeladen",
        "% Carico",
        "% Chargé",
        "% Cargado",
        "% Заряжено",
        "% 充電済み",
        "% 충전됨"
    }}
};

#endif //LANGUAGES_H
