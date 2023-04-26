#include "Menu.h"
#include "iostream"
#include "Facil.h"
#include "Medio.h"
#include "Dificil.h"
#include "Experto.h"

using namespace std;
using namespace sf;

Menu::Menu() { //constructor para inicializar menu
    this->initWindow();
}

Menu::~Menu() { //destructor de menu
    delete this->window;
    delete this->button1;
    delete this->button2;
    delete this->button3;
    delete this->button4;
    delete this->buttonText;
    delete this->buttonText2;
    delete this->buttonText3;
    delete this->buttonText4;
    delete this->TitleText;
    delete this->indicaciones;

}

void Menu::run() { // mientras corre la pantalla, se renderiza
    while (this->window->isOpen()){
        this->update();
        this->render();
    }
}

void Menu::update() {
    Event e;
    while (this->window->pollEvent(e)) { //ciclo encargado de los eventos con botones
        //evento para cerrar la pantalla
        if(e.Event::type == Event::Closed)
            this->window->close();
        //evento para cerrar la pantalla con la tecla escape
        if (e.Event::key.code == Keyboard::Escape)
            this->window->close();
        //evento sobre el boton de facil
        if (e.Event::type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left && this->button1->getGlobalBounds().contains(e.mouseButton.x, e.mouseButton.y)){
            this->window->close();
            Facil facil;
            facil.run();
        }
        // evento sobre el boton de Medio
        if (e.Event::type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left && this->button2->getGlobalBounds().contains(e.mouseButton.x, e.mouseButton.y)){
            this->button2->setFillColor(Color::Blue);
            this->window->close();
            Medio medio;
            medio.run();
        }
        // evento sobre el boton de Dificil
        if (e.Event::type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left && this->button3->getGlobalBounds().contains(e.mouseButton.x, e.mouseButton.y)){
            this->button3->setFillColor(Color::Blue);
            this->window->close();
            Dificil dificil;
            dificil.run();
        }
        // evento sobre el boton de Experto
        if (e.Event::type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left && this->button4->getGlobalBounds().contains(e.mouseButton.x, e.mouseButton.y)){
            this->button4->setFillColor(Color::Blue);
            this->window->close();
            Experto experto;
            experto.run();
        }
    }
}

void Menu::render() { // muestra la ventana renderizada con textos y botones

    this->window->clear(Color(255, 195, 0, 0)); //color de fondo

    //dibuja los botones
    this->window->draw(*this->button1);
    this->window->draw(*this->button2);
    this->window->draw(*this->button3);
    this->window->draw(*this->button4);

    //dibuja el texto de los botones
    this->window->draw(*this->buttonText);
    this->window->draw(*this->buttonText2);
    this->window->draw(*this->buttonText3);
    this->window->draw(*this->buttonText4);

    // dibuja el titulo y las indicaciones
    this->window->draw(*this->TitleText);
    this->window->draw(*this->indicaciones);

    //display de la ventana
    this->window->display();
}

void Menu::initWindow() { //incluye el formato de los botones y textos asi como su posicion en pantalla

    //incluye fuente de texto, nombre de pantalla y frame
    this->font.loadFromFile("/home/fernandez/CLionProjects/PuckMan/fonts/fuenteretro.ttf");
    this->window = new RenderWindow(VideoMode(800, 600), "Menu - PuckMan", Style::Titlebar | Style::Close);
    this->window->setFramerateLimit(144);

    this->window->setVerticalSyncEnabled(false);

    //figura para los botoes de los 4 niveles
    this->button1 = new RectangleShape(Vector2f(100, 50));
    this->button2 = new RectangleShape(Vector2f(100, 50));
    this->button3 = new RectangleShape(Vector2f(100, 50));
    this->button4 = new RectangleShape(Vector2f(100, 50));

    // formato del texto para los cuatro botones
    this->buttonText = new Text("Facil", this->font, 20);
    this->buttonText2 = new Text("Medio", this->font, 20);
    this->buttonText3 = new Text("Dificil", this->font, 20);
    this->buttonText4 = new Text("Experto", this->font, 20);

    //formato de titulo e indicaciones
    this->TitleText = new Text("PuckMan", this->font, 40);
    this->indicaciones = new Text("Seleccione el nivel", this->font, 30);

    //posicion del titulo e indicaciones
    TitleText->setPosition(Vector2f(320, 100));
    indicaciones->setPosition(Vector2f(272, 210));

    // color y posicion de los botones por nivel
    button1->setPosition(Vector2f(350, 275));
    button1->setFillColor(Color::Blue);
    buttonText->setPosition(Vector2f(375, 290));

    button2->setPosition(Vector2f(350, 350));
    button2->setFillColor(Color::Blue);
    buttonText2->setPosition(Vector2f(375, 360));

    button3->setPosition(Vector2f(350, 425));
    button3->setFillColor(Color::Blue);
    buttonText3->setPosition(Vector2f(375, 435));

    button4->setPosition(Vector2f(350, 500));
    button4->setFillColor(Color::Blue);
    buttonText4->setPosition(Vector2f(365, 510));
}