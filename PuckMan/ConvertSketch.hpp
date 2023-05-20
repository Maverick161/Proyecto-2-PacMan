#pragma once

using namespace sf;
using namespace std;

/*
 * Declaracion de Convert_Sketch con tres parametros:
 * matriz de cadenas del mapa i_map_sketch
 * matriz de posiciones de los fantasmas i_ghost position
 * referencia al objeto de la clase pacman i_pacman
 */

array<array<Cell, MAP_HEIGHT>, MAP_WIDTH> convert_sketch(const array<string, MAP_HEIGHT>& i_map_sketch, array<Position, 4>& i_ghost_positions, Pacman& i_pacman);