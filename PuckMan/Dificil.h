#ifndef PUCKMAN_DIFICIL_H
#define PUCKMAN_DIFICIL_H

#include <SFML/Graphics.hpp>

class Dificil {
private:
    sf::RenderWindow* window;
    // Aquí se pueden agregar los objetos necesarios para la pantalla de Dificil

    void initWindow();
public:
    Dificil();
    virtual ~Dificil();

    void run();
    void update();
    void render();
};

#endif //PUCKMAN_DIFICIL_H
