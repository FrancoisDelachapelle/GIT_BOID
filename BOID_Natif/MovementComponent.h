#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp>

class BoidMember;
class MovementComponent
{
private:
    //owner of the component
    BoidMember* owner = nullptr;
    //array of boids near the owner
    std::vector<BoidMember*> nearBoids;
    //has been init or not
    bool initDone= false;
    
    //window size
    sf::Vector2u windowDimensions = sf::Vector2u();
    //margin before the limit of the window - used to determine when boids must turn around
    int marginDistance = 100;
    //value used to make turn around
    sf::Vector2f emergencyTurnValue = sf::Vector2f();
    //coefficient to strengthen/reduce the turning of the boids
    float emergencyTurnMultiplyer = .08f;

    //the current direction of the boid
    sf::Vector2f direction = sf::Vector2f();
    //the starting velocity of the boid
    sf::Vector2f initalVelocity = sf::Vector2f();
    //the normalized velocity of the boid
    sf::Vector2f normalizedVelocity = sf::Vector2f();
    //the current velocity of the boid
    sf::Vector2f velocity = sf::Vector2f();

    //minimal speed possible for boid
    float minSpeed = 0;
    //maximal speed possible for boid
    float maxSpeed = 400;
    //current speed of the boid
    float speed = 200;
    
    //minimal distance to apply alignment method
    float alignmentDistanceLimit = 130;
    //minimal distance to apply separation method for flock
    float separationDistanceFlockLimit = 80;
    //minimal distance to apply separation method for predator
    float separationDistancePredatorLimit = 220;
    //minimal distance to apply cohesion method
    float cohesionDistanceLimit = 150;
    
    //maximal velocity at start
    int maxRandInitialVelocity = 100;

    //cohesion value to direct boid actions
    sf::Vector2f cohesion = sf::Vector2f();
    //separation value to direct boid actions
    sf::Vector2f separation = sf::Vector2f();
    //alignment value to direct boid actions
    sf::Vector2f alignment = sf::Vector2f();
    //coeff to hard modify the cohesion value
    const float cohMult = 0.02f;
    //coeff to hard modify the separation value
    const float sepMult = 0.05f;
    //coeff to hard modify the alignment value
    const float aliMult = 0.05f;

    
public:
    inline BoidMember* GetOwner() {return owner;}
    inline float GetCohesionDistance() const {return cohesionDistanceLimit;}
    inline float& GetSpeed() {return speed;}
    inline float& GetMinSpeed() {return minSpeed;}
    inline float& GetMaxSpeed() {return maxSpeed;}
public:
    MovementComponent();
    MovementComponent(BoidMember* _owner);
    ~MovementComponent();

private:
    /**
     * \brief Alignment method to determine whether the boid need to align direction with others near it
     * \param _boids : other neighbouring boids
     * \return alignment vector value
     */
    sf::Vector2f FindAlignment(std::vector<BoidMember*> _boids);
    /**
     * \brief Separation method to determine whether the boid need to avoid others near it
     * \param _boids : other neighbouring boids
     * \return separation vector value
     */
    sf::Vector2f FindSeparation(std::vector<BoidMember*> _boids);
    /**
     * \brief Cohesion method to determine whether the boid need to approach others near it
     * \param _boids : other neighbouring boids
     * \return cohesion vector value
     */
    sf::Vector2f FindCohesion(std::vector<BoidMember*> _boids);
    /**
     * \brief DRY method to deal with the sum part of each flocking method
     * \param _sum current sum of vectors
     * \param _count : number of boids influencing the sum
     * \param _mult : hard modifying coef
     * \return the sum once it's been worked on
     */
    sf::Vector2f AdaptSumVector(sf::Vector2f _sum, const int& _count, const float& _mult);
    /**
     * \brief Check whether the boid must turn around or not
     */
    void CheckBorders();
    /**
     * \brief Rotate the boid to look into his movement direction
     */
    void Rotate();
    /**
     * \brief Move the boid along its velocity
     * \param _deltaTime : used to avoid discrepancies in behavior with different computers/configs
     */
    void Move(const float& _deltaTime);
    /**
     * \brief Normalize the velocity
     * \return normalized velocity
     */
    sf::Vector2f GetNormalizedVelocity();
    /**
     * \brief Set the boid direction to update the sprite
     */
    void SetOwnerDirection();
    /**
     * \brief Calculate the angle of the sprite
     * \return the calculated angle
     */
    float GetAngle();

public:
    /**
     * \brief Init the component
     */
    void InitMovementComponent();
    void SetOwner(BoidMember* _owner);
    void SetSpeed(float _newSpeed);
    void SetMinSpeed(const float& _newValue);
    void SetMaxSpeed(const float& _newValue);
    void Tick(const float& _deltaTime, std::vector<BoidMember*>& _boids);
    
};
