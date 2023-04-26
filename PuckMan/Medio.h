#ifndef PUCKMAN_MEDIO_H
#define PUCKMAN_MEDIO_H

#include <SFML/Graphics.hpp>

class Medio {
private:
    sf::RenderWindow* window;
    // Aquí se pueden agregar los objetos necesarios para la pantalla de Medio

    void initWindow();
public:
    Medio();
    virtual ~Medio();

    void run();
    void update();
    void render();
};

#endif //PUCKMAN_MEDIO_H
