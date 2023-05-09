#include "BoidGenerator.h"
#include "BoidManager.h"

BoidGenerator::BoidGenerator()
{
}

BoidGenerator::BoidGenerator(sf::RenderWindow& _currentWindow)
{
    std::srand(std::time(0)); //init rand seed
    sf::Vector2u _dimensions = _currentWindow.getSize();
    maxX = _dimensions.x; //Set window max dimensions
    maxY = _dimensions.y;
}

BoidGenerator::~BoidGenerator()
{
  
}


void BoidGenerator::SpawnBoids(BoidManager& _boidManager)
{
    const int _size = flockNumberToSpawn + predatorNumberToSpawn;
    for (int i = 0; i < _size; ++i)
    {
        if(maxX == 0 || maxY == 0)
            break;
        float _x = static_cast<float>(rand()%maxX);
        float _y = static_cast<float>(rand()%maxY);
        BoidMember* _boid = new BoidMember(sf::Vector2f(_x, _y), i < flockNumberToSpawn ? scaleFlock : scalePredator, boidTexturePath,
            i < flockNumberToSpawn ? EBoidsType::FLOCK : EBoidsType::PREDATOR, this);
        _boid->SetAllInitialManagers(gameManager);
        _boidManager.AddBoidMember(_boid); //boid is added to boid manager for centralization of data
        
    }
    _boidManager.SendBoidInfoToSlider(); //Once all boids are created, send their infos to the slider managing their speed
    
}
