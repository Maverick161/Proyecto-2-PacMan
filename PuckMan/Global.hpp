#pragma once

using namespace std;

constexpr unsigned char CELL_SIZE = 16;

constexpr unsigned char FONT_HEIGHT = 16;

//distancia de celdas que busca el fantasma rosado desde pacman
constexpr unsigned char GHOST_1_CHASE = 2;

//distancia de celdas que busca el fantasma azul desde pacman
constexpr unsigned char GHOST_2_CHASE = 1;

//Si la distancia entre el fantasma naranja y Pacman es menor que este valor, el fantasma naranja entrará en el modo de dispersión
constexpr unsigned char GHOST_3_CHASE = 4;

//fps en la animacion de los fantasmas
constexpr unsigned char GHOST_ANIMATION_FRAMES = 6;

//fps en la rapidez de los fantasmas
constexpr unsigned char GHOST_ANIMATION_SPEED = 4;

//La velocidad del fantasma después de que Pacman lo toque mientras está energizado
constexpr unsigned char GHOST_ESCAPE_SPEED = 4;

//entre mas alto el valor, mas lento el movimiento
constexpr unsigned char GHOST_FRIGHTENED_SPEED = 3;
constexpr unsigned char GHOST_SPEED = 1;

constexpr unsigned char MAP_HEIGHT = 21; // columnas del laberinto
constexpr unsigned char MAP_WIDTH = 21; // filas del laberinto


constexpr unsigned char PACMAN_ANIMATION_FRAMES = 6; //fps de la animacion de pacman
constexpr unsigned char PACMAN_ANIMATION_SPEED = 4; //fps de la velocidad de pacman
constexpr unsigned char PACMAN_DEATH_FRAMES = 12; // fps de la muerte de pacman
constexpr unsigned char PACMAN_SPEED = 2; // velocidad de pacman
constexpr unsigned char SCREEN_RESIZE = 2; // resizing de la pantalla

//fps de duraciones
constexpr unsigned short CHASE_DURATION = 1024;
constexpr unsigned short ENERGIZER_DURATION = 512;
constexpr unsigned short FRAME_DURATION = 16667;
constexpr unsigned short GHOST_FLASH_START = 64;
constexpr unsigned short LONG_SCATTER_DURATION = 512;
constexpr unsigned short SHORT_SCATTER_DURATION = 256;

enum Cell
{
    //tipos de objetos de la celda
	Door,
	Empty,
	Energizer,
	Pellet,
	Wall
};

struct Position //estructura de datos para la posicion X y Y
{
	short x;
	short y;

	bool operator==(const Position& i_position)
	{
		return this->x == i_position.x && this->y == i_position.y;
	}
};