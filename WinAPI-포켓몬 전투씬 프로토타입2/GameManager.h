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
			NextSelectNum();
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

	bool CheckGameOver();
};

#define GAME GameManager::GetSingleton()

