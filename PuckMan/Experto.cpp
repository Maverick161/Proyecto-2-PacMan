#include "Experto.h"
#include <iostream>

using namespace sf;

Experto::Experto() {
    this->initWindow();
}

Experto::~Experto() {
    delete this->window;
    // Aquí se pueden agregar la eliminación de otros objetos si es necesario
}

void Experto::run() {
    while (this->window->isOpen()){
        this->update();
        this->render();
    }
}

void Experto::update() {
    Event e;
    while (this->window->pollEvent(e)) {
        if (e.type == Event::Closed)
            this->window->close();
        if (e.type == Event::KeyPressed && e.key.code == Keyboard::Escape)
            this->window->close();
        // Aquí se pueden agregar más eventos si es necesario
    }
}

void Experto::render() {
    /*
    * Muestra la ventana renderizada
    */
    this->window->clear(Color(0, 0, 0, 0));
    // Aquí se pueden agregar los objetos necesarios para renderizar la pantalla de Experto
    this->window->display();
}

void Experto::initWindow() {
    this->window = new RenderWindow(VideoMode(800, 600), "Experto - PuckMan", Style::Titlebar | Style::Close);
    this->window->setFramerateLimit(144);
    // Aquí se pueden agregar más opciones de configuración si es necesario
}