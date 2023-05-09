#include "GameManager.h"
#include <iostream>

GameManager::GameManager()
{
    
}

GameManager::~GameManager()
{
    
}

void GameManager::GeneralInit()
{
    InitWindow();
    InitManager();
    InitGenerator();
}

void GameManager::InitWindow()
{
    window.create(sf::VideoMode(width, height), "BOID");
    windowPtr = &window;
}

void GameManager::InitGenerator()
{
    boidGenerator = new BoidGenerator(*windowPtr);
    boidGenerator->SetGameManager(this);
    boidGenerator->SpawnBoids(*boidManager);
}

void GameManager::InitManager()
{
    uiManager = new UIManager(this, windowPtr);
    boidManager = new BoidManager();
    boidManager->SetGameManager(this);
    timeManager = new TimeManager();
}

void GameManager::ManageWindow()
{
    if (!windowPtr)return;
    if (windowPtr->isOpen())
    {
        sf::Event event;
        while (windowPtr->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                windowPtr->close();
                gameIsRunning = false;
            }
        }
    }
}

void GameManager::Draw()
{
    DrawWindow();
}

void GameManager::DrawWindow()
{
    if (!windowPtr)return;
    if (!windowPtr->isOpen())
    {
        std::cout<< "Not Open"<<std::endl;
        return;
    }
    windowPtr->clear();
    DrawActors(); //Draw every actors
    DrawUI(); // Draw UI elements
    windowPtr->display();
}

void GameManager::DrawActors()
{
    const int _size = static_cast<int>(boidManager->GetAllBoids().size());
    std::vector<BoidMember*> _boids = boidManager->GetAllBoids();
    for (int i = 0; i < _size; ++i)
    {
        if(!_boids[i] || !_boids[i]->GetSprite())continue;
        windowPtr->draw(*_boids[i]->GetSprite());

        if(_boids[i]->GetIsDebug() && _boids[i]->GetID()==0) //Draw Debug
        {
            
            windowPtr->draw(*_boids[i]->GetDebugShape());
            windowPtr->draw(*_boids[i]->GetAreaShape());
        }
    }
}

void GameManager::DrawUI()
{
    uiManager->GetSliderTest()->DrawSlider(windowPtr);
}

void GameManager::ActorLoop(const float& _deltaTime)
{
    if(!boidManager)return; //there are only boids as actors so if no boid manager then no boids
    const int _size = static_cast<int>(boidManager->GetAllBoids().size());
    std::vector<BoidMember*> _boids = boidManager->GetAllBoids();
    for (int i = 0; i < _size; ++i)
    {
        BoidMember* _boid = _boids[i];
        if(!_boid)continue;
        _boid->Tick(_deltaTime, _boids);
    }
}

void GameManager::ManagerLoop()
{
    timeManager->Tick();
    uiManager->Tick(timeManager->GetDeltaTime());
}

void GameManager::GameLoop()
{
    GeneralInit(); //First init of all needed components and elements
    while (gameIsRunning || windowPtr->isOpen()) // Main loop
    {
        ManageWindow(); //check events related to the window
        Draw(); // Main draw function
        ManagerLoop(); // Managers tick
        ActorLoop(timeManager->GetDeltaTime()); // Actors tick
    }
}
