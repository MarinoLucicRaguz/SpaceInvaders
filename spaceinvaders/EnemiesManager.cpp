#include "EnemiesManager.hpp"


EnemiesManager::EnemiesManager() {
    texture.loadFromFile("textures/enemy.png");
    speed = 3;
}

void EnemiesManager::addEnemy(unsigned short fx, unsigned short fy, sf::Color color, unsigned short spd)
{
    Enemy enemy(texture, fx, fy, speed + spd);
    enemy.setColor(color);
    enemies.push_back(enemy);

}

void EnemiesManager::drawEnemies(sf::RenderWindow& window) {
    for (auto& enemy : enemies) {
        enemy.draw(window);
    }
}

void EnemiesManager::updateEnemies() {
    for (auto& enemy : enemies) {
        enemy.update();
    }
}

std::vector<Enemy>& EnemiesManager::get_enemies() {
    return enemies;
}