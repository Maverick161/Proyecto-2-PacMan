cmake_minimum_required(VERSION 3.24)
project(Proyecto-2-PacMan)

set(CMAKE_CXX_STANDARD 17)

add_executable(Proyecto-2-PacMan Main.cpp Ghost.cpp Ghost.hpp GhostManager.cpp GhostManager.hpp ConvertSketch.cpp ConvertSketch.hpp DrawMap.cpp DrawMap.hpp DrawText.cpp DrawText.hpp Global.hpp MapCollision.cpp MapCollision.hpp Pacman.cpp Pacman.hpp)

find_package(SFML 2.5 COMPONENTS graphics window REQUIRED)
target_link_libraries(Proyecto-2-PacMan sfml-graphics sfml-window)