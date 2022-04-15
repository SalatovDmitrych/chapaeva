#include "game.hpp"

void Game::draw()
{
    window.clear(sf::Color::Green);

    window.draw(backgroundSprite);

    for (int i = 0; i < objectsCount; i++)
        window.draw(objects[i].getShape());

    window.display();
}
