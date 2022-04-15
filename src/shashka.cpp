#include "shashka.hpp"
#include "physics.hpp"

Shashka::Shashka()
{
    shape.setRadius(RADIUS * 0.9);
    shape.setOutlineThickness(RADIUS * 0.1);

    side = WHITE;

    speed.x = 0;
    speed.y = 0;

    pos.x = 0;
    pos.y = 0;

    shape.setOrigin(RADIUS, RADIUS);
}

void Shashka::setPos(const float x, const float y)
{
    pos.x = x;
    pos.y = y;
}

void Shashka::setPos(const sf::Vector2f &vec)
{
    pos = vec;
}

sf::Vector2f Shashka::getPos() const
{
    return pos;
}

void Shashka::setSpeed(const float x, const float y)
{
    speed.x = x;
    speed.y = y;
}

void Shashka::setSpeed(const sf::Vector2f &vec)
{
    speed = vec;
}

sf::Vector2f Shashka::getSpeed() const
{
    return speed;
}

sf::CircleShape& Shashka::getShape()
{
    return shape;
}

void Shashka::update(float delta, Shashka *obj, int cnt)
{
    for (int i = 0; i < cnt; i++)
    {
        if (&obj[i] == this)
            continue;

        if (checkCollision(pos, obj[i].getPos()))
        {
            resolveCollision(*this, obj[i]);
        }
    }


    if (vecLen(speed) > 5 )
    {
        speed += -speed * FRICTION * delta;
    }
    else
    {
        speed.x = 0;
        speed.y = 0;
    }

    pos += speed * delta;

    shape.setPosition(pos);
}

SIDE Shashka::getSide() const
{
    return side;
}

void Shashka::setSide(SIDE side_)
{
    side = side_;
    if (side_ == RED)
    {
        shape.setFillColor(sf::Color::Red);
        shape.setOutlineColor(sf::Color::Red);
    }
    else
    {
        shape.setFillColor(sf::Color::White);
        shape.setOutlineColor(sf::Color::White);
    }
}
