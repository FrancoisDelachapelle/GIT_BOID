#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "AllGlobalStructs.h"
#include "Delegate.h"


class Button;
class GameManager;

enum EOrientation
{
    HORIZONTAL,
    VERTICAL
};

class Slider
{
private:
    //Custom event : called each time the slider value change
    Action<float> onValueChangedF = nullptr;
    //sprite of the main bar
    sf::Sprite* sliderBar = nullptr;
    //sprite of the left limit
    sf::Sprite* sliderBarLeft= nullptr;
    //sprite of the right limit
    sf::Sprite* sliderBarRight = nullptr;
    //sprite of the handle
    sf::Sprite* sliderHandle = nullptr;

    //textures
    sf::Texture barTexture = sf::Texture();
    sf::Texture barSideLeftTexture = sf::Texture();
    sf::Texture barSideRightTexture = sf::Texture();
    sf::Texture handleTexture = sf::Texture();

    //position of the slider
    sf::Vector2f position = sf::Vector2f(0,0);
    //scale of the slider
    sf::Vector2f scale = sf::Vector2f(0,0);
    //Clamp of the slider's Y scale so that it keeps a harmonious shape
    float scaleYClamp = .3f;
    //position of the center of the slider
    sf::Vector2f sliderCenter = sf::Vector2f(0,0);
    //position of the center of the handle
    sf::Vector2f handleCenter = sf::Vector2f(0,0);

    //minimal position of the handle
    sf::Vector2f startPositionHandle = sf::Vector2f(0,0);
    //maximal position of the handle
    sf::Vector2f endPositionHandle = sf::Vector2f(0,0);
    //is the slider horizontal or vertical
    EOrientation orientation = HORIZONTAL;
    //ptr to the game manager
    GameManager* gameManager = nullptr;

    //texture paths
    std::string defaultBarTexturePath = "Ressources/SliderBarCenter.png";
    std::string defaultBarSideLeftTexturePath = "Ressources/SliderBarLeft.png";
    std::string defaultBarSideRightTexturePath = "Ressources/SliderBarRight.png";
    std::string defaultHandleTexturePath = "Ressources/SliderHandlePng.png";

    //Debug sprites
    sf::Sprite* debugSprite = nullptr;
    sf::Sprite* debugSpriteEnd = nullptr;
    sf::Texture debugTexture = sf::Texture();
    std::string debugTexturePath = "Ressources/WhiteBoxSprite.png";

    //ptr to the window
    sf::RenderWindow* windowPtr = nullptr;
    //distance between start and end position of the slider
    float distanceSlider = 0;
    //distance between the start position of the slider and the handle's position
    float distanceHandle = 0;
    //max value of the slider (normalized)
    float maxValueSlider = 1;
    //min value of the slider (normalized)
    float minValueSlider = 0;
    //current value of the slider (normalized)
    float currentValue = 0;
    //value passed through constructor. Gives the actual minimal value represented by the slider
    float minValueLerp = 0;
    //value passed through constructor. Gives the actual maximal value represented by the slider
    float maxValueLerp = 0;

public:
    Action<float>& OnValueChangedF() {return onValueChangedF;}
public:
    Slider();
    Slider(const sf::Vector2f& _pos, const sf::Vector2f& _scale, GameManager* _gameManager, sf::RenderWindow* _windowPtr, const EOrientation& _orientation = HORIZONTAL);
    Slider(const sf::Vector2f& _pos, const sf::Vector2f& _scale, const EOrientation& _orientation,
           GameManager* _gameManager, const std::string& _barTexturePath = "",const std::string& _handleTexturePath = "");
    Slider(const sf::Vector2f& _pos, const sf::Vector2f& _scale, const EOrientation& _orientation,
           GameManager* _gameManager, const float& _minValue, const float& _maxValue, sf::RenderWindow* _windowPtr,
           const std::string& _barTexturePath = "",const std::string& _handleTexturePath = "");
    ~Slider();
private:
    /**
     * \brief Init debug members and methods
     */
    void InitDebug();
    /**
     * \brief Rotate the sprite at creation
     * \param _orientation the orientation selected
     * \param _spriteToRotate the sprite that need rotation
     */
    void InitOrientation(const EOrientation& _orientation, sf::Sprite* _spriteToRotate);
    /**
     * \brief Load the texture from the given path into the given texture
     * \param _texture member saving the loaded texture
     * \param _path path to the texture
     * \return 
     */
    sf::Sprite* InitSprite(sf::Texture& _texture, const std::string& _path);
    /**
     * \brief Draw the debugs
     * \param _windowPtr : window ptr to call the draw func
     */
    void DrawDebug(sf::RenderWindow* _windowPtr);
    /**
     * \brief Create the slider by putting every element together
     */
    void InitSliderComposition();
    /**
     * \brief Create the lateral bar's sprites
     */
    void InitLateralBars();
    /**
     * \brief Create the slider's handle
     */
    void InitHandle();
    /**
     * \brief function to automatically call a cout filled with the given vector informations
     * \param _text : text filled
     * \param _vectorToDebug : vector to debug
     */
    void DebugVector(const std::string& _text, const sf::Vector2f& _vectorToDebug);
    /**
     * \brief Manage the slider action if there is interaction or not
     */
    void DetectInteraction();
    /**
     * \brief Update the slider value
     * \param _current current value
     * \param _min minimal value
     * \param _max maximal value
     */
    void ManageSliderValue(float& _current, const float& _min, const float& _max);
    /**
     * \brief Lerp of slider value to get the real modified value
     * \param _currentValue current slider value
     * \return the current value of the lerp
     */
    float Lerp(const float& _currentValue) const;
public:
    /**
     * \brief Draw the slider
     * \param _windowPtr window ptr to call the draw func
     */
    void DrawSlider(sf::RenderWindow* _windowPtr);
    void SetPositionHandle(const float& _x, const float& _y);
    void SetPositionHandle(const sf::Vector2f& _pos);
    void SetWindow(sf::RenderWindow* _windowPtr);
    void Tick(const float& _deltaTime);
    void SetMinValue(const float& _min);
    void SetMaxValue(const float& _max);
    
};




