#pragma once

#include "GameNode.h"

#include "Pokemon.h"

#define SPEED 2.5f

class TestScene : public GameNode
{
private:
	bool isDebug;

	//float moveFrame;
	
	Image* pikachu[5];
	Image* charmander[6];
	Image* effect[2];

	Pokemon pokemon;
	Pokemon enemy;

	RECT temp;
public:
	TestScene();
	~TestScene();

	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;

	void Idle();
	void Move();
	void Attack();
};

