#include "Slider.h"

#include <iostream>

#include "GameManager.h"
#include "Button.h"
#include "Math.h"

Slider::Slider()
{
}

Slider::Slider(const sf::Vector2f& _pos, const sf::Vector2f& _scale, GameManager* _gameManager,
    sf::RenderWindow* _windowPtr, const EOrientation& _orientation)
{
    position = _pos;
    scale = _scale;
    if(scale.y > scaleYClamp)
        scale.y = scaleYClamp;
    orientation = _orientation;
    windowPtr = _windowPtr;
    InitSliderComposition();
}

Slider::Slider(const sf::Vector2f& _pos, const sf::Vector2f& _scale, const EOrientation& _orientation,
   GameManager* _gameManager, const std::string& _barTexturePath, const std::string& _handleTexturePath)
{
    position = _pos;
    sliderBar = InitSprite(barTexture, _barTexturePath);
    sliderBar->setPosition(position);
    orientation = _orientation;
    sliderHandle = InitSprite(handleTexture, _handleTexturePath);
    sliderHandle->setOrigin(sliderHandle->getGlobalBounds().width/2, sliderHandle->getGlobalBounds().height/2);
    sliderHandle->setPosition(sliderBar->getOrigin());
    gameManager =_gameManager;
    
}

Slider::Slider(const sf::Vector2f& _pos, const sf::Vector2f& _scale, const EOrientation& _orientation,
    GameManager* _gameManager, const float& _minValue, const float& _maxValue, sf::RenderWindow* _windowPtr, const std::string& _barTexturePath,
    const std::string& _handleTexturePath)
{
    position = _pos;
    scale = _scale;
    if(scale.y > scaleYClamp)
        scale.y = scaleYClamp;
    orientation = _orientation;
    windowPtr = _windowPtr;
    minValueLerp = _minValue;
    maxValueLerp = _maxValue;
    if(!_barTexturePath.empty())
        defaultBarTexturePath = _barTexturePath;
    if(!_handleTexturePath.empty())
        defaultHandleTexturePath = _handleTexturePath;
    InitSliderComposition();
}



Slider::~Slider()
{
    delete sliderBar;
    delete sliderBarLeft;
    delete sliderBarRight;
    delete sliderHandle;
    delete debugSprite;
    delete debugSpriteEnd;
}

void Slider::InitSliderComposition()
{
    sliderBar = InitSprite(barTexture, defaultBarTexturePath);
    InitOrientation(orientation, sliderBar);
    sliderBarLeft = InitSprite(barSideLeftTexture, defaultBarSideLeftTexturePath);
    InitOrientation(orientation, sliderBarLeft);
    sliderBarRight = InitSprite(barSideRightTexture, defaultBarSideRightTexturePath);
    InitOrientation(orientation, sliderBarRight);
    sliderBar->setScale(scale);
    sliderBar->setPosition(position);
    const sf::FloatRect _barRect = sliderBar->getGlobalBounds();
    sf::Vector2f _pos = sliderBar->getPosition();
    const bool _isHorizontal = orientation == HORIZONTAL;
        startPositionHandle = _isHorizontal ? sf::Vector2f(_pos.x, _pos.y + _barRect.height/2) :
    sf::Vector2f(_pos.x + _barRect.width/2, _pos.y);
        endPositionHandle = _isHorizontal ? sf::Vector2f(_pos.x + _barRect.width, _pos.y + _barRect.height/2) :
    sf::Vector2f(_pos.x + _barRect.width/2, _pos.y - _barRect.height);
    InitLateralBars();
    InitHandle();
    
}

void Slider::InitLateralBars()
{
    const sf::FloatRect _leftBarRect = sliderBarLeft->getGlobalBounds();
    const sf::FloatRect _rightBarRect = sliderBarRight->getGlobalBounds();

    //DEBUG
    sliderBarLeft->setColor(sf::Color(255,255,255));
    sliderBarRight->setColor(sf::Color(255,255,150));
    //DEBUG
    
    sliderBarLeft->setOrigin(_leftBarRect.width/2, _leftBarRect.height/2);
    sliderBarRight->setOrigin(_rightBarRect.width/2, _rightBarRect.height/2);
    
    sliderBarLeft->setRotation(sliderBar->getRotation());
    sliderBarRight->setRotation(sliderBar->getRotation());
    
    sliderBarRight->setScale(scale);
    
    const sf::FloatRect _barRect = sliderBar->getGlobalBounds();
    const sf::Vector2f _pos = sliderBar->getPosition();
    const bool _isHorizontal = orientation == HORIZONTAL;
    sliderBarLeft->setScale(scale.x * (_isHorizontal ? 0.1f : .08f), scale.y + (_isHorizontal ? .5f : .3f));
    sliderBarRight->setScale(scale.x * (_isHorizontal ? 0.1f : .08f), scale.y + (_isHorizontal ? .5f : .3f));
    sliderBarLeft->setPosition(startPositionHandle);
    sliderBarRight->setPosition(endPositionHandle);
}

void Slider::InitHandle()
{
    sliderHandle = InitSprite(handleTexture, defaultHandleTexturePath);
    sliderHandle->setOrigin(sliderHandle->getGlobalBounds().width/2, sliderHandle->getGlobalBounds().height/2);
    sliderHandle->setRotation(sliderBar->getRotation());
    sliderHandle->setScale(scale.x/4, scale.x/4);
    const bool _isHorizontal = orientation == HORIZONTAL;
    float _dist = Math::Distance2D(endPositionHandle, startPositionHandle);
    sf::Vector2f _pos = _isHorizontal ? sf::Vector2f(startPositionHandle.x + _dist/2, startPositionHandle.y) :
    sf::Vector2f(startPositionHandle.x, endPositionHandle.y + _dist/2);
    sliderHandle->setPosition(_pos);
}

