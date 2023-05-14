#include <array>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Global.hpp"
#include "Pacman.hpp"
#include "Ghost.hpp"
#include "GhostManager.hpp"

GhostManager::GhostManager() :
	current_wave(0),
	wave_timer(LONG_SCATTER_DURATION),
	ghosts({Ghost(0), Ghost(1), Ghost(2), Ghost(3)})
{

}
void GhostManager::setLevel(unsigned char level)
{
    current_level = level;
}
void GhostManager::draw(bool i_flash, RenderWindow& i_window)
{
    // Only draw the ghosts that are active in the current level
    for (unsigned char a = 0; a < current_level && a < ghosts.size(); a++)
    {
        ghosts[a].draw(i_flash, i_window);
    }
}

void GhostManager::reset(unsigned char i_level, const std::array<Position, 4>& i_ghost_positions)
{
    //current_level = i_level;
    current_wave = 0;
    wave_timer = static_cast<unsigned short>(LONG_SCATTER_DURATION / pow(2, i_level));

    // Only reset positions for the ghosts that are active in the current level
    for (unsigned char a = 0; a < i_level && a < ghosts.size(); a++)
    {
        ghosts[a].set_position(i_ghost_positions[a].x, i_ghost_positions[a].y);
    }

    //for (unsigned char a = 0; a < i_level && a < ghosts.size(); a++)
    //{
        //ghosts[a].reset(ghosts[2].get_position(), ghosts[0].get_position());
    //}
}

void GhostManager::update(unsigned char i_level, array<array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, Pacman& i_pacman)
{
	if (0 == i_pacman.get_energizer_timer()) //We won't update the wave timer when Pacman is energized.
	{
		if (0 == wave_timer)
		{
			if (7 > current_wave)
			{
				current_wave++;

                for(unsigned char a=0;a<=i_level&&a<ghosts.size();a++){
                    ghosts[a].switch_mode();
                    //ghosts[a].update(i_level,i_map,ghosts[0],i_pacman);
                }

				//for (Ghost& ghost : ghosts)
				//{
				//	ghost.switch_mode();
				//}
			}

			//I took the rules from the website.
			if (1 == current_wave % 2)
			{
				wave_timer = CHASE_DURATION;
			}
			else if (2 == current_wave)
			{
				wave_timer = static_cast<unsigned short>(LONG_SCATTER_DURATION / pow(2, i_level));
			}
			else
			{
				wave_timer = static_cast<unsigned short>(SHORT_SCATTER_DURATION / pow(2, i_level));
			}
		}
		else
		{
			wave_timer--;
		}
	}
    for (unsigned char a=0;a<i_level && a<ghosts.size();a++){
        ghosts[a].update(i_level, i_map, ghosts[0],i_pacman);
    }

	for (Ghost& ghost : ghosts)
	{
		ghost.update(i_level, i_map, ghosts[0], i_pacman);
	}

}