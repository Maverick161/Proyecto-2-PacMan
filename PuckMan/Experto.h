#ifndef PUCKMAN_EXPERTO_H
#define PUCKMAN_EXPERTO_H

#include <SFML/Graphics.hpp>

class Experto {
private:
    sf::RenderWindow* window;
    // Aquí se pueden agregar los objetos necesarios para la pantalla de Experto

    void initWindow();
public:
    Experto();
    virtual ~Experto();

    void run();
    void update();
    void render();
};

#endif //PUCKMAN_EXPERTO_H
