#include "BoidManager.h"
#include <iostream>

#include "GameManager.h"
#include "UIManager.h"

BoidManager::BoidManager()
{
}

BoidManager::~BoidManager()
{
	const int _size = static_cast<int>(allBoids.size());
	for (int i = 0; i < _size; ++i)
	{
		delete allBoids[i];
	}
}

void BoidManager::InitFunctor(BoidMember* _member)
{
	if(!uiMgr)
	{
		uiMgr = gameManager->GetUIManager();
	}
	uiMgr->GetSliderTest()->OnValueChangedF().AddDynamic(_member->GetMovementComponent(), &MovementComponent::SetSpeed);
	//void(*ptrMethod)(float)
}

void BoidManager::AddBoidMember(BoidMember* _toAdd)
{
	if (Exist(*_toAdd))return;
	allBoids.push_back(_toAdd);
	allBoidsNumber++;
}

void BoidManager::RemoveBoidMember(BoidMember* _toRemove)
{
	if (!Exist(*_toRemove))return;
	const int _index = GetBoidIndex(*_toRemove);
	if(_index < 0)
		std::cout<<"Error : index returned -1 and is invalid"<<std::endl;
	const int _size = static_cast<int>(allBoids.size());
	for (int i = _index; i < _size; ++i)
	{
		if(i+1 < _size)
			allBoids[i] = allBoids[i+1];
	}
	allBoids.pop_back();
	allBoidsNumber--;
}

void BoidManager::RemoveBoidMember(const int& _indexToRemove)
{
	if (!Exist(_indexToRemove))return;
	const int _size = static_cast<int>(allBoids.size());
	for (int i = _indexToRemove; i < _size; ++i)
	{
		if(i+1 < _size)
			allBoids[i] = allBoids[i+1];
	}
	delete allBoids.back(); //TODO : check if no conflict with popBack
	allBoids.pop_back();
	allBoidsNumber--;

}

bool BoidManager::Exist(const BoidMember& _boidMember)
{
	const int _size = static_cast<int>(allBoids.size());
	for (int i = 0; i < _size; i++)
	{
		BoidMember* _boid = allBoids[i];
		if (!_boid)continue;
		if (_boid->operator==(_boidMember))
			return true;
	}
	return false;
}

bool BoidManager::Exist(const int& _index)
{
	return _index >= 0 && _index < allBoids.size();
}

BoidMember* BoidManager::GetBoidMember(const int& _index)
{
	if (!Exist(_index))return nullptr;
	return allBoids[_index];
}

int BoidManager::GetBoidIndex(const BoidMember& _boidMember)
{
	const int _size = static_cast<int>(allBoids.size());
	for (int i = 0; i < _size; i++)
	{
		BoidMember* _boid = allBoids[i];
		if (!_boid)continue;
		if (_boid->operator==(_boidMember))
			return i;
	}
	return -1;
}


void BoidManager::SendBoidInfoToSlider()
{
	if(allBoidsNumber < 1)return;
	Slider* _slider = gameManager->GetUIManager()->GetSliderTest();
	if(!_slider)return;
	_slider->SetMinValue(allBoids[0]->GetMovementComponent()->GetMinSpeed());
	_slider->SetMaxValue(allBoids[0]->GetMovementComponent()->GetMaxSpeed());
}
