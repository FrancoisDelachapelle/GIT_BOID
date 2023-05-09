#pragma once
#include <vector>
#include "BoidMember.h"

//class GameManager;
class UIManager;
class BoidManager
{
protected:
	std::vector<BoidMember*> allBoids;
	GameManager* gameManager = nullptr;
	UIManager* uiMgr = nullptr;
	int allBoidsNumber = 0;

//GetterSetters
public:
	std::vector<BoidMember*>& GetAllBoids() {return allBoids;}
	void SetGameManager(GameManager* _gameManager) {gameManager = _gameManager;}
public:
	BoidManager();
	~BoidManager();

private:
	void InitFunctor(BoidMember* _member);

public:
	void AddBoidMember(BoidMember* _toAdd);
	void RemoveBoidMember(BoidMember* _toRemove);
	void RemoveBoidMember(const int& _indexToRemove);
	bool Exist(const BoidMember& _boidMember);
	bool Exist(const int& _index);
	BoidMember* GetBoidMember(const int& _index);
	int GetBoidIndex(const BoidMember& _boidMember);
	void SendBoidInfoToSlider();
	
	

};

