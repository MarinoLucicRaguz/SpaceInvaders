#include <vector>
#include <SFML/Graphics.hpp>
#include "Enemy.hpp"
#include <iostream>

class EnemiesManager {
    unsigned short speed;

    sf::Texture texture;
    std::vector<Enemy> enemies;
public:
    EnemiesManager();

    void addEnemy(unsigned short fx, unsigned short fy, sf::Color color, unsigned short spd);
    void drawEnemies(sf::RenderWindow& window);
    void updateEnemies();
    std::vector<Enemy>& get_enemies();
};
