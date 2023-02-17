#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Player.hpp"
#include "Global.hpp"
#include "EnemiesManager.hpp"

#ifndef GAME_H
#define GAME_H

class Game {
private:
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;

    Player ship;
    EnemiesManager* enemiesManager;

    void initVar();
    void initWind();
    
    bool gameOver;
    int level;
public:
    Game();
    virtual ~Game();

    sf::RenderWindow* getWindow() { return window; }

    const bool running() const;

    void pollEvents();
    void update();
    void render();

    void displayScore();
    void draw_text(short i_x, short i_y, const std::string& i_text, sf::RenderWindow& i_window, const sf::Texture& i_font_texture);
};
#endif
