#pragma once
#include <set>

using namespace sf;
using namespace std;

//estructura del nodo que se va a utilizar en el algoritmo A*
/*struct Node
{
    int y;
    int x;
    int parentX;
    int parentY;
    float gCost;
    float hCost;
    float fCost;
};*/

class GhostManager
{
    // control de la dificultad del juego
    unsigned char current_wave;

    //timer para controlar la dificultad del juego
    unsigned short wave_timer;

    // ghosts como vector de la clase Ghost
    vector<Ghost> ghosts;

    /*inline bool operator < (const Node& lhs, const Node& rhs); // Operador de comparación para usar un Node en un set

    static bool isValid(int x, int y); // Verificar si el nodo es válido
    static bool isDestination(int x, int y, Node dest); // Verificar si el nodo es el destino
    static double calculateH(int x, int y, Node dest); // Calcular el coste heurístico de un nodo
    static std::vector<Node> aStar(Node player, Node dest); // Implementación del algoritmo A*
    static std::vector<Node> makePath(std::array<std::array<Node, (Y_MAX / Y_STEP)>, (X_MAX / X_STEP)> map, Node dest); // Crear un camino desde el inicio hasta el destino
*/
public:
    GhostManager(); //declaracion del constructor del juego
    void draw(bool i_flash, RenderWindow& i_window); // declaracion de la funcion con los parametros que renderiza en pantalla
    void reset(unsigned char i_level, const array<Position, 4>& i_ghost_positions); // declaracion de reinicio que recibe parametros para el nivel y posiciones de fantasmas
    void update(unsigned char i_level, array<array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, Pacman& i_pacman); // declaracion para actualizar que recibe parametros con el nivel, mapa y pacman
    void activateGhost(unsigned char index); // para activar los fantasmas por nivel
};