#include "Button.h"

Button::Button()
{
}

Button::Button(const sf::Vector2f& _pos, const sf::Vector2f& _scale, sf::Texture* _texture)
{
    buttonSprite->setScale(_scale);
    position = _pos;
    buttonSprite->setPosition(position);
    buttonSprite->setTexture(*_texture);
}

Button::~Button()
{
}


Button* Button::CreateButton(const sf::Vector2f& _position, const sf::Vector2f& _size, sf::Texture* _texture)
{
    return new Button(_position, _size, _texture);
}
