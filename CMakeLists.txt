cmake_minimum_required(VERSION 3.15)
project(PhonePhone VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



add_executable(PhonePhone main.cpp
	kernel/src/permissions.cpp
)

target_include_directories(PhonePhone PRIVATE kernel/include)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
