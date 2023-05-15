#pragma once
#include <iostream>

using namespace sf;
using namespace std;

class Pacman
{
	//This is used for the death animation.
	bool animation_over;
	bool dead;

	unsigned char direction; // variable para la direccion

    unsigned int puntaje; // variable para el puntaje cuando colecta un power

    unsigned int vidas; // variable para almacenar las vidas

	//timers
	unsigned short animation_timer;
	unsigned short energizer_timer;

	//Current location of this creature, commonly known as Pacman.
	Position position;

public:
	Pacman();

	bool get_animation_over(); // obtiene animacion de cuando pacman muere
	bool get_dead(); // obtiene el booleano de cuando pacman muere

	unsigned char get_direction(); // metodo que obtiene la direccion de pacman

	unsigned short get_energizer_timer(); // metodo para el timer de cuando pacman adquiere un poder

	void draw(bool i_victory, RenderWindow& i_window); // metodo para renderizar el objeto
	void reset(); // reiniciar las variables del juego
	void set_animation_timer(unsigned short i_animation_timer); // metodo para la animacion del juego cuando hay un poder en pacman
	void set_dead(bool i_dead); // metodo para verificar la muerte del jugador
	void set_position(short i_x, short i_y); // metodo para verificar la posicion del jugador
	void update(unsigned char i_level, array<array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map); // metodo para actualizar las variables del juego
    void loseLife();

	Position get_position(); // estructura para la posicion de pacman en el juego

    unsigned int get_score(); // metodo para obtener el puntaje

    unsigned int get_vidas(); // metodo para obtener las vidas de pacman
};