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
    sh.setSpeed(speed);
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
            if (chooseSh(objects[i].getPos(), mousePos(window)) && objects[i].getSpeed() == sf::Vector2f(0, 0))
            {
                currentSh = &objects[i];
                currentSh->getShape().setOutlineColor(sf::Color::Yellow);
            }
        }

    }
    else
    {
        currentSh->setSide(currentSh->getSide());
        kickSh(*currentSh, mousePos(window));
        currentSh = nullptr;
    }
}

void Game::rmbPressed()
{
    if (currentSh != nullptr)
        currentSh->setSide(currentSh->getSide());

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
            {
                lmbPressed();
            }
            else if (event.mouseButton.button == sf::Mouse::Right)
            {
                rmbPressed();
            }
        }
    }
}

