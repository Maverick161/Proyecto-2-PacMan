#include <array>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Global.hpp"
#include "Pacman.hpp"
#include "Ghost.hpp"
#include "GhostManager.hpp"

GhostManager::GhostManager() :
        current_wave(0),
        wave_timer(LONG_SCATTER_DURATION)
{

}

void GhostManager::draw(bool i_flash, RenderWindow& i_window)
{
    for (Ghost& ghost : ghosts)
    {
        ghost.draw(i_flash, i_window);
    }
}

void GhostManager::reset(unsigned char i_level, const std::array<Position, 4>& i_ghost_positions)
{
    current_wave = 0;
    wave_timer = static_cast<unsigned short>(LONG_SCATTER_DURATION / pow(2, i_level));

    // Calcula el número de fantasmas basado en el nivel, con un mínimo de 1 y un máximo de 4.
    unsigned char numGhosts = std::min(static_cast<unsigned char>(4), static_cast<unsigned char>(i_level + 1));
    ghosts.clear(); // Borra cualquier fantasma anterior.

    for (unsigned char a = 0; a < numGhosts; a++)
    {
        Ghost newGhost(a);
        newGhost.set_position(i_ghost_positions[a].x, i_ghost_positions[a].y);
        ghosts.push_back(newGhost);
    }

    for (Ghost& ghost : ghosts)
    {
        //Usamos el fantasma azul para obtener la ubicación de la casa y el fantasma rojo para obtener la ubicación de la salida.
        // Necesitamos asegurarnos de que hay al menos 3 fantasmas antes de hacer esto.
        if (ghosts.size() >= 3) {
            ghost.reset(ghosts[2].get_position(), ghosts[0].get_position());
        }
    }
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

                for (Ghost& ghost : ghosts)
                {
                    ghost.switch_mode();
                }
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

    for (Ghost& ghost : ghosts)
    {
        ghost.update(i_level, i_map, ghosts[0], i_pacman);
    }
}