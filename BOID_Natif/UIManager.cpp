#include "UIManager.h"
#include "GameManager.h"

UIManager::UIManager()
{
}

UIManager::UIManager(GameManager* _gameManager, sf::RenderWindow* _windowPtr)
{
    gameManager = _gameManager;
    windowPtr = _windowPtr;
    InitSlider();
}

UIManager::~UIManager()
{
    
}

void UIManager::InitSlider()
{
    sf::Vector2u _dimensions = gameManager->GetGameWindowDimensions();
    sf::Vector2f pos = sf::Vector2f(10, _dimensions.y - 10);
    sf::Vector2f scale = sf::Vector2f(5, 10);//default
    //sliderTest = new Slider(pos,scale, gameManager, VERTICAL);
    sliderTest = new Slider(pos,scale, gameManager, windowPtr, VERTICAL);
}

void UIManager::SetWindow(sf::RenderWindow* _windowPtr)
{
    windowPtr = _windowPtr;
}

void UIManager::Tick(const float _deltaTime)
{
    sliderTest->Tick(_deltaTime);
}
