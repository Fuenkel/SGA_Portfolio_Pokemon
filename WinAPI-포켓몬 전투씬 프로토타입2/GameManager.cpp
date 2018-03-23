#include "stdafx.h"
#include "GameManager.h"


GameManager::GameManager()
{
	Init();
}


GameManager::~GameManager()
{
}

void GameManager::Init()
{
	inventory.ItemSetup();
	PokemonInit();

	for (int i = 0; i < ITEMCOUNT; i++) {
		invenInfo[i].x = 610;
		invenInfo[i].y = 155 + 40 * i;
		invenInfo[i].invenBox = RectMake(
			invenInfo[i].x, invenInfo[i].y, 325, 40);
		invenInfo[i].item.itemKind = ITEM_EMPTY;
	}

	invenRc = RectMake(
		WINSIZEX - 400 - 50, 100, 400, 500);
	statusBox = RectMake(68, 214, 50, 50);
	nextPokemonRc = RectMake(375, 100, 60, 40);

	inventory.SetGold(10000);

	showInven = false;
	showStatus = false;
	isDrag = false;

	pokemonIndex = 0;
	selectNum = 0;

	playerLevel = 5;

	beforeTown = 1;
}

void GameManager::Release()
{
}

void GameManager::PokemonInit()
{
	//m_name = "파이리";
	//m_level = 8;
	//m_maxHp = 24;
	//m_hp = 24;
	//m_atk = 15;
	//m_def = 14;
	//m_spAtk = 15;
	//m_spDef = 14;
	//m_speed = 15;
	//m_exp = 0;
	//m_maxExp = 419;

	Pokemon temp;

	temp.SetName("파이리");
	temp.SetLevel(5);
	temp.SetMaxHp(39);
	temp.SetHp(39);
	temp.SetAtk(52);
	temp.SetDef(43);
	temp.SetSpAtk(60);
	temp.SetSpDef(50);
	temp.SetSpeed(65);
	temp.SetExp(0);
	temp.SetMaxExp(300);
	temp.SetModel(IMAGE->FindImage("Charmander_img"));
	temp.SetPortrait(IMAGE->FindImage("Charmander_portrait"));
	temp.SetAni(STATUS_IDLE, IMAGE->FindImage("Charmander_idle"));
	temp.SetAniMaxNum(STATUS_IDLE, 1);
	temp.SetAni(STATUS_MOVE, IMAGE->FindImage("Charmander_movement"));
	temp.SetAniMaxNum(STATUS_MOVE, 3);
	temp.SetAni(STATUS_ATTACK, IMAGE->FindImage("Charmander_attack"));
	temp.SetAniMaxNum(STATUS_ATTACK, 3);
	temp.SetAni(STATUS_HURT, IMAGE->FindImage("Charmander_hurt"));
	temp.SetAniMaxNum(STATUS_HURT, 1);
	temp.SetAni(STATUS_SPECIAL_ATTACK,
		IMAGE->FindImage("Charmander_special_attack"));
	temp.SetAniMaxNum(STATUS_SPECIAL_ATTACK, 1);
	temp.SetAni(STATUS_ATTACK2, IMAGE->FindImage("Charmander_attack2"));
	temp.SetAniMaxNum(STATUS_ATTACK2, 4);
	temp.SetEffectNum(EFFECT_FIRE);

	temp.SetAtk(5);
	temp.SetSpAtk(10);

	this->pokemonList.push_back(temp);
	this->pokemonList.push_back(temp);

	temp.SetName("피카츄");
	temp.SetLevel(5);
	temp.SetMaxHp(35);
	temp.SetHp(35);
	temp.SetAtk(55);
	temp.SetDef(40);
	temp.SetSpAtk(50);
	temp.SetSpDef(50);
	temp.SetSpeed(90);
	temp.SetExp(0);
	temp.SetMaxExp(300);
	temp.SetModel(IMAGE->FindImage("Pikachu_img"));
	temp.SetPortrait(IMAGE->FindImage("Pikachu_portrait"));
	temp.SetAni(STATUS_IDLE, IMAGE->FindImage("Pikachu_idle"));
	temp.SetAniMaxNum(STATUS_IDLE, 1);
	temp.SetAni(STATUS_MOVE, IMAGE->FindImage("Pikachu_movement"));
	temp.SetAniMaxNum(STATUS_MOVE, 3);
	temp.SetAni(STATUS_ATTACK, IMAGE->FindImage("Pikachu_attack"));
	temp.SetAniMaxNum(STATUS_ATTACK, 1);
	temp.SetAni(STATUS_HURT, IMAGE->FindImage("Pikachu_hurt"));
	temp.SetAniMaxNum(STATUS_HURT, 1);
	temp.SetAni(STATUS_SPECIAL_ATTACK,
		IMAGE->FindImage("Pikachu_special_attack"));
	temp.SetAniMaxNum(STATUS_SPECIAL_ATTACK, 2);
	temp.SetEffectNum(EFFECT_ELECTRICITY);

	temp.SetAtk(5);
	temp.SetSpAtk(10);

	this->pokemonList.push_back(temp);
	this->pokemonList.push_back(temp);
}

bool GameManager::CheckGameOver()
{
	for (int i = 0; i < pokemonList.size(); i++)
		if (pokemonList[i].GetDied() == false)
			return false;

	return true;
}

