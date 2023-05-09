#include "MovementComponent.h"
#include <functional>
#include <iostream>
#include "Math.h"
#include "BoidMember.h"
#include "GameManager.h"

MovementComponent::MovementComponent()
{
}

MovementComponent::MovementComponent(BoidMember* _owner)
{
    owner = _owner;
}

MovementComponent::~MovementComponent()
{
}

void MovementComponent::InitMovementComponent()
{
    const float _x = static_cast<float>(rand()% maxRandInitialVelocity); //Gives a random initial velocity for each boid
    const float _y = static_cast<float>(rand()% maxRandInitialVelocity);
    initalVelocity = sf::Vector2f(_x,_y);
    initalVelocity *= owner->GetBoidsType() == EBoidsType::FLOCK ? 1.f : 3.f; //Boost initial velocity depending on the boid type : flock member or predator
    velocity = Math::Normalize(initalVelocity);
    emergencyTurnValue.x = velocity.x;
    emergencyTurnValue.y = velocity.y;
    emergencyTurnValue = Math::Normalize(emergencyTurnValue); // init turning value
    windowDimensions = owner->GetGameManager()->GetGameWindowDimensions();
    initDone = true;
    //owner->SetIsDebug(false);
    UIManager* _uiMgr = owner->GetGameManager()->GetUIManager();
    if(!_uiMgr)return;
    _uiMgr->GetSliderTest()->OnValueChangedF().AddDynamic(this, &MovementComponent::SetSpeed);
}

sf::Vector2f MovementComponent::FindAlignment(std::vector<BoidMember*> _boids)
{
    if(owner->GetBoidsType() == EBoidsType::PREDATOR)return sf::Vector2f(0,0);
    sf::Vector2f _sum = sf::Vector2f(0,0);
    const int _size = static_cast<int>(_boids.size());
    int _count = 0;
    for (int i = 0; i < _size; ++i)
    {
        BoidMember* _boid = _boids[i];
        if(!_boid || _boid == owner || _boid->GetBoidsType() != EBoidsType::FLOCK)continue;
        const float _dist = Math::Distance2D(owner->GetPosition(), _boid->GetPosition());
        if(_dist > 0 && _dist < alignmentDistanceLimit)
        {
            _sum += _boid->GetMovementComponent()->velocity/_dist; // for alignment, sum adds up each neighbor velocity div by the distance between owner and it
            _count++; // add new influencing neighbor
        }
    }
    if(_count > 0)
        _sum = AdaptSumVector(_sum, _count, aliMult); // all the work on the sum value
    return _sum;
}

sf::Vector2f MovementComponent::FindSeparation(std::vector<BoidMember*> _boids)
{
    sf::Vector2f _sum = sf::Vector2f(0,0);
    const int _size = static_cast<int>(_boids.size());
    int _count = 0;
    int _predatorCount = 0;
    for (int i = 0; i < _size; ++i)
    {
        BoidMember* _boid = _boids[i];
        if(!_boid || _boid == owner)continue;
        
        const bool _flockToFlock = _boid->GetBoidsType() == EBoidsType::FLOCK && owner->GetBoidsType()==EBoidsType::FLOCK;
        const bool _predatorToPredator = _boid->GetBoidsType() == EBoidsType::PREDATOR && owner->GetBoidsType()==EBoidsType::PREDATOR;
        
        if(owner->GetBoidsType()==EBoidsType::PREDATOR && _boid->GetBoidsType() == EBoidsType::FLOCK)continue;
        const float _dist = Math::Distance2D(owner->GetPosition(), _boid->GetPosition());
        if(_flockToFlock)
        {
            if(_dist > 0 && _dist < separationDistanceFlockLimit)
            {
                const sf::Vector2f _direction = _boid->GetPosition() - owner->GetPosition();
                _sum -= _direction/_dist; // for separation it's each direction div by distance
                _count++;
            }
        }
        if(owner->GetBoidsType() == EBoidsType::FLOCK && _boid->GetBoidsType() == EBoidsType::PREDATOR)
        {
            if(_dist > 0 && _dist < separationDistancePredatorLimit && !_flockToFlock)
            {
                const sf::Vector2f _direction = _boid->GetPosition() - owner->GetPosition();
                _sum -= _direction/_dist;
                _count++;
                _predatorCount++; // boids must avoid predators as well
            }
        }
        if(_predatorToPredator) // predators are only concerned about avoiding other predators
        {
            if(_dist > 0 && _dist < separationDistancePredatorLimit)
            {
                const sf::Vector2f _direction = _boid->GetPosition() - owner->GetPosition();
                _sum -= _direction/_dist;
                _count++;
            }
        }
        
    }
    if(_count > 0)
        _sum = AdaptSumVector(_sum, _count, sepMult);
    return _predatorCount > 1 && owner->GetBoidsType() == EBoidsType::FLOCK ? _sum *1.05f : _sum; // increase separation force if predators are neighbors
}

