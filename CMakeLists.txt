cmake_minimum_required(VERSION 3.16)
project(PhonePhone CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# main.cpp is C++ (Qt wrapper)
add_executable(PhonePhone
        Src/main.cpp
        Src/time.cpp
        Src/wallpaper.cpp
        Src/pin.cpp
        Src/screens/lockscreen.cpp
        Src/screens/setupScreen.cpp
        Src/styleManager.cpp
        Src/systemInfo.cpp
        Src/shapes.cpp
        Src/commonElements.cpp
        include/screens/lockscreen.h
        include/screens/setupScreen.h
)

target_link_libraries(PhonePhone
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        wlanapi
)
