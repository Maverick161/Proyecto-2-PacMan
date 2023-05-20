#include <array>
#include <SFML/Graphics.hpp>

#include "Global.hpp"
#include "DrawMap.hpp"
#include "Pacman.hpp"
#include "Ghost.hpp"
#include "MapCollision.hpp"

Pacman pacman; // instancia de la clase Pacman de su .cpp

colisionGhosts colisionghosts; // instancia de la clase colisionGhosts de Ghosts.cpp

colisionPellet colisionpellet;  // instancia de la clase colisionPellet de MapCollision.cpp

void draw_map(const array<array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, RenderWindow& i_window)
{
	sf::Sprite sprite;

	sf::Texture texture;
	texture.loadFromFile("/home/fernando/Documentos/Proyecto-2-PacMan/PuckMan/Images/Map16.png");

	sprite.setTexture(texture);

	for (unsigned char a = 0; a < MAP_WIDTH; a++)
	{
		for (unsigned char b = 0; b < MAP_HEIGHT; b++)
		{
			sprite.setPosition(static_cast<float>(CELL_SIZE * a), static_cast<float>(CELL_SIZE * b));

			switch (i_map[a][b])
			{
				case Cell::Door: // puerta de la celda de los fantasmas
				{
					sprite.setTextureRect(sf::IntRect(2 * CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_SIZE));

					i_window.draw(sprite);

					break;
				}
				case Cell::Energizer: // poder
				{
                    if ((pacman.get_score() + colisionpellet.get_scorePellet() + colisionghosts.get_scoreGhost())>=200){
                        sprite.setTextureRect(IntRect(CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_SIZE));

                        i_window.draw(sprite);

                        //break;
                    }

					//break;
				}
				case Cell::Pellet: // puntos del laberinto
				{
					sprite.setTextureRect(IntRect(0, CELL_SIZE, CELL_SIZE, CELL_SIZE));

					i_window.draw(sprite);

					break;
				}
				case Cell::Wall: // paredes del laberinto
				{
					bool down = 0;
					bool left = 0;
					bool right = 0;
					bool up = 0;

					if (b < MAP_HEIGHT - 1)
					{
						if (Cell::Wall == i_map[a][1 + b])
						{
							down = 1;
						}
					}

					//conectar y dibujar tuneles
					if (0 < a)
					{
						if (Cell::Wall == i_map[a - 1][b])
						{
							left = 1;
						}
					}
					else
					{
						left = 1;
					}

					if (a < MAP_WIDTH - 1)
					{
						if (Cell::Wall == i_map[1 + a][b])
						{
							right = 1;
						}
					}
					else
					{
						right = 1;
					}

					if (0 < b)
					{
						if (Cell::Wall == i_map[a][b - 1])
						{
							up = 1;
						}
					}

					//Distribucion de las celdas
					sprite.setTextureRect(sf::IntRect(CELL_SIZE * (down + 2 * (left + 2 * (right + 2 * up))), 0, CELL_SIZE, CELL_SIZE));

					i_window.draw(sprite);
				}
			}
		}
	}
}