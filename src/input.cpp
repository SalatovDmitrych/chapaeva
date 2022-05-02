#include "game.hpp"
#include "physics.hpp"

bool chooseSh(const sf::Vector2f &s, const sf::Vector2f &v)
{
    return (v.x - s.x) * (v.x - s.x) +
           (v.y - s.y) * (v.y - s.y)  <= RADIUS * RADIUS;
}

void kickSh(Shashka &sh, const sf::Vector2f &vec)
{
    sf::Vector2f speed;
    speed = (vec - sh.getPos()) * -1.5f;
    sh.setVelocity(speed);
}

sf::Vector2f mousePos(const sf::RenderWindow &w)
{
    return w.mapPixelToCoords(sf::Mouse::getPosition(w));
}

void Game::lmbPressed()
{
    if (currentSh == nullptr)
    {
        for (int i = 0; i < objectsCount; i++)
        {
            if (chooseSh(objects[i].getPos(), mousePos(window)) && objects[i].getVelocity() == sf::Vector2f(0, 0))
            {
                currentSh = &objects[i];
                currentSh->choose();
            }
        }

    }
    else
    {
        currentSh->unchoose();
        kickSh(*currentSh, mousePos(window));
        currentSh = nullptr;
    }
}

void Game::rmbPressed()
{
    if (currentSh != nullptr)
        currentSh->unchoose();

    currentSh = nullptr;
}

void Game::input()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
                window.close();
                break;

            default:
                break;
            }
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
                lmbPressed();

            if (event.mouseButton.button == sf::Mouse::Right)
                rmbPressed();
        }
    }
}

