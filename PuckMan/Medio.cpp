#include "Medio.h"
#include <iostream>

using namespace sf;

Medio::Medio() {
    this->initWindow();
}

Medio::~Medio() {
    delete this->window;
    // Aquí se pueden agregar la eliminación de otros objetos si es necesario
}

void Medio::run() {
    while (this->window->isOpen()){
        this->update();
        this->render();
    }
}

void Medio::update() {
    Event e;
    while (this->window->pollEvent(e)) {
        if (e.type == Event::Closed)
            this->window->close();
        if (e.type == Event::KeyPressed && e.key.code == Keyboard::Escape)
            this->window->close();
        // Aquí se pueden agregar más eventos si es necesario
    }
}

void Medio::render() {
    /*
    * Muestra la ventana renderizada
    */
    this->window->clear(Color(0, 0, 0, 0));
    // Aquí se pueden agregar los objetos necesarios para renderizar la pantalla de Medio
    this->window->display();
}

void Medio::initWindow() {
    this->window = new RenderWindow(VideoMode(800, 600), "Medio - PuckMan", Style::Titlebar | Style::Close);
    this->window->setFramerateLimit(144);
    // Aquí se pueden agregar más opciones de configuración si es necesario
}
