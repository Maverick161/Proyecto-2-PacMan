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

    //para aumentar la dificultad del juego
    wave_timer = static_cast<unsigned short>(LONG_SCATTER_DURATION / pow(2, i_level));

    // Calcula el número de fantasmas basado en el nivel, con un mínimo de 1 y un máximo de 4
    unsigned char numGhosts = min(static_cast<unsigned char>(4), static_cast<unsigned char>(i_level + 1));
    ghosts.clear(); // Borra cualquier fantasma anterior

    for (unsigned char a = 0; a < numGhosts; a++)
    {
        Ghost newGhost(a);
        newGhost.set_position(i_ghost_positions[a].x, i_ghost_positions[a].y);
        ghosts.push_back(newGhost);
    }

    for (Ghost& ghost : ghosts)
    {
        //Usamos el fantasma azul para obtener la ubicación de la casa y el fantasma rojo para obtener la ubicación de la salida
        if (ghosts.size() >= 1) {
            ghost.reset(ghosts[0].get_position(), ghosts[3].get_position());
        }
    }
}

void GhostManager::update(unsigned char i_level, array<array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, Pacman& i_pacman)
{
    //la dificultad no incrementa cuando pacman tiene un poder
    if (0 == i_pacman.get_energizer_timer())
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

            //duracion del incremento de la dificultad
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

void GhostManager::activateGhost(unsigned char index) { // para activar los fantasmas por nivel
    if (index < ghosts.size()){
        ghosts[index].active = true;
    }
   /* // Implementa el operador de comparación para los nodos
    inline bool operator < (const Node& lhs, const Node& rhs) {
        return lhs.fCost < rhs.fCost;
    }

// Implementa la verificación de validez para los nodos
    static bool isValid(int x, int y) {
        // Aquí necesitas implementar la verificación de obstáculos y límites del mapa según tu mundo de juego.
    }

// Implementa la verificación si el nodo es el destino
    static bool isDestination(int x, int y, Node dest) {
        if (x == dest.x && y == dest.y) {
            return true;
        }
        return false;
    }

// cálculo del coste heurístico de un nodo
    static double calculateH(int x, int y, Node dest) {
        double H = (sqrt((x - dest.x)*(x - dest.x) + (y - dest.y)*(y - dest.y)));
        return H;
    }

// Implementa el algoritmo A*
    static std::vector<Node> aStar(Node player, Node dest) {
        // Aquí debería ir la implementación completa del algoritmo A* que proporcionaste en tu código anterior.
    }

// Implementa la creación de un camino desde el inicio hasta el destino
    static std::vector<Node> makePath(std::array<std::array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)> map, Node dest) {
        // Aquí debería ir la implementación completa de makePath que proporcionaste en tu código anterior.
    } */
}