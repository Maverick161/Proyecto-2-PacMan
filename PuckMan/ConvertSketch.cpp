#include <array>
#include <string>
#include <SFML/Graphics.hpp>

#include "Global.hpp"
#include "Pacman.hpp"
#include "ConvertSketch.hpp"

array<array<Cell, MAP_HEIGHT>, MAP_WIDTH> convert_sketch(const array<string, MAP_HEIGHT>& i_map_sketch, array<Position, 4>& i_ghost_positions, Pacman& i_pacman)
{
	array<array<Cell, MAP_HEIGHT>, MAP_WIDTH> output_map{};

	for (unsigned char a = 0; a < MAP_HEIGHT; a++)
	{
		for (unsigned char b = 0; b < MAP_WIDTH; b++)
		{
			//Cada celda esta vacia por default
			output_map[b][a] = Cell::Empty;

			switch (i_map_sketch[a][b])
			{
				//paredes como obstaculo
				case '#':
				{
					output_map[b][a] = Cell::Wall;

					break;
				}
				case '=':
				{
					output_map[b][a] = Cell::Door;

					break;
				}
				case '.':
				{
					output_map[b][a] = Cell::Pellet;

					break;
				}
				//enemigo rojo
				case '0':
				{
					i_ghost_positions[0].x = CELL_SIZE * b;
					i_ghost_positions[0].y = CELL_SIZE * a;

					break;
				}
				//Enemigo Rosado
				case '1':
				{
					i_ghost_positions[1].x = CELL_SIZE * b;
					i_ghost_positions[1].y = CELL_SIZE * a;

					break;
				}
				//Enemigo azul
				case '2':
				{
					i_ghost_positions[2].x = CELL_SIZE * b;
					i_ghost_positions[2].y = CELL_SIZE * a;

					break;
				}
				//Enemigo Naranja
				case '3':
				{
					i_ghost_positions[3].x = CELL_SIZE * b;
					i_ghost_positions[3].y = CELL_SIZE * a;

					break;
				}
				//Personaje PacMan
				case 'P':
				{
					i_pacman.set_position(CELL_SIZE * b, CELL_SIZE * a);

					break;
				}
				//Poder
				case 'o':
				{
					output_map[b][a] = Cell::Energizer;
				}
			}
		}
	}

	return output_map;
}