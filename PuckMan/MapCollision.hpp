#include <iostream>
#pragma once

using namespace std;

//unsigned int puntajePellet;


bool map_collision(bool i_collect_pellets, bool i_use_door, short i_x, short i_y, array<array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map);

class colisionPellet{

public:
    //colisionPellet();

    unsigned int get_scorePellet(); // metodo para obtener el puntaje

};