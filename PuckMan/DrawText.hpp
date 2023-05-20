#pragma once

using namespace sf;
using namespace std;

/*
 * declaracion de la funcion draw_text con 5 parametros:
 * bool i_center para centrar el texto
 * enteros i_x para el eje x y i_y para el eje y que representan las coordenadas en las cuales se dibuja el texto
 * referencia a la cadena i_text que contiene el texto por dibujar en pantalla
 * referencia a RenderWindow i_window para renderizar el texto en pantalla
 */

void draw_text(bool i_center, unsigned short i_x, unsigned short i_y, const string& i_text, RenderWindow& i_window);