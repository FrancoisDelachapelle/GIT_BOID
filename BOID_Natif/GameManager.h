#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "BoidGenerator.h"
#include "BoidManager.h"
#include "TimeManager.h"
#include "UIManager.h"

class GameManager
{

protected:
	//Window of the program
	sf::RenderWindow window;
	// Ptr of the window above
	sf::RenderWindow* windowPtr = nullptr;
	//bool used for the main loop
	bool gameIsRunning = true;
	//generator to create boids
	BoidGenerator* boidGenerator = nullptr;
	//manager centralizing boids
	BoidManager* boidManager = nullptr;
	//manager used for time and delta time calculation
	TimeManager* timeManager = nullptr;
	//Centralize UI elements
	UIManager* uiManager = nullptr;
	//size X of the window
	float width = 1200;
	//size Y of the window
	float height = 800;
	//GetterSetters
public:
	inline BoidGenerator* GetBoidGenerator() const {return boidGenerator;}
	inline BoidManager* GetBoidManager() const {return boidManager;}
	inline TimeManager* GetTimeManager() const {return timeManager;}
	inline UIManager* GetUIManager() const {return uiManager;}
	inline sf::Vector2u GetGameWindowDimensions() const {return windowPtr->getSize();}
public:
	GameManager();
	~GameManager();
private :
	/**
	 * \brief Init all needed elements for the start of the program
	 */
	void GeneralInit();
	/**
	 * \brief Init the window
	 */
	void InitWindow();
	/**
	 * \brief Init generator manager as it requires more steps than the others
	 */
	void InitGenerator();
	/**
	 * \brief init other managers (boids, time and ui)
	 */
	void InitManager();
	/**
	 * \brief manage window related events 
	 */
	void ManageWindow();
	//Main draw function
	void Draw();
	//Draw the window elements and its content
	void DrawWindow();
	//Draw every actors
	void DrawActors();
	//Draw every UI elements
	void DrawUI();
	//Actor tick function. Call each actor's tick function
	void ActorLoop(const float& _deltaTime);
	//Manager tick function. Call each manager's tick function
	void ManagerLoop();
public:
	//Main tick function
	void GameLoop();

};

