#ifndef PUCKMAN_FACIL_H
#define PUCKMAN_FACIL_H

#include <SFML/Graphics.hpp>

class Facil {
private:
    sf::RenderWindow* window;
    // Aquí se pueden agregar los objetos necesarios para la pantalla de Facil

    void initWindow();
public:
    Facil();
    virtual ~Facil();

    void run();
    void update();
    void render();
};

#endif //PUCKMAN_FACIL_H
