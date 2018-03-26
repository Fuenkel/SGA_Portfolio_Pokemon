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

	isOver = false;
	isStartBattle = false;

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
	//m_name = "ÆÄÀÌ¸®";
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

	temp.SetName("ÆÄÀÌ¸®");
	temp.SetLevel(5);
	temp.SetMaxHp(39);
	temp.SetHp(1);
	temp.SetAtk(52);
	temp.SetDef(43);
	temp.SetSpAtk(60);
	temp.SetSpDef(50);
	temp.SetSpeed(65);
	temp.SetExp(0);
	temp.SetMaxExp(300);
	temp.SetModel(IMAGE->FindImage("Charmander_img"));
	temp.SetPortrait(0, IMAGE->FindImage("Charmander_portrait"));
	temp.SetPortrait(1, IMAGE->FindImage("Charmander_portrait2"));
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

	temp.SetAtk(3);
	temp.SetSpAtk(10);

	temp.SetAtk(3);
	temp.SetDef(0);
	temp.SetSpAtk(10);
	temp.SetSpDef(3);
	temp.SetSpeed(65);

	this->pokemonList.push_back(temp);

	temp.SetName("ÇÇÄ«Ãò");
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
	temp.SetPortrait(0, IMAGE->FindImage("Pikachu_portrait"));
	temp.SetPortrait(1, IMAGE->FindImage("Pikachu_portrait2"));
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
	temp.SetSpAtk(8);

	temp.SetAtk(5);
	temp.SetDef(0);
	temp.SetSpAtk(8);
	temp.SetSpDef(0);
	temp.SetSpeed(90);

	this->pokemonList.push_back(temp);

	temp.SetName("²¿ºÎ±â");
	temp.SetLevel(5);
	temp.SetMaxHp(44);
	temp.SetHp(44);
	temp.SetAtk(48);
	temp.SetDef(65);
	temp.SetSpAtk(50);
	temp.SetSpDef(64);
	temp.SetSpeed(43);
	temp.SetExp(0);
	temp.SetMaxExp(300);
	temp.SetModel(IMAGE->FindImage("Squirtle_img"));
	temp.SetPortrait(0, IMAGE->FindImage("Squirtle_portrait"));
	temp.SetPortrait(1, IMAGE->FindImage("Squirtle_portrait2"));
	temp.SetAni(STATUS_IDLE, IMAGE->FindImage("Squirtle_idle"));
	temp.SetAniMaxNum(STATUS_IDLE, 1);
	temp.SetAni(STATUS_MOVE, IMAGE->FindImage("Squirtle_movement"));
	temp.SetAniMaxNum(STATUS_MOVE, 3);
	temp.SetAni(STATUS_ATTACK, IMAGE->FindImage("Squirtle_attack"));
	temp.SetAniMaxNum(STATUS_ATTACK, 3);
	temp.SetAni(STATUS_HURT, IMAGE->FindImage("Squirtle_hurt"));
	temp.SetAniMaxNum(STATUS_HURT, 1);
	temp.SetAni(STATUS_SPECIAL_ATTACK,
		IMAGE->FindImage("Squirtle_special_attack"));
	temp.SetAniMaxNum(STATUS_SPECIAL_ATTACK, 3);
	temp.SetEffectNum(EFFECT_WATER);

	temp.SetAtk(2);
	temp.SetDef(3);
	temp.SetSpAtk(10);
	temp.SetSpDef(3);
	temp.SetSpeed(43);

	this->pokemonList.push_back(temp);

	temp.SetName("ÀÌ»óÇØ¾¾");
	temp.SetLevel(5);
	temp.SetMaxHp(45);
	temp.SetHp(45);
	temp.SetAtk(49);
	temp.SetDef(49);
	temp.SetSpAtk(65);
	temp.SetSpDef(65);
	temp.SetSpeed(45);
	temp.SetExp(0);
	temp.SetMaxExp(300);
	temp.SetModel(IMAGE->FindImage("Bulbasaur_img"));
	temp.SetPortrait(0, IMAGE->FindImage("Bulbasaur_portrait"));
	temp.SetPortrait(1, IMAGE->FindImage("Bulbasaur_portrait2"));
	temp.SetAni(STATUS_IDLE, IMAGE->FindImage("Bulbasaur_idle"));
	temp.SetAniMaxNum(STATUS_IDLE, 1);
	temp.SetAni(STATUS_MOVE, IMAGE->FindImage("Bulbasaur_movement"));
	temp.SetAniMaxNum(STATUS_MOVE, 3);
	temp.SetAni(STATUS_ATTACK, IMAGE->FindImage("Bulbasaur_attack"));
	temp.SetAniMaxNum(STATUS_ATTACK, 3);
	temp.SetAni(STATUS_HURT, IMAGE->FindImage("Bulbasaur_hurt"));
	temp.SetAniMaxNum(STATUS_HURT, 1);
	temp.SetAni(STATUS_SPECIAL_ATTACK,
		IMAGE->FindImage("Bulbasaur_special_attack"));
	temp.SetAniMaxNum(STATUS_SPECIAL_ATTACK, 2);
	temp.SetEffectNum(EFFECT_GRASS);

	temp.SetAtk(2);
	temp.SetDef(1);
	temp.SetSpAtk(12);
	temp.SetSpDef(2);
	temp.SetSpeed(45);

	this->pokemonList.push_back(temp);
}

