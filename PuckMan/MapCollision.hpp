#include <iostream>
#pragma once

using namespace std;

/*
 * Declaracion de la funcion map_collision con 7 parametros:
 * booleano para revisar si se colectan los pellets en la pantalla i_collect_pellets
 * booleano para revisar si se utiliza la puerta del mapa i_use_door
 * enteros cortos con las coordenadas en el mapa i_x i_y
 * referencia a la matriz bidimensional i_map
 * altura y ancho de la matriz MAP_HEIGHT y MAP_WIDTH
 */
bool map_collision(bool i_collect_pellets, bool i_use_door, short i_x, short i_y, array<array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map);

class colisionPellet{

public:
    unsigned int get_scorePellet(); // metodo para obtener el puntaje

};