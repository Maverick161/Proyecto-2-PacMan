#pragma once
using namespace sf;
using namespace std;

class GhostManager
{
    //The ghosts will switch between the scatter mode and the chase mode before permanently chasing Pacman.
    //So we need this to keep track of the waves.
    unsigned char current_wave;

    //Damn, I really used a lot of timers.
    unsigned short wave_timer;

    //array<Ghost, 4> ghosts;

    vector<Ghost> ghosts;

public:
    GhostManager();
    void draw(bool i_flash, RenderWindow& i_window);
    void reset(unsigned char i_level, const array<Position, 4>& i_ghost_positions);
    void update(unsigned char i_level, array<array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, Pacman& i_pacman);
    void activateGhost(unsigned char index); // para activar los fantasmas por nivel

};