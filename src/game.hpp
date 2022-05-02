#pragma once
#include <SFML/Graphics.hpp>
#include "shashka.hpp"

constexpr int objectsCount = 16;
static_assert(objectsCount % 2 == 0);

class Game
{
private:
    sf::RenderWindow window;

    sf::Sprite tableSprite;
    sf::Texture tableTexture;

    sf::Sprite boardSprite;
    sf::Texture boardTexture;

    Shashka* currentSh;
    Shashka objects[objectsCount];

    int redLine;
    int whiteLine;

    void newGame(const int whiteLn, const int redLn);
    void endGame();
    void input();
    void update(const float delta);
    void draw();
    void lmbPressed();
    void rmbPressed();

public:
    Game();

    void start();
};
