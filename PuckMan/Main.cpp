#include <array>
#include <chrono>
#include <ctime>
#include <SFML/Graphics.hpp>

#include "Global.hpp"
#include "DrawText.hpp"
#include "Pacman.hpp"
#include "Ghost.hpp"
#include "GhostManager.hpp"
#include "ConvertSketch.hpp"
#include "DrawMap.hpp"
#include "MapCollision.hpp"

using namespace sf;
using namespace std;

int main()
{
	//Is the game won?
	bool game_won = 0;

	//Used to make the game framerate-independent.
	unsigned lag = 0;

	unsigned char level = 0;

    //extern int puntaje;

	//Similar to lag, used to make the game framerate-independent.
	chrono::time_point<chrono::steady_clock> previous_time;

	//It's not exactly like the map from the original Pac-Man game, but it's close enough.
	array<string, MAP_HEIGHT> map_sketch = {
		" ################### ",
		" #........#........# ",
		" #o##.###.#.###.##o# ",
		" #.................# ",
		" #.##.#.#####.#.##.# ",
		" #....#...#...#....# ",
		" ####.### # ###.#### ",
		"    #.#   0   #.#    ",
		"#####.# ##=## #.#####",
		"     .  #123#  .     ",
		"#####.# ##### #.#####",
		"    #.#       #.#    ",
		" ####.# ##### #.#### ",
		" #........#........# ",
		" #.##.###.#.###.##.# ",
		" #o.#.....P.....#.o# ",
		" ##.#.#.#####.#.#.## ",
		" #....#...#...#....# ",
		" #.######.#.######.# ",
		" #.................# ",
		" ################### "
	};

	array<array<Cell, MAP_HEIGHT>, MAP_WIDTH> map{};

	//Initial ghost positions.
	array<Position, 4> ghost_positions;

	//SFML thing. Stores events, I think.
	Event event;

	RenderWindow window(VideoMode(CELL_SIZE * MAP_WIDTH * SCREEN_RESIZE, (FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT) * SCREEN_RESIZE), "Pac-Man", Style::Close);
	//Resizing the window.
	window.setView(View(FloatRect(0, 0, CELL_SIZE * MAP_WIDTH, FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT)));

	GhostManager ghost_manager;

	Pacman pacman;

	//Generating a random seed.
	srand(static_cast<unsigned>(time(0)));

	map = convert_sketch(map_sketch, ghost_positions, pacman);

	ghost_manager.reset(level, ghost_positions);

	//Get the current time and store it in a variable.
	previous_time = chrono::steady_clock::now();

	while (1 == window.isOpen())
	{
		//Here we're calculating the lag.
		unsigned delta_time = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - previous_time).count();

		lag += delta_time;

		previous_time += chrono::microseconds(delta_time);

		//While the lag exceeds the maximum allowed frame duration.
		while (FRAME_DURATION <= lag)
		{
			//We decrease the lag.
			lag -= FRAME_DURATION;

			while (1 == window.pollEvent(event))
			{
				switch (event.type)
				{
					case Event::Closed:
					{
						//Making sure the player can close the window.
						window.close();
					}
				}
			}

			if (0 == game_won && 0 == pacman.get_dead())
			{
				game_won = 1;

				pacman.update(level, map);

				ghost_manager.update(level, map, pacman);

				//We're checking every cell in the map.
				for (const array<Cell, MAP_HEIGHT>& column : map)
				{
					for (const Cell& cell : column)
					{
						if (Cell::Pellet == cell) //And if at least one of them has a pellet.
						{
							game_won = 0; //The game is not yet won.

							break;
						}
					}

					if (0 == game_won)
					{
						break;
					}
				}

				if (1 == game_won)
				{
					pacman.set_animation_timer(0);
				}
			}
			else if (1 == Keyboard::isKeyPressed(Keyboard::Enter)) //Restarting the game.
			{
				game_won = 0;

				if (1 == pacman.get_dead())
				{
					level = 0;
				}
				else
				{
					//After each win we reduce the duration of attack waves and energizers.
					level++;
				}

				map = convert_sketch(map_sketch, ghost_positions, pacman);

				ghost_manager.reset(level, ghost_positions);

				pacman.reset();
			}

			//I don't think anything needs to be explained here.
			if (FRAME_DURATION > lag)
			{
				window.clear();


				if (0 == game_won && 0 == pacman.get_dead())
				{
					draw_map(map, window);

					ghost_manager.draw(GHOST_FLASH_START >= pacman.get_energizer_timer(), window);

					draw_text(false, 0, CELL_SIZE * MAP_HEIGHT, "Nivel: " + to_string(1 + level), window);

                    //draw_text(false, 80, CELL_SIZE * MAP_HEIGHT, "Puntos: "+ to_string(puntaje), window);

                }

				pacman.draw(game_won, window);

				if (1 == pacman.get_animation_over())
				{
					if (1 == game_won)
					{
						draw_text(1, 0, 0, "Next!", window);
					}
					else
					{
						draw_text(1, 0, 0, "Game over", window);
					}
				}

				window.display();
			}
		}
	}
}