#include "BoidMember.h"

#include <iostream>
#include "BoidGenerator.h"
#include "GameManager.h"

int BoidMember::ID = 0;


BoidMember::BoidMember() : currentID(ID++)
{
}

BoidMember::BoidMember(const sf::Vector2f& _position, const float& _scale, const std::string& _spritePath,const EBoidsType& _type, BoidGenerator* _generator) : currentID(ID++)
{
	position = _position;
	spriteScale = _scale;
	type = _type;
	generator = _generator;
	movement = new MovementComponent(this);
	LoadSprite(_spritePath); //Load sprite texture
	color = type == EBoidsType::FLOCK ? sprite->getColor() : sf::Color(100,0,255); //Change the color depending on whether boid is flock member or predator
	sprite->setColor(color);
	
	//DEBUG
	debug = false;
	debugShape = new sf::CircleShape(10); // Debug boid position
	debugShape->setOrigin(debugShape->getOrigin().x + debugShape->getRadius(), debugShape->getOrigin().y + debugShape->getRadius()); //center origin

	if(currentID==0 && debug)
	{
		sprite->setColor(sf::Color(255,0,0));
		areaShape = new sf::CircleShape(movement->GetCohesionDistance()); //Debug boid method area of effect
		areaShape->setFillColor(sf::Color::Transparent);
		areaShape->setOutlineThickness(2);
		areaShape->setOutlineColor(sf::Color::Red);
		areaShape->setPosition(position);
		areaShape->setOrigin(areaShape->getOrigin().x + areaShape->getRadius(), areaShape->getOrigin().y + areaShape->getRadius());
	}
	//DEBUG
}

BoidMember::~BoidMember()
{
	boidManager->RemoveBoidMember(this);
	delete sprite;
	delete generator;
	delete movement;
}


void BoidMember::LoadSprite(const std::string _filePath)
{
	if(!texture.loadFromFile(_filePath))
		std::cout<<"ERROR : Failed to load texture from file"<<std::endl;
	sprite = new sf::Sprite(texture);
	sprite->setOrigin(.5f * GetSpriteSize().x, .5f * GetSpriteSize().y); // center the origin of the sprite
	sprite->scale(spriteScale * -1,spriteScale); //invert the sprite
	sprite->setPosition(position);
	sprite->setRotation(0);
}

void BoidMember::SetAllInitialManagers(GameManager* _gameManager)
{
	gameManager = _gameManager; //Set all the various managers used by the boid
	generator = gameManager->GetBoidGenerator();
	boidManager = gameManager->GetBoidManager();
}

void BoidMember::SetGenerator(BoidGenerator* _generator)
{
	generator = _generator;
}

void BoidMember::SetPosition(const sf::Vector2f& _position)
{
	position = _position;
	sprite->setPosition(position);
}

void BoidMember::SetPosition(const float& _x, const float& _y)
{
	position.x = _x;
	position.y = _y;
	sprite->setPosition(position);
}

void BoidMember::SetAngle(const float& _angle)
{
	angle = _angle;
	sprite->setRotation(angle);
}

sf::Vector2f BoidMember::GetSpriteSize()
{
	const float _x = static_cast<float>(sprite->getTexture()->getSize().x) * sprite->getScale().x;
	const float _y = static_cast<float>(sprite->getTexture()->getSize().y) * sprite->getScale().y;
	const sf::Vector2f _temp(_x, _y);
	return _temp;
}

void BoidMember::Tick(const float& _deltaTime, std::vector<BoidMember*>& _boids)
{
	if(!movement)return;
	movement->Tick(_deltaTime,_boids);
	if(currentID==0 && areaShape)
		areaShape->setPosition(position); //if debug and is first boid, update area of effect position
}

bool BoidMember::operator==(const BoidMember& _other) const
{
	return currentID == _other.currentID;
}
