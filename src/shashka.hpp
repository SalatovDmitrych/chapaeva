#pragma once
#include <SFML/Graphics.hpp>

enum Side {WHITE, RED};

constexpr float RADIUS = 20.0f;
constexpr float FRICTION = 0.8f;

class Shashka
{
private:
    sf::Vector2f pos;

    sf::Vector2f velocity;

    sf::CircleShape shape;

    Side side;

    bool thisOnBoard;

    int whenThisOut; //ход когда шашка вылетела за доску

public:
    static int whitesCount;
    static int redsCount;

    Shashka();

    sf::CircleShape getShape() const;

    void setVelocity(const sf::Vector2f &vec);
    void setVelocity(const float x, const float y);
    sf::Vector2f getVelocity() const;

    void setPos(const sf::Vector2f &vec);
    void setPos(const float x, const float y);
    sf::Vector2f getPos() const;

    void update(const float delta, Shashka * const obj, const int cnt, const int currentMove);

    Side getSide() const;
    void setSide(const Side s);

    bool inRect(const int left, const int right, const int top, const int bottom) const;
    bool onBoard() const;
    int whenOut() const;
    void putOnBoard();

    void choose();
    void unchoose();
};
