#pragma once
#include <vector>
#include "BoidMember.h"

class GameManager;
class BoidManager;
class BoidGenerator
{
protected:
	//number of flock member to spawn
	int flockNumberToSpawn = 30;
	//number of predator to spawn (still WIP with avoidance and map limits)
	int predatorNumberToSpawn = 0;
	//scale of flock member's sprite
	float scaleFlock = 1.f;
	//scale of predator's sprite
	float scalePredator = 2.f;
	//max dimensions of the window
	unsigned int maxX = 0, maxY=0;
	//path to the boid texture
	std::string boidTexturePath = "Ressources/fishSpriteTest.png";
	GameManager* gameManager = nullptr;

	//GetterSetters
public:
	sf::Vector2f GetMaxWindowDimensions() const {return sf::Vector2f(static_cast<float>(maxX), static_cast<float>(maxY));}
	void SetGameManager(GameManager* _gameManager) {gameManager = _gameManager;}
public:
	BoidGenerator();
	BoidGenerator(sf::RenderWindow& _currentWindow);
	
	~BoidGenerator();


public:
	/**
	 * \brief Spawn the boids and add them to the boid manager
	 * \param _boidManager : manager centralizing all boids
	 */
	void SpawnBoids(BoidManager& _boidManager);
};

