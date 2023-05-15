#pragma once
using namespace sf;
using namespace std;

class GhostManager
{

public:
    GhostManager();
    void draw(bool i_flash, RenderWindow& i_window);
    void reset(unsigned char i_level, const std::array<Position, 4>& i_ghost_positions);
    void update(unsigned char i_level, array<array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, Pacman& i_pacman);

private:
    unsigned char current_wave;
    unsigned short wave_timer;
    std::vector<Ghost> ghosts;  // Cambiado de std::array a std::vector
};