void Slider::DebugVector(const std::string& _text, const sf::Vector2f& _vectorToDebug)
{
    std::cout<<_text<<_vectorToDebug.x<<"-"<<_vectorToDebug.y<<"\n";
}

void Slider::DetectInteraction()
{
    const bool _pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    if(!_pressed)return;
    sf::Vector2i _mousePos = sf::Mouse::getPosition(*windowPtr);
    if(sliderHandle->getGlobalBounds().contains(static_cast<sf::Vector2f>(_mousePos)))
    {
        SetPositionHandle(static_cast<sf::Vector2f>(_mousePos));
        ManageSliderValue(currentValue, minValueSlider, maxValueSlider);
    }
}

void Slider::ManageSliderValue(float& _current, const float& _min, const float& _max)
{
    distanceSlider = Math::Distance2D(endPositionHandle, startPositionHandle);
    distanceHandle = Math::Distance2D(sliderHandle->getPosition(), startPositionHandle);
    float _currentSliderValue = distanceHandle/distanceSlider;
    _currentSliderValue = _currentSliderValue > _max ? _max : _currentSliderValue < _min ? _min : _currentSliderValue;
    
    if(minValueLerp != 0.f || maxValueLerp != 0.f)
    {
        _current = Lerp(_currentSliderValue);
        onValueChangedF.Invoke(_current);
        return;
    }
    _current = _currentSliderValue;
    onValueChangedF.Invoke(_current);
}

float Slider::Lerp(const float& _currentValue) const
{
    return (maxValueLerp - minValueLerp) * _currentValue + minValueLerp;
}

void Slider::InitDebug()
{
    debugTexture.loadFromFile(debugTexturePath);
    debugSprite = new sf::Sprite(debugTexture);
    debugSpriteEnd = new sf::Sprite(debugTexture);
    debugSpriteEnd->setColor(sf::Color(255,150,0));
}

void Slider::InitOrientation(const EOrientation& _orientation, sf::Sprite* _spriteToRotate)
{
    _spriteToRotate->setRotation(_orientation == HORIZONTAL ? 0 : -90);
}

sf::Sprite* Slider::InitSprite(sf::Texture& _texture,const std::string& _path)
{
    if(!_texture.loadFromFile(_path))
        throw std::exception("Error : failed to load slider sprite texture");
    sf::Sprite* _spriteToInit = new sf::Sprite(_texture);
    return _spriteToInit;

}


void Slider::DrawDebug(sf::RenderWindow* _windowPtr)
{
    _windowPtr->draw(*debugSprite);
}


void Slider::DrawSlider(sf::RenderWindow* _windowPtr)
{
    _windowPtr->draw(*sliderBar);
    _windowPtr->draw(*sliderBarLeft);
    _windowPtr->draw(*sliderBarRight);
    _windowPtr->draw(*sliderHandle);

    if(debugSprite)
        DrawDebug(_windowPtr);
}


void Slider::SetPositionHandle(const float& _x, const float& _y)
{
    const bool _isHorizontal = orientation == HORIZONTAL;
    sf::Vector2f _temp = sf::Vector2f(_x, _y);
    sf::Vector2f _newPos;
    if(_isHorizontal)
    {
        const float _x = _temp.x > endPositionHandle.x ? endPositionHandle.x :
        _temp.x < startPositionHandle.x ? startPositionHandle.x : _temp.x;
        const float _y = startPositionHandle.y;
        _newPos = sf::Vector2f(_x, _y);
    }
    else
    {
        const float _x = startPositionHandle.x;
        const float _y = _temp.y > endPositionHandle.y ? endPositionHandle.y :
        _temp.y < startPositionHandle.y ? startPositionHandle.y : _temp.y;
        _newPos = sf::Vector2f(_x, _y);
    }
    sliderHandle->setPosition(_newPos);
}

void Slider::SetPositionHandle(const sf::Vector2f& _pos)
{
    const bool _isHorizontal = orientation == HORIZONTAL;
    sf::Vector2f _newPos;
    if(_isHorizontal)
    {
        const float _x = _pos.x > endPositionHandle.x ? endPositionHandle.x :
        _pos.x < startPositionHandle.x ? startPositionHandle.x : _pos.x;
        const float _y = startPositionHandle.y;
        _newPos = sf::Vector2f(_x, _y);
    }
    else
    {
        const float _x = startPositionHandle.x;
        const float _y = _pos.y < endPositionHandle.y ? endPositionHandle.y :
        _pos.y > startPositionHandle.y ? startPositionHandle.y : _pos.y;
        _newPos = sf::Vector2f(_x, _y);
    }
    sliderHandle->setPosition(_newPos);
}

void Slider::SetWindow(sf::RenderWindow* _windowPtr)
{
    if(windowPtr)
        delete windowPtr;
    windowPtr = _windowPtr;
}

void Slider::Tick(const float& _deltaTime)
{
    DetectInteraction();
}

void Slider::SetMinValue(const float& _min)
{
    minValueLerp = _min;
}

void Slider::SetMaxValue(const float& _max)
{
    maxValueLerp = _max;
}

