#pragma once

using namespace sf;
using namespace std;

void draw_map(const array<array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, RenderWindow& i_window);