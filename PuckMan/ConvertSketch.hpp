#pragma once

using namespace sf;
using namespace std;

array<array<Cell, MAP_HEIGHT>, MAP_WIDTH> convert_sketch(const array<string, MAP_HEIGHT>& i_map_sketch, array<Position, 4>& i_ghost_positions, Pacman& i_pacman);