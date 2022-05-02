#include "physics.hpp"
#include <cmath>

float vecLen(const sf::Vector2f &v)
{
    return std::hypot(v.x, v.y);
}

sf::Vector2f normalize(const sf::Vector2f &v)
{
    float l = 1.0f / vecLen(v);
    return sf::Vector2f(v.x * l, v.y * l);
}

float dotProduct(const sf::Vector2f &a, const sf::Vector2f &b)
{
    return a.x * b.x + a.y * b.y;
}

bool checkCollision(const sf::Vector2f &a, const sf::Vector2f &b)
{
    float r = RADIUS * 2;
    r *= r;
    return r > (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

void resolveCollision(Shashka &a, Shashka &b)
{
    sf::Vector2f rv(b.getVelocity() - a.getVelocity());

    sf::Vector2f n = normalize(b.getPos() - a.getPos());

    float velAlongNormal = dotProduct(rv, n);

    if (velAlongNormal > 0)
        return;

    float e = 0.3;

    float j = -(1 + e) * velAlongNormal;
    j /= 2;

    sf::Vector2f impulse = n * j;

    a.setVelocity(a.getVelocity() - impulse);

    b.setVelocity(b.getVelocity() + impulse);
}
