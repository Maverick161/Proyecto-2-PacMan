cmake_minimum_required(VERSION 3.24)
project(PuckMan)

set(CMAKE_CXX_STANDARD 17)

add_executable(PuckMan main.cpp Menu.cpp Menu.h Facil.cpp Facil.h Medio.cpp Medio.h Dificil.cpp Dificil.h Experto.cpp Experto.h)

find_package(SFML 2.5 COMPONENTS graphics window REQUIRED)
target_link_libraries(PuckMan sfml-graphics sfml-window)