#include <array>
#include <cmath>

#include "Global.hpp"
#include "MapCollision.hpp"

unsigned int puntajePellet;

bool map_collision(bool i_collect_pellets, bool i_use_door, short i_x, short i_y, array<array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map)
{
	bool output = 0;

	//obtiene la posicion exacta en cada celda para el eje x y y
	float cell_x = i_x / static_cast<float>(CELL_SIZE);
	float cell_y = i_y / static_cast<float>(CELL_SIZE);

	//permite que pacman o un fantasma este solo entre 4 celdas
	for (unsigned char a = 0; a < 4; a++)
	{
		short x = 0;
		short y = 0;

		switch (a)
		{
			case 0: //celda izquierda superior
			{
				x = static_cast<short>(floor(cell_x));
				y = static_cast<short>(floor(cell_y));

				break;
			}
			case 1: //celda derecha superior
			{
				x = static_cast<short>(ceil(cell_x));
				y = static_cast<short>(floor(cell_y));

				break;
			}
			case 2: //celda izquierda inferior
			{
				x = static_cast<short>(floor(cell_x));
				y = static_cast<short>(ceil(cell_y));

				break;
			}
			case 3: //celda derecha inferior
			{
				x = static_cast<short>(ceil(cell_x));
				y = static_cast<short>(ceil(cell_y));
			}
		}

		//funcion para asegurarse de que la posicion sea dentro del mapa
		if (0 <= x && 0 <= y && MAP_HEIGHT > y && MAP_WIDTH > x)
		{
			if (0 == i_collect_pellets) // para invalidar el movimiento hacia las paredes o puerta
			{
                if (Cell::Wall == i_map[x][y])
				{
					output = 1;
				}
				else if (0 == i_use_door && Cell::Door == i_map[x][y])
				{
					output = 1;
				}
			}
			else //cuando hay colision entre el poder o los puntos del mapa
			{
				if (Cell::Energizer == i_map[x][y])
				{
					output = 1;

					i_map[x][y] = Cell::Empty;
				}
				else if (Cell::Pellet == i_map[x][y])
				{
					i_map[x][y] = Cell::Empty;
                    puntajePellet+=10;
                    //cout << "El valor de puntaje es: " << puntajePellet << std::endl;
                }
			}
		}
	}

	return output; // devuelve las funciones
}

unsigned int colisionPellet::get_scorePellet() { // metodo para retornar el puntaje cuando colisiona con un punto del laberinto
    return puntajePellet;
}