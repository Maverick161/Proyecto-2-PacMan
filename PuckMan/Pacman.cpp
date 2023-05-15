#include <array>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Global.hpp"
#include "Pacman.hpp"
#include "MapCollision.hpp"

Pacman::Pacman() :
    puntaje(0),
    vidas(3),
	animation_over(0),
	dead(0),
	direction(0),
	energizer_timer(0),
	position({0, 0})

{
}

unsigned int Pacman::get_score() {
    return puntaje;
}

unsigned int Pacman::get_vidas(){
    return vidas;
}

bool Pacman::get_animation_over()
{
	return animation_over;
}

bool Pacman::get_dead()
{
	return dead;
}

unsigned char Pacman::get_direction()
{
	return direction;
}

unsigned short Pacman::get_energizer_timer()
{
	return energizer_timer;
}

void Pacman::draw(bool i_victory, RenderWindow& i_window)
{
	unsigned char frame = static_cast<unsigned char>(floor(animation_timer / static_cast<float>(PACMAN_ANIMATION_SPEED)));

	Sprite sprite;

	Texture texture;

	sprite.setPosition(position.x, position.y);

	if (1 == dead || 1 == i_victory)
	{
		if (animation_timer < PACMAN_DEATH_FRAMES * PACMAN_ANIMATION_SPEED)
		{
			animation_timer++;

			texture.loadFromFile("/home/fernandez/CLionProjects/Proyecto-2-PacMan/PuckMan/Images/PacmanDeath16.png");

			sprite.setTexture(texture);
			sprite.setTextureRect(IntRect(CELL_SIZE * frame, 0, CELL_SIZE, CELL_SIZE));

			i_window.draw(sprite);

		}
		else
		{
			//You can only die once.
			animation_over = 1;
		}
	}
	else
	{
		texture.loadFromFile("/home/fernandez/CLionProjects/Proyecto-2-PacMan/PuckMan/Images/Pacman16.png");

		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(CELL_SIZE * frame, CELL_SIZE * direction, CELL_SIZE, CELL_SIZE));

		i_window.draw(sprite);

		animation_timer = (1 + animation_timer) % (PACMAN_ANIMATION_FRAMES * PACMAN_ANIMATION_SPEED);
	}
}

void Pacman::reset()
{
    puntaje = 0;
    vidas = 3;
	animation_over = 0;
	dead = 0;

	direction = 0;

	animation_timer = 0;
	energizer_timer = 0;
}

void Pacman::set_animation_timer(unsigned short i_animation_timer)
{
	animation_timer = i_animation_timer;
}

void Pacman::set_dead(bool i_dead)
{
	dead = i_dead;

	if (1 == dead)
	{
		//revisa que la animacion empiece desde 0
		animation_timer = 0;
	}
}

void Pacman::set_position(short i_x, short i_y)
{
	position = {i_x, i_y};
}

void Pacman::update(unsigned char i_level, array<array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map)
{
	array<bool, 4> walls{};
	walls[0] = map_collision(0, 0, PACMAN_SPEED + position.x, position.y, i_map);
	walls[1] = map_collision(0, 0, position.x, position.y - PACMAN_SPEED, i_map);
	walls[2] = map_collision(0, 0, position.x - PACMAN_SPEED, position.y, i_map);
	walls[3] = map_collision(0, 0, position.x, PACMAN_SPEED + position.y, i_map);


	if (1 == Keyboard::isKeyPressed(Keyboard::Right))
	{
		if (0 == walls[0]) // no virar en esta direccion si se encuentra un muro
		{
			direction = 0;
		}
	}

	if (1 == Keyboard::isKeyPressed(Keyboard::Up))
	{
		if (0 == walls[1])
		{
			direction = 1;
		}
	}

	if (1 == Keyboard::isKeyPressed(Keyboard::Left))
	{
		if (0 == walls[2])
		{
			direction = 2;
		}
	}

	if (1 == Keyboard::isKeyPressed(Keyboard::Down))
	{
		if (0 == walls[3])
		{
			direction = 3;
		}
	}

	if (0 == walls[direction])
	{
		switch (direction)
		{
			case 0:
			{
				position.x += PACMAN_SPEED;

				break;
			}
			case 1:
			{
				position.y -= PACMAN_SPEED;

				break;
			}
			case 2:
			{
				position.x -= PACMAN_SPEED;

				break;
			}
			case 3:
			{
				position.y += PACMAN_SPEED;
			}
		}
	}

	if (-CELL_SIZE >= position.x)
	{
		position.x = CELL_SIZE * MAP_WIDTH - PACMAN_SPEED;
	}
	else if (CELL_SIZE * MAP_WIDTH <= position.x)
	{
		position.x = PACMAN_SPEED - CELL_SIZE;
	}

	if (1 == map_collision(1, 0, position.x, position.y, i_map)) //cuando pacman come un poder
	{
		energizer_timer = static_cast<unsigned short>(ENERGIZER_DURATION / pow(2, i_level));

        puntaje += 10;
        cout << "El valor de puntaje es: " << puntaje << std::endl;
	}

	else
	{
		energizer_timer = max(0, energizer_timer - 1);
	}
}

Position Pacman::get_position()
{
	return position;
}

void Pacman::loseLife() { //metodo para reducir la vida cuando pacman toca un fantasma
    vidas--;
    if(vidas <= 0) {
        set_dead(1); // muere pacman cuando ya no hay vidas
    }
}
