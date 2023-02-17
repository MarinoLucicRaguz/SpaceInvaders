#include "Game.hpp"
#include <iostream>

void Game::initVar()
{
    this->window = nullptr;
    this->enemiesManager = new EnemiesManager();
}

void Game::initWind()
{
    this->videoMode.height = SCREEN_HEIGHT;
    this->videoMode.width = SCREEN_WIDTH;
    this->window = new sf::RenderWindow(this->videoMode, "SpaceInvaders");
}

Game::Game()
{
    this->initVar();
    this->initWind();
    level = 1;
    gameOver = 0;

    for (int i = 0; i < MAX_ENEMIES / 2; i++) {
        this->enemiesManager->addEnemy(i * 50, 20, sf::Color::Red,0);
    }
    for (int i = 0; i < MAX_ENEMIES / 2; i++) {
        this->enemiesManager->addEnemy(i * 50, 70, sf::Color::Green,0);
    }
}

Game::~Game()
{
    delete this->window;
    delete this->enemiesManager;
}

const bool Game::running() const
{
    return this->window->isOpen();
}
void Game::pollEvents()
{
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->ev.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;
        }
    }
}

void Game::update() {

    this->pollEvents();
    ship.update();
    ship.checkCollisions(enemiesManager->get_enemies());
    enemiesManager->updateEnemies();

    for (auto& enemy : enemiesManager->get_enemies()) {
        if (enemy.get_y() >= ship.get_y()) {
            gameOver = true;
            break;
        }
    }
    
    if (enemiesManager->get_enemies().empty()) {
        level++;

        for (int i = 0; i < MAX_ENEMIES / 2; i++) {
            this->enemiesManager->addEnemy(i * 50, 20, sf::Color::Red, level);
        }
        for (int i = 0; i < MAX_ENEMIES / 2; i++) {
            this->enemiesManager->addEnemy(i * 50, 70, sf::Color::Green, level);
        }
    }
}


void Game::render()
{
    sf::Texture font_texture;
    font_texture.loadFromFile("textures/Font.png");
    this->window->clear();

    if (!gameOver) {
        ship.draw(*this->window);
        enemiesManager->drawEnemies(*this->window);
    }
    else {
        draw_text(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, "Game Over", *this->window, font_texture);
    }

    displayScore();
    //draw_text(8, 8, "Bullets: " + std::to_string(ship.sizeBullets()), *this->window, font_texture);
    this->window->display();
}

void Game::displayScore()
{
    sf::Text text;
    sf::Font font;
    font.loadFromFile("textures/font3.ttf");
    text.setFont(font);


    text.setString("Score: " + std::to_string(ship.returnScore()));
    text.setPosition(10, 20);  
    text.setFont(font);
    text.setCharacterSize(24);  
    text.setFillColor(sf::Color::White); 

    window->draw(text);
}

void Game::draw_text(short i_x, short i_y, const std::string& i_text, sf::RenderWindow& i_window, const sf::Texture& i_font_texture)
{
    short character_x = i_x;
    short character_y = i_y;

    unsigned char character_height = i_font_texture.getSize().y;
    unsigned char character_width = i_font_texture.getSize().x / 96;

    sf::Sprite character_sprite(i_font_texture);

    for (std::string::const_iterator a = i_text.begin(); a != i_text.end(); a++)
    {
        if ('\n' == *a)
        {
            character_x = i_x;
            character_y += character_height;

            continue;
        }

        character_sprite.setPosition(character_x, character_y);
        character_sprite.setTextureRect(sf::IntRect(character_width * (*a - 32), 0, character_width, character_height));

        character_x += character_width;

        i_window.draw(character_sprite);
    }
}