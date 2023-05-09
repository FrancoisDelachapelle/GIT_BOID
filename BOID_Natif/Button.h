#pragma once
#include <SFML/Graphics/Sprite.hpp>

class Button
{
private:
    sf::Sprite* buttonSprite = nullptr;
    sf::Color normal = sf::Color(0,0,0);
    sf::Color hovered = sf::Color(0,0,0);
    sf::Color pressed = sf::Color(0,0,0);
    sf::Vector2f position = sf::Vector2f(0,0);
    sf::Texture* texture = nullptr;
public:
    sf::Sprite* GetButtonSprite() const {return buttonSprite;}
    sf::Color& GetNormalButtonColor() {return normal;}
    sf::Color& GetHoveredButtonColor() {return hovered;}
    sf::Color& GetpressedButtonColor() {return pressed;}
    sf::Vector2f& GetButtonPosition() {return position;}
    void SetButtonSprite(sf::Sprite* _sprite) {buttonSprite = _sprite;}
    void SetNormalButtonColor(const sf::Color& _normal) {normal = _normal;}
    void SetHoveredButtonColor(const sf::Color& _hovered) {hovered = _hovered;}
    void SetPressedButtonColor(const sf::Color& _pressed) {pressed = _pressed;}
    void SetButtonPosition(const sf::Vector2f& _position) {position = _position;}
public:
    Button();
    Button(const sf::Vector2f& _pos, const sf::Vector2f& _scale, sf::Texture* _texture);
    ~Button();
private:
public:
    static Button* CreateButton(const sf::Vector2f& _position, const sf::Vector2f& _size, sf::Texture* _texture);
};
