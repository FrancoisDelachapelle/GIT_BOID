#pragma once
#include <SFML/System/Clock.hpp>

class TimeManager
{
private:
    sf::Clock clock;
    float deltaTime = 0.1f;
    int fps = 0;

public:
    static inline float DeltaTimeSeconds = 0;
    TimeManager();
    ~TimeManager();

private:
    /**
     * \brief Update delta time in seconds
     */
    void UpdateDeltaTime();
    /**
     * \brief Update current FPS
     */
    void UpdateFPS();
public:
    inline float GetDeltaTime() const {return deltaTime;}
    inline int GetFPS() const {return fps;}
    void Tick();
};