sf::Vector2f MovementComponent::FindCohesion(std::vector<BoidMember*> _boids)
{
    if(owner->GetBoidsType() == EBoidsType::PREDATOR)return sf::Vector2f(0,0);
    sf::Vector2f _sum = sf::Vector2f(0,0);
    const int _size = static_cast<int>(_boids.size());
    float _count = 0;
    for (int i = 0; i < _size; ++i)
    {
        BoidMember* _boid = _boids[i];
        if(!_boid || _boid == owner || _boid->GetBoidsType() != EBoidsType::FLOCK)continue;
        const float _dist = Math::Distance2D(owner->GetPosition(), _boid->GetPosition());
        if(_dist > 0 && _dist < cohesionDistanceLimit) 
        {
            _sum += _boid->GetPosition(); //for this one, sum is only the addition of each neighbors position.
            _count++;
        }
    }
    if(_count > 0)
    {
        _sum = _sum /_count;
        sf::Vector2f _avrgDir;
        _avrgDir = Math::Normalize(_sum - owner->GetPosition());
        _avrgDir *=  speed * owner->GetGameManager()->GetTimeManager()->GetDeltaTime() * cohMult;
        return _avrgDir;
    }

    return _sum;
}

sf::Vector2f MovementComponent::AdaptSumVector(sf::Vector2f _sum, const int& _count, const float& _mult)
{
    _sum /= static_cast<float>(_count);
    if(Math::Magnitude(_sum)> 0) //only if there is magnitude, otherwise there is no neighbor
    {
        _sum = Math::Normalize(_sum); // normalize the sum for easier work material
        _sum *= speed * owner->GetGameManager()->GetTimeManager()->GetDeltaTime() * _mult/*strengthReductionCoef */; //Make the sum as if it was a movement value
    }
    return _sum;
}

void MovementComponent::CheckBorders()
{
    const sf::Vector2f _position = owner->GetPosition();
    const float _lowerMargin = 0 + static_cast<float>(marginDistance);
    const float _upperMarginX = static_cast<float>(windowDimensions.x) - static_cast<float>(marginDistance);
    const float _upperMarginY = static_cast<float>(windowDimensions.y) - static_cast<float>(marginDistance);
    float _mult = 1.2f;
    if(_position.x < _lowerMargin) // movement to reverse direction for each limit of the window.
    {
        velocity.x = velocity.x + emergencyTurnValue.x * owner->GetGameManager()->GetTimeManager()->DeltaTimeSeconds * emergencyTurnMultiplyer * speed;
    }
    
    if (_position.y < _lowerMargin)
    {
        velocity.y = velocity.y + emergencyTurnValue.y * owner->GetGameManager()->GetTimeManager()->DeltaTimeSeconds * emergencyTurnMultiplyer * speed;

    }
    
    if(_position.x > _upperMarginX)
    {
        velocity.x = velocity.x - emergencyTurnValue.x * owner->GetGameManager()->GetTimeManager()->DeltaTimeSeconds * emergencyTurnMultiplyer * speed;
    }
    
    if (_position.y > _upperMarginY)
        velocity.y = velocity.y - emergencyTurnValue.y * owner->GetGameManager()->GetTimeManager()->DeltaTimeSeconds * emergencyTurnMultiplyer * speed;
        
    
    
    
}

