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

// El tamano de la pantalla es de 336x352

int main()
{
    //para saber si se gana el juego
    bool game_won = 0;

    //juego independiente de los fps
    unsigned lag = 0;

    // variable para el nivel en pantalla
    unsigned char level = 0;

    //juego independiente de la velocidad de los fps
    chrono::time_point<chrono::steady_clock> previous_time;

    //mapa manejado con vectores
    array<string, MAP_HEIGHT> map_sketch = {
            " ################### ",
            " #........#........# ",
            " #o##.###.#.###.##o# ",
            " #.................# ",
            " #.##.#.#####.#.##.# ",
            " #....#...#...#....# ",
            " ####.###.#.###.#### ",
            "    #.#.......#.#    ",
            "#####.# ##### #.#####",
            ".........0123........",
            "#####.# ##### #.#####",
            "    #.#.......#.#    ",
            " ####.# ##### #.#### ",
            " #........#........# ",
            " #.##.###.#.###.##.# ",
            " #o.#.....P.....#.o# ",
            " ##.#.#.#####.#.#.## ",
            " #....#...#...#....# ",
            " #.######.#.######.# ",
            " #.................# ",
            " ################### " // 21 filas x 21 columnas
    };

    // crea un mapa del juego de tamaño MAP_WIDTH x MAP_HEIGHT, donde cada celda está inicializada utilizando el constructor por defecto de la clase o enumeración Cell.
    array<array<Cell, MAP_HEIGHT>, MAP_WIDTH> map{};

    //posicion inicial de los fantasmas
    array<Position, 4> ghost_positions;

    //Palabra de SFML guarda los eventos
    Event event;

    // Crea la ventana de acuerdo al laberinto
    RenderWindow window(VideoMode(CELL_SIZE * MAP_WIDTH * SCREEN_RESIZE, (FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT) * SCREEN_RESIZE), "PuckMan", Style::Close);

    //tamano de la pantalla
    window.setView(View(FloatRect(0, 0, CELL_SIZE * MAP_WIDTH, FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT)));

    GhostManager ghost_manager; // instancia de la clase GhostManager de su .cpp

    Pacman pacman; // instancia de la clase Pacman de su .cpp

    colisionGhosts colisionghosts; // instancia de la clase colisionGhosts de Ghosts.cpp

    colisionPellet colisionpellet;  // instancia de la clase colisionPellet de MapCollision.cpp

    //se genera la semilla para el random del juego
    srand(static_cast<unsigned>(time(0))); //random del juego

    map = convert_sketch(map_sketch, ghost_positions, pacman); // posiciones en el mapa

    ghost_manager.reset(level, ghost_positions); // reset del nivel y la posicion de los fantasmas

    //obtiene el tiempo real y lo almacena en una variable
    previous_time = chrono::steady_clock::now();

    while (1 == window.isOpen())
    {
        //calculo del lag en el juego
        unsigned delta_time = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - previous_time).count();

        lag += delta_time;

        previous_time += chrono::microseconds(delta_time);

        // bucle cuando el lag se pasa del maximo permitido durante los frames del juego
        while (FRAME_DURATION <= lag)
        {
            //se reduce el lag
            lag -= FRAME_DURATION;

            while (1 == window.pollEvent(event))
            {
                switch (event.type)
                {
                    case Event::Closed: // para cerrar la ventana
                    {
                        window.close();
                    }
                }
            }

            if (0 == game_won && 0 == pacman.get_dead())
            {
                game_won = 1;

                pacman.update(level, map);

                ghost_manager.update(level, map, pacman);

                //revisa cada celda en el mapa
                for (const array<Cell, MAP_HEIGHT>& column : map)
                {
                    for (const Cell& cell : column)
                    {
                        if (Cell::Pellet == cell) // se queda puntos en el laberinto
                        {
                            game_won = 0; //el jugador no ha ganado el juego

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
            else if (1 == Keyboard::isKeyPressed(Keyboard::Enter)) //reinicia el juego con la tecla de enter
            {
                game_won = 0;

                if (1 == pacman.get_dead())
                {
                    level = 0;
                }
                else
                {
                    //despues de ganar cada nivel, se reduce la duracion de las olas de ataque y poderes
                    level++;

                    for (unsigned char i = 0; i < level && i < 4; ++i){
                        ghost_manager.activateGhost(i);
                    }
                }

                map = convert_sketch(map_sketch, ghost_positions, pacman);

                ghost_manager.reset(level, ghost_positions);

                pacman.reset();
            }

            if (FRAME_DURATION > lag)
            {
                window.clear();

                if (0 == game_won && 0 == pacman.get_dead()) // mientras el juego siga corriendo, aparece en pantalla
                {
                    draw_map(map, window);

                    ghost_manager.draw(GHOST_FLASH_START >= pacman.get_energizer_timer(), window);

                    draw_text(0, 0, CELL_SIZE * MAP_HEIGHT, "Nivel: " + to_string(1 + level), window); // label de nivel actual

                    draw_text(0, 110, CELL_SIZE * MAP_HEIGHT, "Puntos: " + to_string(pacman.get_score() + colisionpellet.get_scorePellet() + colisionghosts.get_scoreGhost()), window); // label de puntos que se van obteniendo

                    draw_text(0, 220, CELL_SIZE * MAP_HEIGHT, "Vida: " + to_string(pacman.get_vidas()), window); // label de vidas actuales

                }

                pacman.draw(game_won, window);

                if (1 == pacman.get_animation_over()) // si pacman gana, pasa al siguiente nivel
                {
                    if (1 == game_won)
                    {
                        draw_text(1, 0, 0, "Siguiente nivel", window); // pausa para el siguiente nivel
                        draw_text(0, 120, 200, "Puntos: " + to_string(pacman.get_score() + colisionpellet.get_scorePellet() + colisionghosts.get_scoreGhost()), window); // label de puntos que se van obteniendo
                        draw_text(0, 55, 300, "Presione enter para continuar", window); // pausa para el siguiente nivel


                    }
                    else
                    {
                        draw_text(1, 0, 0, "Juego Perdido", window); // pausa cuando se acaban las vidas de pacman
                        draw_text(0, 120, 200, "Puntos: " + to_string(pacman.get_score() + colisionpellet.get_scorePellet() + colisionghosts.get_scoreGhost()), window); // label de puntos que se van obteniendo
                        draw_text(0, 55, 300, "Presione enter para continuar", window); // pausa para el siguiente nivel

                    }
                }
                window.display();
            }
        }
    }
}
