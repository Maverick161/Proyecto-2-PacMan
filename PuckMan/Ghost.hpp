#pragma once

using namespace std;

class Ghost
{

	bool movement_mode;
	bool use_door;

	unsigned char direction;
	unsigned char frightened_mode;

	//Timer para mover a los fantasmas lento
	unsigned char frightened_speed_timer;

	unsigned char id; // 1 rojo, 2 rosado, 3 azul, 4 naranja

	unsigned short animation_timer;

	//cuando se escape se va a home el fantasma
	Position home;

	//para que salga del home
	Position home_exit;

	//posicion actual
	Position position;

	//target actual
	Position target;
public:
	Ghost(unsigned char i_id);

	bool pacman_collision(const Position& i_pacman_position);

	float get_target_distance(unsigned char i_direction);

	void draw(bool i_flash, RenderWindow& i_window);
	void reset(const Position& i_home, const Position& i_home_exit);
	void set_position(short i_x, short i_y);
	void switch_mode();
	void update(unsigned char i_level, array<array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, Ghost& i_ghost_0, Pacman& i_pacman);
	void update_target(unsigned char i_pacman_direction, const Position& i_ghost_0_position, const Position& i_pacman_position);

	Position get_position();
};