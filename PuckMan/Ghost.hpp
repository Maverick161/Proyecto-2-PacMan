#pragma once

using namespace std;

class Ghost
{
    bool movement_mode; // bool para confirmar el movimiento del fantasma
    bool use_door; // para confirmar cuando los fantasmas salen del home

    unsigned char direction; // variable para almacenar la direccion de los fantasmas
    unsigned char frightened_mode; // variable para almacenar cuando estan en modo susto y pacman con un poder

    //Timer para mover a los fantasmas lento
    unsigned char frightened_speed_timer;

    unsigned char id; // variable para la identidad de los fantasmas: 1 rojo, 2 rosado, 3 azul, 4 naranja

    unsigned short animation_timer; // timer para mover la animacion de los fantasmas

    //cuando se escape se va a home el fantasma
    Position home;

    //para que salga del home
    Position home_exit;

    //posicion actual
    Position position;

    //target actual
    Position target;
public:

    Ghost(unsigned char i_id); // declaracion del constructor con el paramatero de la identidad para cada fantasma

    bool pacman_collision(const Position& i_pacman_position); // declaracion de la colision con el pacman que recibe como parametro la direccion de pacman

    bool active; //para activar los fantasmas por nivel

    float get_target_distance(unsigned char i_direction); // declaracion que obtiene como parametro una direccion final

    void draw(bool i_flash, RenderWindow& i_window); // declaracion que recibe como parametro el renderizar en pantalla
    void reset(const Position& i_home, const Position& i_home_exit); // declaracion que recibe como parametro la posicion del home y de la puerta del home por reiniciar
    void set_position(short i_x, short i_y); // declaracion de las coordenadas
    void switch_mode(); // declaracion de cuando cambian de modo los fantasmas
    void update(unsigned char i_level, array<array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, Ghost& i_ghost_0, Pacman& i_pacman); // declaracion para actualizar el nive, el mapa, los fantasmas y el pacman
    void update_target(unsigned char i_pacman_direction, const Position& i_ghost_0_position, const Position& i_pacman_position); // declaracion para actualizar la posicion final

    Position get_position(); // estructura de la posicion para obtener la posicion de los fantasmas
};

class colisionGhosts{

public:

    unsigned int get_scoreGhost(); // metodo para obtener el puntaje cuando pacman se comen a un fantasma

};