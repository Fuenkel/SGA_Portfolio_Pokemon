#pragma once

#include "GameNode.h"

#include "Player.h"
#include "Pokemon.h"

#define SPEED 2.5f

class TestScene : public GameNode
{
private:
	bool isDebug;

	//float moveFrame;

	Image* bg;
	
	Image* effect[2];

	Pokemon pokemon;
	Pokemon enemy;

	Player player;

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

	void PokemonIdle(Pokemon& pokemon, int maxNum);
	void PokemonMove(Pokemon& pokemon, int maxNum,
		float speed, Direction dir, bool isStart = false);
	void PokemonAttack(Pokemon& pokemon, int maxNum, int idleMaxNum, bool isStart = false);
	void PokemonHurt(Pokemon& pokemon, int maxNum);

	Direction FindDirection(Pokemon& pokemon, Unit& unit);
};

