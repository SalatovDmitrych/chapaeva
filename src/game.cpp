#include "game.hpp"

Game::Game()
{
    backgroundTexture.loadFromFile("res/board.png");
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setOrigin(backgroundTexture.getSize().x / 2, backgroundTexture.getSize().y / 2);
    backgroundSprite.setPosition(400, 400);

    window.create(sf::VideoMode(800, 800), "chapaeva");

    for (int i = 0, s = 1; i < objectsCount; i++, s *= -1)
    {
        if (s < 0)
            objects[i].setSide(RED);
        else
            objects[i].setSide(WHITE);
    }

    for (int i = 0, x = 225; i < objectsCount; i += 2, x += 50)
    {
        objects[i].setPos(x, 225);
        objects[i + 1].setPos(x, 575);
    }

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
