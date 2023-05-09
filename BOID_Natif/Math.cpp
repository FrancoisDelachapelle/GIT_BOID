#include "Math.h"

#include <iostream>
#include <math.h>

float Math::Distance2D(const sf::Vector2f& _a, const sf::Vector2f& _b)
{
    const float _result = (_b.x - _a.x) * (_b.x - _a.x) + (_b.y - _a.y) * (_b.y - _a.y);
    return sqrtf(_result);
}

int Math::Distance2D(const sf::Vector2i& _a, const sf::Vector2i& _b)
{
    const int _result = (_b.x - _a.x) * (_b.x - _a.x) + (_b.y - _a.y) * (_b.y - _a.y);
    return static_cast<int>(sqrt(_result));
}

float Math::Distance2DSquared(const sf::Vector2f& _a, const sf::Vector2f& _b)
{
    return (_b.x - _a.x) * (_b.x - _a.x) + (_b.y - _a.y) * (_b.y - _a.y);
}

int Math::Distance2DSquared(const sf::Vector2i& _a, const sf::Vector2i& _b)
{
    return (_b.x - _a.x) * (_b.x - _a.x) + (_b.y - _a.y) * (_b.y - _a.y);
}

float Math::Magnitude(const sf::Vector2f& _a)
{
    return sqrtf(_a.x * _a.x + _a.y * _a.y);
}

int Math::Magnitude(const sf::Vector2i& _a)
{
    return static_cast<int>(sqrt(_a.x * _a.x + _a.y * _a.y));
}

sf::Vector2f Math::Normalize(const sf::Vector2f& _a)
{
    const float _length = Magnitude(_a);
    const float _x = _a.x /_length;
    const float _y = _a.y /_length;
    return sf::Vector2f{_x, _y};

}

sf::Vector2i Math::Normalize(const sf::Vector2i& _a)
{
    const int _length = Magnitude(_a);
    const int _x = _a.x /_length;
    const int _y = _a.y /_length;
    return sf::Vector2i{_x, _y};
}

sf::Vector2f Math::Limit(const sf::Vector2f& _vec, const float& _max)
{
    sf::Vector2f _norm;
    if(Magnitude(_vec)> _max*_max)
    {
        _norm = Normalize(_vec);
        _norm *= _max;
    }
    return _norm;
}

sf::Vector2i Math::Limit(const sf::Vector2i& _vec, const float& _max)
{
    sf::Vector2i _norm;
    if(Magnitude(_vec) > static_cast<int>(_max*_max))
    {
        _norm = Normalize(_vec);
        _norm *= static_cast<int>(_max);
    }
    return _norm;
}

float Math::Dot(const sf::Vector2f& _a, const sf::Vector2f& _b)
{
    return _a.x * _b.x + _a.y * _b.y;
}
