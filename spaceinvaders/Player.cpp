#include "Player.hpp"
#include "Global.hpp"
#include <iostream>


Player::Player() :	x(0.5f * (SCREEN_WIDTH - BASE_SIZE))
	{
	reload_time = 1;
	score = 0;

	texture.loadFromFile("textures/ship.png");
	sprite.setTexture(texture);

	bullet_texture.loadFromFile("textures/bullet.png");
	bullet_sprite.setTexture(bullet_texture);
	}

void Player::draw(sf::RenderWindow& window)
{
	sprite.setPosition(x, SCREEN_HEIGHT - 3 * BASE_SIZE);
	for (const Bullet& bullet : bullets)
	{
		bullet_sprite.setPosition(bullet.x, bullet.y);

		window.draw(bullet_sprite);
	}
	window.draw(sprite);

}

void Player::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if(x>BUFFER_FR_BORDER)
			x -= NORMAL_SPEED;
		
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{ 
		if(x<SCREEN_WIDTH- BUFFER_FR_BORDER *3)
			x += NORMAL_SPEED;
	}
	if (reload_time == 0) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			reload_time = FPERRELOAD;
			bullets.push_back({ static_cast<short>(x),SCREEN_HEIGHT - 2 * BASE_SIZE });
		}
	}
	else
	{
		reload_time--;
	}


	for (Bullet& bullet : bullets)
	{
		bullet.y -= PLAYER_BULLET_SPEED;
		if (-BASE_SIZE >= bullet.y)
		{
			bullet.dead = 1;
		}
	}

	bullets.erase(remove_if(bullets.begin(), bullets.end(), [](const Bullet& i_bullet)
		{
			return 1 == i_bullet.dead;
		}), bullets.end());
}
int Player::sizeBullets()
{
	return bullets.size();
}

std::vector<Bullet> Player::returnBullets()
{
	return bullets;
}
void Player::checkCollisions(std::vector<Enemy>& enemies) {
	for (auto& bullet : bullets) {
		for (auto& enemy : enemies) {
			if ((bullet.x >= enemy.get_x() && bullet.x <= enemy.get_x() + texture.getSize().x) && (bullet.y >= enemy.get_y() && bullet.y <= enemy.get_y() + texture.getSize().y)) {
				if (enemy.getColor() == sf::Color::Red)
					score += 200;
				else
					score += 100;
				enemy.set_dead(1);
				bullet.dead = true;
				enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](const Enemy& enemy) { return enemy.get_dead(); }), enemies.end());
				break;
			}
		}
	}
}



unsigned short Player::get_y() const
{
	return SCREEN_HEIGHT - 3 * BASE_SIZE;
}

unsigned int Player::returnScore() const
{
	return score;
}