void MovementComponent::Rotate()
{
    /*
    // //arcos du (dot * magnitude des 2 vecteurs)
    // const sf::Vector2f _a = Math::Normalize(owner->GetForwardVector());
    //std::cout<<_a.x<<"/"<<_a.y<<std::endl;
    // const sf::Vector2f _b = Math::Normalize(velocity);
    // const float _size = Math::Magnitude(_a) * Math::Magnitude(_b);
    // float _angle = std::acosf(Math::Dot(_a,_b)/_size) * (180 / 3.14f);
    // owner->SetAngle(_angle);

    //90 ou 270
    // sf::Vector2f _pos = owner->GetPosition();
    // const float _futureX = (_pos.x + velocity.x) * 10;
    // const float _futureY = (_pos.y + velocity.y) * 10;
    // //sf::Vector2f _futurePos(_futureX, _futureY);
    
    // std::cout<<"Start angle : "<<owner->GetSprite()->getRotation()<<std::endl;
    // float _angle = std::atan2(_futureY - _pos.y, _futureX - _pos.x);
    // _angle = _angle * 180 / 3.14f;
    // std::cout<<"After calc : "<<_angle<<std::endl;
    // float _startAngle = owner->GetSprite()->getRotation();
    //float _newAngle = _angle > _startAngle ? _startAngle + 1  : _startAngle - 1;
    //owner->GetSprite()->setRotation(_angle);
    //owner->GetSprite()->rotate(_startAngle/_angle);
*/
    float _angleValue =GetAngle(); //Get the new angle value
    _angleValue = velocity.x > 0 ? _angleValue : _angleValue -180; //adapt it to the direction the boid is facing
    owner->SetAngle(_angleValue);
}

void MovementComponent::Move(const float& _deltaTime)
{
    owner->SetPosition(owner->GetPosition() + normalizedVelocity * speed * _deltaTime);
}


void MovementComponent::SetOwner(BoidMember* _owner)
{
    owner = _owner;
}

void MovementComponent::SetSpeed(float _newSpeed)
{
    speed = _newSpeed;
}

void MovementComponent::SetMinSpeed(const float& _newValue)
{
    minSpeed = _newValue;
    if(minSpeed > maxSpeed)
    {
        std::cout<<"Warning : minSpeed was above maxSpeed and was clamped"<<"\n";
        minSpeed = maxSpeed;
    }
}

void MovementComponent::SetMaxSpeed(const float& _newValue)
{
    maxSpeed = _newValue;
    if(minSpeed > maxSpeed)
    {
        std::cout<<"Warning : maxSpeed was beneath minSpeed and was clamped"<<"\n";
        maxSpeed = minSpeed;
    }
}

sf::Vector2f MovementComponent::GetNormalizedVelocity()
{
    normalizedVelocity = Math::Normalize(velocity);
    return normalizedVelocity;
}

void MovementComponent::SetOwnerDirection()
{
    normalizedVelocity = GetNormalizedVelocity();
    const float _dirX = normalizedVelocity.x < 0 ? -1 : 1; //is the boid going right or left ?
    sf::Sprite* _sprite = owner->GetSprite();
    const sf::Vector2f _scaleSprite = _sprite->getScale();
    if(_dirX > 0 && _sprite->getScale().x > 0) //Adpat the scale of the sprite to revert it if needed so that it's facing the right direction
        _sprite->setScale(_scaleSprite.x * -1,_scaleSprite.y);
    if(_dirX < 0 && _sprite->getScale().x < 0)
        _sprite->setScale(_scaleSprite.x * -1,_scaleSprite.y);
        

}

float MovementComponent::GetAngle()
{
    sf::Vector2f _pos = owner->GetPosition();
    const float _futureX = _pos.x + normalizedVelocity.x; // get the future position of the boid
    const float _futureY = _pos.y + normalizedVelocity.y;
    const float _angle = std::atan2(_futureY - _pos.y, _futureX - _pos.x) * 180 / 3.14f;
    return _angle;
}



void MovementComponent::Tick(const float& _deltaTime, std::vector<BoidMember*>& _boids)
{
    if(!owner)return;
    if(!initDone)
        InitMovementComponent();
    alignment = FindAlignment(_boids); // get each value of the flocking method
    cohesion = FindCohesion(_boids);
    separation = FindSeparation(_boids);
    separation *= 1.2f;
    velocity += alignment; // add each of them to the velocity
    velocity += separation;
    velocity += cohesion;
    velocity = Math::Normalize(velocity); // normalize it
    if(owner->GetIsDebug() && owner->GetID() ==0)
        owner->GetDebugShape()->setPosition(owner->GetPosition() + cohesion);
    SetOwnerDirection();
    Move(_deltaTime); // then move the boid with this normalized velocity
    Rotate();
    CheckBorders();

}
