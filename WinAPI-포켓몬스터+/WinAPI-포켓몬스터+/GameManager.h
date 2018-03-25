#pragma once

#include "SIngletonBase.h"

#include "Inventory.h"
#include "Item.h"
#include "Pokemon.h"

#define ITEMCOUNT 10

struct tagInvenInfo {
	RECT invenBox;
	tagItemInfo item;
	float x, y;
};

class GameManager : public SingletonBase<GameManager>
{
private:
	Inventory inventory;
	tagInvenInfo invenInfo[ITEMCOUNT];

	vector<Pokemon> pokemonList;

	tagItemInfo currentItem;
	Pokemon currentEnemy;

	int pokemonIndex;
	int selectNum;

	bool showInven;
	bool showStatus;

	bool isDrag;

	int beforeTown;

	int playerLevel;

	RECT invenRc;
	RECT statusBox;
	RECT nextPokemonRc;

	bool isOver;
	bool isStartBattle;
public:
	GameManager();
	~GameManager();

	void Init();
	void Release();

	Inventory& GetInventory() { return inventory; }

	bool GetShowInven() { return showInven; }
	void SetShowInven(bool showInven) { this->showInven = showInven; }

	bool GetShowStatus() { return showStatus; }
	void SetShowStatus(bool showStatus) { this->showStatus = showStatus; }

	bool GetIsDrag() { return isDrag; }
	void SetIsDrag(bool isDrag) { this->isDrag = isDrag; }

	tagInvenInfo& GetInvenInfo(int i) { return invenInfo[i]; }
	tagItemInfo& GetCurrentItem() { return currentItem; }

	RECT GetInvenRc() { return invenRc; }
	RECT GetStatusBox() { return statusBox; }
	RECT GetNextPokemonRc() { return nextPokemonRc; }

	void PokemonInit();
	void PokemonInput(Pokemon pokemon) { pokemonList.push_back(pokemon); }

	Pokemon& GetPokemon(int i) { return pokemonList[i]; }
	int GetPokemonCount() { return pokemonList.size(); }

	void SetSelectNum(int num) { selectNum = num; }
	int GetSelectNum() { return selectNum; }
	int NextSelectNum() {
		int num = GetSelectNum();
		num++;

		if (this->pokemonList.size() == num)
			num = 0;
		if (pokemonList[num].GetDied())
		{
			while (pokemonList[num].GetDied()) {
				num++;
				if (this->pokemonList.size() == num)
					num = 0;
			}
		}
		SetSelectNum(num);
		return num;
	}

	void SetPokemonIndex(int i) { pokemonIndex = i; }
	int GetPokemonIndex() { return pokemonIndex; }
	void NextPokemonIndex() {
		int index = GetPokemonIndex();
		index++;
		if (this->pokemonList.size() == index)
			index = 0;
		SetPokemonIndex(index);
	}

	void SetPlayerLevel(int level) { playerLevel = level; }
	int GetPlayerLevel() { return playerLevel; }
	void AddPlayerLevel(int num) { playerLevel += num; }

	void SetBeforeTown(int num) { beforeTown = num; }
	int GetBeforeTown() { return beforeTown; }

	void SetIsOver(bool isOver) { this->isOver = isOver; }
	bool GetIsOver() { return isOver; }

	void SetCurrentPokemon(Pokemon enemy) { this->currentEnemy = enemy; }
	Pokemon GetCurrentPokemon() { return currentEnemy; }

	void SetIsStartBattle(bool isStart) { this->isStartBattle = isStart; }
	bool GetIsStartBattle() { return isStartBattle; }
};

#define GAME GameManager::GetSingleton()

