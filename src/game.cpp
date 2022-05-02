#include "game.hpp"

int Shashka::whitesCount = objectsCount / 2;
int Shashka::redsCount = objectsCount / 2;

Game::Game()
{
    /*tableTexture.loadFromFile("res/table.png");
    tableTexture.setSmooth(true);
    tableSprite.setTexture(tableTexture);
    tableSprite.setOrigin(tableTexture.getSize().x / 2, tableTexture.getSize().y / 2);
    tableSprite.setPosition(400, 400);*/

    boardTexture.loadFromFile("res/board.png");
    boardSprite.setTexture(boardTexture);
    boardSprite.setOrigin(boardTexture.getSize().x / 2, boardTexture.getSize().y / 2);
    boardSprite.setPosition(400, 400);

    window.create(sf::VideoMode(800, 800), "chapaeva");

    newGame(0, 7);
}

void Game::newGame(const int whiteLn, const int redLn)
{
    Shashka::redsCount = objectsCount / 2;
    Shashka::whitesCount = objectsCount / 2;

    whiteLine = whiteLn;
    redLine = redLn;


    for (int i = 0, s = 1; i < objectsCount; i++, s *= -1)
    {
        if (s < 0)
            objects[i].setSide(RED);
        else
            objects[i].setSide(WHITE);
    }

    for (int i = 0, x = 225; i < objectsCount; i += 2, x += 50)
    {
        objects[i].setPos(x, 225 + 50 * whiteLn);
        objects[i].putOnBoard();
        objects[i].setVelocity(0, 0);

        objects[i + 1].setPos(x, 225 + 50 * redLn);
        objects[i + 1].putOnBoard();
        objects[i + 1].setVelocity(0, 0);
    }

    currentSh = nullptr;
}

void Game::start()
{
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Time dt = clock.restart();

        float delta = dt.asSeconds();

        input();
        update(delta);
        draw();
    }
}

void Game::endGame()
{
    if (Shashka::redsCount < 1)
    {
        if (whiteLine + 1 == redLine)
            newGame(whiteLine + 1, redLine + 1);
        else
            newGame(whiteLine + 1, redLine);
    }

    if (Shashka::whitesCount < 1)
    {
        if (redLine - 1 == whiteLine)
            newGame(whiteLine - 1, redLine - 1);
        else
            newGame(whiteLine, redLine - 1);
    }
}
