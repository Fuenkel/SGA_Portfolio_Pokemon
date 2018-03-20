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

	inventory.SetGold(10000);

	showInven = false;
	showStatus = false;
	isDrag = false;
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
	temp.SetLevel(8);
	temp.SetMaxHp(24);
	temp.SetHp(24);
	temp.SetAtk(15);
	temp.SetDef(14);
	temp.SetSpAtk(15);
	temp.SetSpDef(14);
	temp.SetSpeed(15);
	temp.SetExp(0);
	temp.SetMaxExp(419);

	this->pokemonList.push_back(temp);
}

