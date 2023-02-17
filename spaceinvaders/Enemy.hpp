#pragma once


class Enemy {
	bool direction;
	bool dead;

	unsigned short x;
	unsigned short y;
	unsigned short speed;
	
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Color color;
public:
	Enemy();
	Enemy(sf::Texture& texture, unsigned short fx, unsigned short fy,unsigned short spd);

	unsigned short get_x() const;
	unsigned short get_y() const;

	void draw(sf::RenderWindow& window);
	void update();
	void set_dead(int i);

	void setColor(sf::Color color);
	unsigned short get_dead() const;

	sf::Color getColor() const;
	sf::Vector2u get_texture_size() const;
};