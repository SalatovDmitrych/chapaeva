#pragma once
#include <SFML/Graphics.hpp>
#include "shashka.hpp"

constexpr int objectsCount = 16;
static_assert(objectsCount % 2 == 0);

class Game
{
private:
    sf::RenderWindow window;

    sf::Sprite boardSprite;
    sf::Texture boardTexture;

    sf::Texture endGameTexture;
    sf::Sprite endGameSprite;

    sf::CircleShape moveIndexer;

    Side currentSide;
    int currentMove;
    bool playerMadeMove;
    Shashka* currentSh;
    Shashka objects[objectsCount];

    int redLine;
    int whiteLine;
    const int NUM_OF_BOARD_LINES = 8;

    void newGame(const int whiteLn, const int redLn);
    void endGame(const Side s);
    void changeLine();
    void input();
    void update(const float delta);
    void draw();
    void lmbPressed();
    void rmbPressed();
    bool allChekersStop();
    void changeSide();
    sf::VertexArray getArrowToChecker(const Shashka &s) const;
    sf::Vector2f mousePos(const sf::RenderWindow &w) const;

public:
    Game();

    void start();
};
