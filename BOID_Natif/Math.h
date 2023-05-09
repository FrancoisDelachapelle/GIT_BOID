#pragma once
#include <SFML/System/Vector2.hpp>
#include "Mat.h"
class Math
{
public:
    static float Distance2D(const sf::Vector2f& _a, const sf::Vector2f& _b);
    static int Distance2D(const sf::Vector2i& _a, const sf::Vector2i& _b);
    static float Distance2DSquared(const sf::Vector2f& _a,const sf::Vector2f& _b);
    static int Distance2DSquared(const sf::Vector2i& _a,const sf::Vector2i& _b);
    static float Magnitude(const sf::Vector2f& _a);
    static int Magnitude(const sf::Vector2i& _a);
    static float Dot(const sf::Vector2f& _a, const sf::Vector2f& _b);
    
    static sf::Vector2f Normalize(const sf::Vector2f& _a);
    static sf::Vector2i Normalize(const sf::Vector2i& _a);
    static sf::Vector2f Limit(const sf::Vector2f& _vec,const float& _max);
    static sf::Vector2i Limit(const sf::Vector2i& _vec,const float& _max);
};
