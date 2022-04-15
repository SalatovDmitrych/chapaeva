#pragma once
#include <SFML/Graphics.hpp>
#include "shashka.hpp"

const int objectsCount = 16;

class Game
{
private:
    sf::RenderWindow window;

    sf::Sprite backgroundSprite;
    sf::Texture backgroundTexture;

    Shashka* currentSh = nullptr;
    Shashka objects[objectsCount];

    void input();
    void update(float delta);
    void draw();
    void lmbPressed();
    void rmbPressed();

public:
    Game();

    void start();
};
