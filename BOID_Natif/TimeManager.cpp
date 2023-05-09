#include "TimeManager.h"

#include <SFML/Graphics/RenderWindow.hpp>

TimeManager::TimeManager()
{
    clock = sf::Clock();
}

TimeManager::~TimeManager()
{
}

void TimeManager::Tick()
{
    UpdateDeltaTime();
    UpdateFPS();
}

void TimeManager::UpdateDeltaTime()
{
    sf::Time _time = clock.getElapsedTime(); //How much time elapsed since start
    deltaTime = _time.asSeconds(); //get the delta time as seconds
    DeltaTimeSeconds = deltaTime;
    clock.restart(); // restart clock for next call
}

void TimeManager::UpdateFPS()
{
    fps = static_cast<int>(1/deltaTime); // calc fps
}


