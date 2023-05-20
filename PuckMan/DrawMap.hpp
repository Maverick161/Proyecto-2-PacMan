#include <iostream>
#pragma once

using namespace sf;
using namespace std;

/*
 * Funcion draw_map con dos parametros:
 * matriz de dos dimensiones i_map
 * referencia al objeto de RenderWindow para dibujar el mapa en la pantalla i_window
 */

void draw_map(const array<array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, RenderWindow& i_window);