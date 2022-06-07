#include "game.hpp"

void Game::draw()
{
    window.clear(sf::Color::Green);

    window.draw(boardSprite);

    for (int i = 0; i < objectsCount; i++)
        if (objects[i].onBoard()) window.draw(objects[i].getShape());

    if (currentSh != nullptr)
        window.draw(getArrowToChecker(*currentSh));

    if (allChekersStop())
        window.draw(moveIndexer);

    window.display();
}
