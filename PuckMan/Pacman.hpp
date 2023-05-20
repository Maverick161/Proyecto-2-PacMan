#pragma once
#include <iostream>
#include "Global.hpp"

using namespace sf;
using namespace std;

class Pacman
{
	bool animation_over; // para revisar si la animacion de pacman ha terminado
	bool dead; // para revisar cuando muere pacman

	unsigned char direction; // variable para la direccion

    unsigned int puntaje; // variable para el puntaje cuando colecta un power

    unsigned int vidas; // variable para almacenar las vidas

	//timers de animacion, poder y vulnerabilidad
	unsigned short animation_timer;
	unsigned short energizer_timer;
    //unsigned short intocable_timer;

	// estructura para la posicion de pacman
	Position position;

public:
	Pacman(); // declaracion del constructor de pacman

	bool get_animation_over(); // obtiene animacion de cuando pacman muere
	bool get_dead(); // obtiene el booleano de cuando pacman muere

	unsigned char get_direction(); // metodo que obtiene la direccion de pacman

	unsigned short get_energizer_timer(); // metodo para el timer de cuando pacman adquiere un poder

    //short randomX, randomY;// posiciones random cada vez que muere

    // Generar una semilla única basada en el tiempo actual
    unsigned int seed = static_cast<unsigned int>(time(0));

	void draw(bool i_victory, RenderWindow& i_window); // funcion para renderizar el objeto
	void reset(); // reiniciar las variables del juego
	void set_animation_timer(unsigned short i_animation_timer); //  animacion del juego cuando hay un poder en pacman
	void set_dead(bool i_dead); // verificar la muerte del jugador
	void set_position(short i_x, short i_y); //verificar la posicion del jugador
	void update(unsigned char i_level, array<array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map); // actualizar las variables del juego
    void loseLife(); // verificar cuando se pierde una vida

	Position get_position(); // estructura para la posicion de pacman en el juego

    unsigned int get_score(); // metodo para obtener el puntaje

    unsigned int get_vidas(); // metodo para obtener las vidas de pacman
};