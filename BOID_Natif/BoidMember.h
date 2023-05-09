#pragma once
#include <SFML/graphics.hpp>
#include "MovementComponent.h"

enum class EBoidsType
{
	FLOCK,
	PREDATOR,
	MAX
};

class BoidGenerator;
class GameManager;
class BoidManager;
class BoidMember
{
protected:
	//number used to generate boid ID
	static int ID;
	//Boid's ID
	const int currentID;
	//Current poisition
	sf::Vector2f position= sf::Vector2f();
	//current angle
	float angle = 0;
	//current scale of the sprite
	float spriteScale = 1;
	//Color of the sprite
	sf::Color color;
	//sprite ptr
	sf::Sprite* sprite = nullptr;
	//Texture saved to optimize performances
	sf::Texture texture = sf::Texture();
	//Debug shape for boid position
	sf::CircleShape* debugShape= nullptr;
	//Debug shape for boid method
	sf::CircleShape* areaShape= nullptr;
	//show debugs
	bool debug = false;
	//Boid type
	EBoidsType type = EBoidsType::FLOCK;

	//Managers and components ptr
	GameManager* gameManager = nullptr;
	BoidManager* boidManager = nullptr;
	BoidGenerator* generator = nullptr;
	MovementComponent* movement = nullptr;

	//GettersSetters inline
public:
	inline int GetID() const {return currentID;}
	inline EBoidsType GetBoidsType() const {return type;}
	inline sf::Sprite* GetSprite() const {return sprite;}
	inline sf::CircleShape* GetDebugShape() const {return debugShape;}
	inline sf::CircleShape* GetAreaShape() const {return areaShape;}
	inline bool GetIsDebug() const {return debug;}
	inline sf::Vector2f GetPosition() const {return position;}
	inline MovementComponent* GetMovementComponent() const {return movement;}
	inline GameManager* GetGameManager() const {return gameManager;}
	inline float GetAngle() const {return angle;}
	inline void SetBoidGenerator(BoidGenerator* _generator) {generator = _generator;}
	inline void SetBoidManager(BoidManager* _boidManager) {boidManager = _boidManager;}
	inline void SetGameManager(GameManager* _gameManager) {gameManager = _gameManager;}
	inline void SetIsDebug(const bool& _debug) {debug = _debug;}
	
public:
	BoidMember();
	BoidMember(const sf::Vector2f& _position, const float& _scale, const std::string& _spritePath,const EBoidsType& _type, BoidGenerator* _generator);
	BoidMember(const BoidMember& _boidMember, const std::string& _spritePath) : currentID(ID++) {}
	~BoidMember();

public:
	/**
	 * \brief Load the sprite with the given texture path 
	 * \param _filePath : path to the texture
	 */
	void LoadSprite(const std::string _filePath);
	/**
	 * \brief set the boid generator (manager)
	 * \param _generator : generator manager
	 */
	void SetGenerator(BoidGenerator* _generator);
	void SetPosition(const sf::Vector2f& _position);
	void SetPosition(const float& _x, const float& _y);
	void SetAngle(const float& _angle);
	/**
	 * \brief Set all needed managers of the boid
	 * \param _gameManager : main manager which creates and contains the sub managers
	 */
	void SetAllInitialManagers(GameManager* _gameManager);
	sf::Vector2f GetSpriteSize();
	void Tick(const float& _deltaTime, std::vector<BoidMember*>& _boids);
	
	//operators
	bool operator==(const BoidMember& _other) const;
	
};

