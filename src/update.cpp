#include "game.hpp"

void Game::update(const float delta)
{
    for (int i = 0; i < objectsCount; i++)
        if (objects[i].onBoard())
            objects[i].update(delta, objects, objectsCount, currentMove);
}
