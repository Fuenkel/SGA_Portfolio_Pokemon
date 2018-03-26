#pragma once

#include "GameNode.h"

#include "Player.h"
#include "Pokemon.h"

#define SPEED 2.5f
#define POKEMON_COUNT 3

class BattleScene : public GameNode
{
private:
	bool isDebug;

	//float moveFrame;

	Image* bg;
	Image* ui[2];

	Image* effect[EFFECT_END];

	Pokemon pokemon;
	Pokemon enemy[POKEMON_COUNT];

	Player player;

	RECT temp;
	char str[128];
	//float width;

	RECT hpBar[6];
	float hpWidth[6];
	int hpStatus[6];

	RECT enemyHpBar[POKEMON_COUNT];
	float enemyHpWidth[POKEMON_COUNT];
	int enemyHpStatus[POKEMON_COUNT];

	int currentEnemy;

	HFONT hFont;
	HFONT oldFont;

	HBRUSH hBrush;
	HBRUSH hOldBrush;

	COLORREF fullHp;
	COLORREF halfHp;
	COLORREF littleHp;
public:
	BattleScene();
	~BattleScene();

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

	int CalculateAttack(Pokemon attacker, Pokemon defender, Status status);

	void ChangeHpBar();
	void DrawUI();

	bool GameOver();
	bool GameWin();
};

