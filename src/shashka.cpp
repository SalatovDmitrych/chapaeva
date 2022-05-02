#include "shashka.hpp"
#include "physics.hpp"

Shashka::Shashka()
{
    shape.setRadius(RADIUS * 0.9);
    shape.setOutlineThickness(RADIUS * 0.1);

    side = WHITE;

    velocity.x = 0;
    velocity.y = 0;

    pos.x = 0;
    pos.y = 0;

    shape.setOrigin(RADIUS, RADIUS);

    thisOnBoard = true;
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

void Shashka::setVelocity(const float x, const float y)
{
    velocity.x = x;
    velocity.y = y;
}

void Shashka::setVelocity(const sf::Vector2f &vec)
{
    velocity = vec;
}

sf::Vector2f Shashka::getVelocity() const
{
    return velocity;
}

sf::CircleShape Shashka::getShape() const
{
    return shape;
}

void Shashka::update(const float delta, Shashka * const obj, const int cnt)
{
    for (int i = 0; i < cnt; i++)
    {
        if (&obj[i] == this || !obj[i].onBoard())
            continue;

        if (checkCollision(pos, obj[i].getPos()))
        {
            resolveCollision(*this, obj[i]);
        }
    }


    if (vecLen(velocity) > 5 )
        velocity -= velocity * FRICTION * delta;
    else
        setVelocity(0, 0);


    pos += velocity * delta;

    shape.setPosition(pos);

    if (!inRect(200, 600, 200, 600))
    {
        thisOnBoard = false;
        if (side == RED)
            Shashka::redsCount -= 1;
        else
            Shashka::whitesCount -= 1;
    }
}

Side Shashka::getSide() const
{
    return side;
}

void Shashka::setSide(const Side s)
{
    side = s;
    if (s == RED)
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

bool Shashka::inRect(const int left, const int right, const int top, const int bottom) const
{
    return pos.x + RADIUS > left && pos.x - RADIUS < right && pos.y + RADIUS > top && pos.y - RADIUS < bottom;
}

bool Shashka::onBoard() const
{
    return thisOnBoard;
}

void Shashka::putOnBoard()
{
    thisOnBoard = true;
}

void Shashka::choose()
{
    shape.setOutlineColor(sf::Color::Yellow);
}

void Shashka::unchoose()
{
    if (side == RED)
        shape.setOutlineColor(sf::Color::Red);
    else
        shape.setOutlineColor(sf::Color::White);
}
