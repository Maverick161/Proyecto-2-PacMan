#include <array>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Global.hpp"
#include "Pacman.hpp"
#include "MapCollision.hpp"
#include "ConvertSketch.hpp"
//#include "contrAndroid.h"

//Controller controller; // instancia de la clase Controler de contrAndroid.cpp

Pacman::Pacman() : // valor de las variables al inicio del juego
    puntaje(0),
    vidas(3),
	animation_over(0),
	dead(0),
	direction(0),
	energizer_timer(0),
    invulnerability_timer(0),
	position({0, 0})

{
}

unsigned int Pacman::get_score() { // metodo para obtener el puntaje de pacman
    return puntaje;
}

unsigned int Pacman::get_vidas(){ // metodo para obtener las vidas de pacman
    return vidas;
}

bool Pacman::get_animation_over() // metodo para obtener la animacion cuando muere pacman
{
	return animation_over;
}

bool Pacman::get_dead() // metodo para obtener cuando muere pacman
{
	return dead;
}

unsigned char Pacman::get_direction() // metodo para obtener la direccion de pacman
{
	return direction;
}

unsigned short Pacman::get_energizer_timer() // metodo para obtener el tiempo mientras pacman tiene un poder
{
	return energizer_timer;
}

void Pacman::draw(bool i_victory, RenderWindow& i_window) // funcion para dibujar en pantalla la animacion
{
	unsigned char frame = static_cast<unsigned char>(floor(animation_timer / static_cast<float>(PACMAN_ANIMATION_SPEED)));

	Sprite sprite;

	Texture texture;

	sprite.setPosition(position.x, position.y);

	if (1 == dead || 1 == i_victory) // animacion para cuando se pierde el juego o se pasa de nivel
	{
		if (animation_timer < PACMAN_DEATH_FRAMES * PACMAN_ANIMATION_SPEED)
		{
			animation_timer++;

			texture.loadFromFile("/home/fernando/Documentos/Proyecto-2-PacMan/PuckMan/Images/PacmanDeath16.png");

			sprite.setTexture(texture);
			sprite.setTextureRect(IntRect(CELL_SIZE * frame, 0, CELL_SIZE, CELL_SIZE));

			i_window.draw(sprite);

		}
		else
		{
			//se terminan las animaciones
			animation_over = 1;
		}
	}
	else
	{    //animaciones mientras pacman este vivo
		texture.loadFromFile("/home/fernando/Documentos/Proyecto-2-PacMan/PuckMan/Images/Pacman16.png");

		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(CELL_SIZE * frame, CELL_SIZE * direction, CELL_SIZE, CELL_SIZE));

		i_window.draw(sprite);

		animation_timer = (1 + animation_timer) % (PACMAN_ANIMATION_FRAMES * PACMAN_ANIMATION_SPEED);//tiempo de animacion en juego

        //controller.SocketServer();

	}
}

void Pacman::reset() // variables iniciales del personaje de pacman para la funcion de reset
{
    puntaje = 0;
    vidas = 3;
	animation_over = 0;
	dead = 0;

	direction = 0;

	animation_timer = 0;
	energizer_timer = 0;
}

void Pacman::set_animation_timer(unsigned short i_animation_timer) // funcion para obtener el tiempo de animacion
{
	animation_timer = i_animation_timer;
}

void Pacman::set_dead(bool i_dead) // funcion para terminar la animacion cuando muere pacman
{
	dead = i_dead;

	if (1 == dead)
	{
		//revisa que la animacion empiece desde 0
		animation_timer = 0;
	}
}

void Pacman::set_position(short i_x, short i_y) // funcion para acceder a la posicion x y y
{
	position = {i_x, i_y};
}

void Pacman::update(unsigned char i_level, array<array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map) // funcion para actualizar lo que pasa en el laberinto
{
    if (invulnerability_timer > 0){
        invulnerability_timer--;
    }

	array<bool, 4> walls{}; // colision entre las paredes
	walls[0] = map_collision(0, 0, PACMAN_SPEED + position.x, position.y, i_map);
	walls[1] = map_collision(0, 0, position.x, position.y - PACMAN_SPEED, i_map);
	walls[2] = map_collision(0, 0, position.x - PACMAN_SPEED, position.y, i_map);
	walls[3] = map_collision(0, 0, position.x, PACMAN_SPEED + position.y, i_map);


	if (1 == Keyboard::isKeyPressed(Keyboard::Right))
	{  // no virar en esta direccion si se encuentra un muro

		if (0 == walls[0])
		{
			direction = 0;
		}
	}

	if (1 == Keyboard::isKeyPressed(Keyboard::Up))
	{
		if (0 == walls[1])
		{
			direction = 1;
		}
	}

	if (1 == Keyboard::isKeyPressed(Keyboard::Left))
	{
		if (0 == walls[2])
		{
			direction = 2;
		}
	}

	if (1 == Keyboard::isKeyPressed(Keyboard::Down))
	{
		if (0 == walls[3])
		{
			direction = 3;
		}
	}

	if (0 == walls[direction]) // si se mueve hacia una direccion en la cual no hay muros, el movimiento es valido
	{
		switch (direction)
		{
			case 0:
			{
				position.x += PACMAN_SPEED;

				break;
			}
			case 1:
			{
				position.y -= PACMAN_SPEED;

				break;
			}
			case 2:
			{
				position.x -= PACMAN_SPEED;

				break;
			}
			case 3:
			{
				position.y += PACMAN_SPEED;
			}
		}
	}

	if (-CELL_SIZE >= position.x) // movimiento en el eje x
	{
		position.x = CELL_SIZE * MAP_WIDTH - PACMAN_SPEED;
	}
	else if (CELL_SIZE * MAP_WIDTH <= position.x)
	{
		position.x = PACMAN_SPEED - CELL_SIZE;
	}

	if (1 == map_collision(1, 0, position.x, position.y, i_map)) //cuando pacman come un poder
	{
		energizer_timer = static_cast<unsigned short>(ENERGIZER_DURATION / pow(2, i_level));

        puntaje += 10; //  puntaje de cuando pacman come un poder

        //if (intocable_timer==0){ //pacman pierde una vida cuando no esta vulnerable
          //  loseLife();
        //}
	}

	else
	{
		energizer_timer = max(0, energizer_timer - 1); // cuando termina el tiempo del poder
	}
}

Position Pacman::get_position() // accede a la posicion de pacman
{
	return position;
}

//Esta es la implementación de Pacman::loseLife
// Modificación de la función loseLife para aceptar el mapa del juego como un argumento
void Pacman::loseLife(const array<array<Cell, MAP_HEIGHT>, MAP_WIDTH>& game_map) {
    // Verifica si el temporizador de invulnerabilidad está activo
    if(invulnerability_timer == 0) {
        // Si no está activo, reduce la vida de Pacman
        vidas--;

        // Activa el temporizador de invulnerabilidad
        invulnerability_timer = INVULNERABILITY_TIME;

        // Verifica si Pacman se ha quedado sin vidas
        if(vidas <= 0) {
            // Si Pacman se ha quedado sin vidas, marca a Pacman como muerto
            set_dead(1);
        } else {
            // Si Pacman todavía tiene vidas, genera una nueva posición aleatoria que no sea una pared
            short new_x, new_y;
            do {
                new_x = rand() % MAP_WIDTH;
                new_y = rand() % MAP_HEIGHT;
            } while(game_map[new_x][new_y] == Cell::Wall);

            // Establece la posición de Pacman a la nueva posición aleatoria
            set_position(new_x * CELL_SIZE, new_y * CELL_SIZE);
        }
    }
}