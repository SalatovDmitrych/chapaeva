#include "game.hpp"

void Game::update(float delta)
{
    for (int i = 0; i < objectsCount; i++)
        objects[i].update(delta, objects, objectsCount);
}
