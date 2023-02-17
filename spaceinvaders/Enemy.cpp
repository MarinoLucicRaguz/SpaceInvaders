#include <SFML/Graphics.hpp>
#include "Global.hpp"
#include "Enemy.hpp"
#include <iostream>

Enemy::Enemy()
{
    dead = 0;
    direction = 0;
    speed = 3;
    x = 50;
    y = 50;
    color = sf::Color::Magenta;
    sprite.setColor(sf::Color::Magenta);
    sprite.setTexture(texture);
}

Enemy::Enemy(sf::Texture& texture, unsigned short fx, unsigned short fy,unsigned short spd) :
    direction(0),
    dead(0),speed(spd),
    x(fx), y(fy)
{
    color = sf::Color::White;
    sprite.setTexture(texture);
    sprite.setColor(color);
}

void Enemy::draw(sf::RenderWindow& window)
{
    if(dead == 0)
    {
        sprite.setPosition(x, y);
        window.draw(sprite);
    }
}

unsigned short Enemy::get_x() const
{
	return x;
}
unsigned short Enemy::get_y() const
{
	return y;
}

void Enemy::update() {

    if (dead == 0) {
        switch (direction) {
        case 0:
            if (x < SCREEN_WIDTH - BUFFER_FR_BORDER * 2) {
                x += speed;
            }
            else {
                direction = 1;
                y += 75;
            }
            break;
        case 1:
            if (x > BUFFER_FR_BORDER) {
                x -= speed;
            }
            else {
                direction = 0;
                y += 75;
            }
            break;
        }
    }
}

void Enemy::set_dead(int i) {
    dead = i;
}

unsigned short Enemy::get_dead() const {
    return dead;
}
void Enemy::setColor(sf::Color color) {
    sprite.setColor(color);
    this->color = color;
}

sf::Color Enemy::getColor() const {
    return this->color;
}

sf::Vector2u Enemy::get_texture_size() const {
    return texture.getSize();
}
