#pragma once
#include "Button.h"
#include "Slider.h"

class GameManager;
class UIManager
{
private:
    GameManager* gameManager = nullptr;
    sf::RenderWindow* windowPtr = nullptr;
    Slider* sliderTest = nullptr;
    
public:
    Slider* GetSliderTest() const {return sliderTest;}
public:
    UIManager();
    UIManager(GameManager* _gameManager, sf::RenderWindow* _windowPtr);
    ~UIManager();
private:
    void InitSlider();
public:
    void SetWindow(sf::RenderWindow* _windowPtr);
    void Tick(const float _deltaTime);
    
    
    
};
