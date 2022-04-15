#pragma once
#include <SFML/Graphics.hpp>

enum SIDE {WHITE, RED};

const float RADIUS = 20;
const float FRICTION = 0.8f;

class Shashka
{
private:
    sf::Vector2f pos;

    sf::Vector2f speed;

    sf::CircleShape shape;

    SIDE side;

public:

    Shashka();

    sf::CircleShape& getShape();

    void setSpeed(const sf::Vector2f &vec);
    void setSpeed(const float x, const float y);
    sf::Vector2f getSpeed() const;

    void setPos(const sf::Vector2f &vec);
    void setPos(const float x, const float y);
    sf::Vector2f getPos() const;

    //גûחûגאועסÿ םא ךאזהûי םמגûי ךאהנ
    void update(float delta, Shashka *obj, int cnt);

    SIDE getSide() const;
    void setSide(SIDE side_);
};
