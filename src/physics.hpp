#pragma once
#include <SFML/Graphics.hpp>
#include "shashka.hpp"

sf::Vector2f normalize(const sf::Vector2f &v);
float vecLen(const sf::Vector2f &v);
float scalar(const sf::Vector2f &a, const sf::Vector2f &b);
bool checkCollision(const sf::Vector2f &a, const sf::Vector2f &b);
void resolveCollision(Shashka &a, Shashka &b);
