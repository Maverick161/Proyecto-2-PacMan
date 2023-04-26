#include "Dificil.h"
#include <iostream>

using namespace sf;

Dificil::Dificil() {
    this->initWindow();
}

Dificil::~Dificil() {
    delete this->window;
    // Aquí se pueden agregar la eliminación de otros objetos si es necesario
}

void Dificil::run() {
    while (this->window->isOpen()){
        this->update();
        this->render();
    }
}

void Dificil::update() {
    Event e;
    while (this->window->pollEvent(e)) {
        if (e.type == Event::Closed)
            this->window->close();
        if (e.type == Event::KeyPressed && e.key.code == Keyboard::Escape)
            this->window->close();
        // Aquí se pueden agregar más eventos si es necesario
    }
}

void Dificil::render() {
    /*
    * Muestra la ventana renderizada
    */
    this->window->clear(Color(0, 0, 0, 0));
    // Aquí se pueden agregar los objetos necesarios para renderizar la pantalla de Dificil
    this->window->display();
}

void Dificil::initWindow() {
    this->window = new RenderWindow(VideoMode(800, 600), "Dificil - PuckMan", Style::Titlebar | Style::Close);
    this->window->setFramerateLimit(144);
    // Aquí se pueden agregar más opciones de configuración si es necesario
}
