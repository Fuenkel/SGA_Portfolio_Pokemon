#include "stdafx.h"
#include "MainGame.h"

#include "TestScene.h"
#include "Town1Scene.h"
#include "Town2Scene.h"
#include "ShopScene.h"
#include "TravelScene.h"
#include "BattleScene.h"

MainGame::MainGame()
{
}


MainGame::~MainGame()
{
}

HRESULT MainGame::Init()
{
	GameNode::Init();
	isDebug = false;

	// bg
	IMAGE->AddImage("Town1", "images/town1.bmp", 0, 0,
		WINSIZEX * 2, WINSIZEY * 2, 1, 1, false, RGB(255, 0, 255));
	IMAGE->AddImage("Town1Pixel", "images/town1Pixel.bmp", 0, 0,
		WINSIZEX * 2, WINSIZEY * 2, 1, 1, false, RGB(255, 0, 255));

	IMAGE->AddImage("Town2", "images/town2.bmp", 0, 0,
		WINSIZEX * 4, WINSIZEY * 4, 1, 1, false, RGB(255, 0, 255));
	IMAGE->AddImage("Town2Pixel", "images/town2Pixel.bmp", 0, 0,
		WINSIZEX * 4, WINSIZEY * 4, 1, 1, false, RGB(255, 0, 255));

	IMAGE->AddImage("Shop", "images/shop.bmp", 0, 0,
		WINSIZEX, WINSIZEY, 1, 1, false, RGB(255, 0, 255));
	IMAGE->AddImage("ShopPixel", "images/shopPixel.bmp", 0, 0,
		WINSIZEX, WINSIZEY, 1, 1, false, RGB(255, 0, 255));

	IMAGE->AddImage("Travel", "images/travel.bmp", 0, 0, WINSIZEX, WINSIZEY * 2, 1, 1,
		false, RGB(255, 0, 255));

	IMAGE->AddImage("Battle", "images/forest.bmp",
		0, 0, WINSIZEX + WINSIZEX / 2, WINSIZEY + WINSIZEY / 2, 1, 1, true, RGB(255, 0, 255));

	// player
	IMAGE->AddImage("Player", "images/trainer.bmp", WINSIZEX / 2, WINSIZEY / 2,
		70 * 3, 100 * 4, 3, 4, true, RGB(255, 200, 106));
	IMAGE->AddImage("Player_travel", "images/trainer.bmp", WINSIZEX / 2, WINSIZEY / 2,
		50 * 3, 60 * 4, 3, 4, true, RGB(255, 200, 106));
	IMAGE->AddImage("Player_battle", "images/trainer.bmp", WINSIZEX / 2, WINSIZEY / 2,
		50 * 3, 60 * 4, 3, 4, true, RGB(255, 200, 106));
	IMAGE->AddImage("Player_portrait", "images/trainerPortrait.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 100, 100, 1, 1, false, RGB(255, 0, 255));

	// item
	IMAGE->AddImage("Item_ball", 
		"images/item/ball.bmp", 0, 0, 600, 50, 12, 1, true, RGB(0, 120, 192));
	IMAGE->AddImage("Item_potion",
		"images/item/potion.bmp", 0, 0, 150, 50, 3, 1, true, RGB(0, 120, 192));
	IMAGE->AddImage("Item_potion2",
		"images/item/potion2.bmp", 0, 0, 240, 50, 6, 1, true, RGB(0, 120, 192));
	IMAGE->AddImage("Item_battleBooster", "images/item/battleBooster.bmp",
		0, 0, 350, 50, 7, 1, true, RGB(0, 120, 192));

	// window
	IMAGE->AddImage("Menu", "images/item/menu.bmp", 
		0, 0, 400, 500, 1, 1, false, RGB(255, 0, 255));
	IMAGE->AddImage("Inventory","images/item/inventory.bmp", 
		0, 0, 400, 500, 1, 1, false, RGB(255, 0, 255));
	IMAGE->AddImage("Status", "images/item/status.bmp",
		0, 0, 500, 500, 1, 1, false, RGB(255, 0, 255));

	// pokemon
	// img
	IMAGE->AddImage("Pikachu_img", "images/pikachu/pikachu_img.bmp",
		0, 0, 90, 130, 1, 1, true, RGB(182, 185, 184));
	IMAGE->AddImage("Charmander_img", "images/charmander/charmander_img.bmp",
		0, 0, 90, 130, 1, 1, true, RGB(182, 185, 184));
	IMAGE->AddImage("Squirtle_img", "images/squirtle/squirtle_img.bmp",
		0, 0, 90, 130, 1, 1, true, RGB(182, 185, 184));
	IMAGE->AddImage("Bulbasaur_img", "images/bulbasaur/bulbasaur_img.bmp",
		0, 0, 90, 130, 1, 1, true, RGB(182, 185, 184));

	// pikachu img
	IMAGE->AddImage("Pikachu_portrait", "images/pikachu/portrait.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 100, 100, 1, 1, false, RGB(255, 0, 255));
	IMAGE->AddImage("Pikachu_portrait2", "images/pikachu/portrait2.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 100, 100, 1, 1, false, RGB(255, 0, 255));
	IMAGE->AddImage("Pikachu_idle", "images/pikachu/idle_8x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 400, 50, 8, 1, true, RGB(182, 185, 184));
	IMAGE->AddImage("Pikachu_movement", "images/pikachu/movement_24x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 50 * 24, 50, 24, 1, true, RGB(182, 185, 184));
	IMAGE->AddImage("Pikachu_hurt", "images/pikachu/hurt_8x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 400, 50, 8, 1, true, RGB(182, 185, 184));
	IMAGE->AddImage("Pikachu_attack", "images/pikachu/attack_8x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 400, 50, 8, 1, true, RGB(182, 185, 184));
	IMAGE->AddImage("Pikachu_special_attack", "images/pikachu/special_attack_16x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 50 * 16, 50, 16, 1, true, RGB(182, 185, 184));

	// charmander img
	IMAGE->AddImage("Charmander_portrait", "images/charmander/portrait.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 100, 100, 1, 1, false, RGB(255, 0, 255));
	IMAGE->AddImage("Charmander_portrait2", "images/charmander/portrait2.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 100, 100, 1, 1, false, RGB(255, 0, 255));
	IMAGE->AddImage("Charmander_idle", "images/charmander/idle_8x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 50 * 8, 50, 8, 1, true, RGB(182, 185, 184));
	IMAGE->AddImage("Charmander_movement", "images/charmander/movement_24x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 50 * 24, 50, 24, 1, true, RGB(182, 185, 184));
	IMAGE->AddImage("Charmander_hurt", "images/charmander/hurt_8x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 50 * 8, 50, 8, 1, true, RGB(182, 185, 184));
	IMAGE->AddImage("Charmander_attack", "images/charmander/attack1_24x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 50 * 24, 50, 24, 1, true, RGB(182, 185, 184));
	IMAGE->AddImage("Charmander_special_attack", "images/charmander/special_attack_8x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 8 * 50, 50, 8, 1, true, RGB(182, 185, 184));
	IMAGE->AddImage("Charmander_attack2", "images/charmander/attack2_32x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 50 * 32, 50, 32, 1, true, RGB(182, 185, 184));

	// squirtle img
	IMAGE->AddImage("Squirtle_portrait", "images/squirtle/portrait.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 100, 100, 1, 1, false, RGB(255, 0, 255));
	IMAGE->AddImage("Squirtle_portrait2", "images/squirtle/portrait2.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 100, 100, 1, 1, false, RGB(255, 0, 255));
	IMAGE->AddImage("Squirtle_idle", "images/squirtle/idle_8x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 50 * 8, 50, 8, 1, true, RGB(182, 185, 184));
	IMAGE->AddImage("Squirtle_movement", "images/squirtle/movement_24x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 50 * 24, 50, 24, 1, true, RGB(182, 185, 184));
	IMAGE->AddImage("Squirtle_hurt", "images/squirtle/hurt_8x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 50 * 8, 50, 8, 1, true, RGB(182, 185, 184));
	IMAGE->AddImage("Squirtle_attack", "images/squirtle/attack_24x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 50 * 24, 50, 24, 1, true, RGB(182, 185, 184));
	IMAGE->AddImage("Squirtle_special_attack", "images/squirtle/special_attack_24x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 24 * 50, 50, 24, 1, true, RGB(182, 185, 184));

	// bulbasaur img
	IMAGE->AddImage("Bulbasaur_portrait", "images/bulbasaur/portrait.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 100, 100, 1, 1, false, RGB(255, 0, 255));
	IMAGE->AddImage("Bulbasaur_portrait2", "images/bulbasaur/portrait2.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 100, 100, 1, 1, false, RGB(255, 0, 255));
	IMAGE->AddImage("Bulbasaur_idle", "images/bulbasaur/idle_8x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 50 * 8, 50, 8, 1, true, RGB(182, 185, 184));
	IMAGE->AddImage("Bulbasaur_movement", "images/bulbasaur/movement_24x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 50 * 24, 50, 24, 1, true, RGB(182, 185, 184));
	IMAGE->AddImage("Bulbasaur_hurt", "images/bulbasaur/hurt_8x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 50 * 8, 50, 8, 1, true, RGB(182, 185, 184));
	IMAGE->AddImage("Bulbasaur_attack", "images/bulbasaur/attack_24x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 50 * 24, 50, 24, 1, true, RGB(182, 185, 184));
	IMAGE->AddImage("Bulbasaur_special_attack", "images/bulbasaur/special_attack_16x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 16 * 50, 50, 16, 1, true, RGB(182, 185, 184));

	// pidgey img
	IMAGE->AddImage("Pidgey_portrait", "images/pidgey/portrait.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 100, 100, 1, 1, false, RGB(255, 0, 255));
	IMAGE->AddImage("Pidgey_idle", "images/pidgey/idle_16x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 50 * 16, 50, 16, 1, true, RGB(182, 185, 184));
	IMAGE->AddImage("Pidgey_movement", "images/pidgey/movement_24x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 50 * 24, 50, 24, 1, true, RGB(182, 185, 184));
	IMAGE->AddImage("Pidgey_hurt", "images/pidgey/hurt_8x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 50 * 8, 50, 8, 1, true, RGB(182, 185, 184));
	IMAGE->AddImage("Pidgey_attack", "images/pidgey/attack_24x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 50 * 24, 50, 24, 1, true, RGB(182, 185, 184));
	IMAGE->AddImage("Pidgey_special_attack", "images/pidgey/special_attack_16x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 16 * 50, 50, 16, 1, true, RGB(182, 185, 184));

	// rattata img
	IMAGE->AddImage("Rattata_portrait", "images/rattata/portrait.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 100, 100, 1, 1, false, RGB(255, 0, 255));
	IMAGE->AddImage("Rattata_idle", "images/rattata/idle_16x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 50 * 16, 50, 16, 1, true, RGB(182, 185, 184));
	IMAGE->AddImage("Rattata_movement", "images/rattata/movement_24x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 50 * 24, 50, 24, 1, true, RGB(182, 185, 184));
	IMAGE->AddImage("Rattata_hurt", "images/rattata/hurt_8x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 50 * 8, 50, 8, 1, true, RGB(182, 185, 184));
	IMAGE->AddImage("Rattata_attack", "images/rattata/attack_32x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 50 * 32, 50, 32, 1, true, RGB(182, 185, 184));
	IMAGE->AddImage("Rattata_special_attack", "images/rattata/special_attack_32x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 50 * 32, 50, 32, 1, true, RGB(182, 185, 184));

	// effect
	IMAGE->AddImage("Effect_electricity", "images/pikachu/electricity_14x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 100 * 14, 100, 14, 1, true, RGB(182, 185, 184));
	IMAGE->AddImage("Effect_fire", "images/charmander/fire_12x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 12 * 50, 50, 12, 1, true, RGB(182, 185, 184));
	IMAGE->AddImage("Effect_water", "images/squirtle/water_16x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 16 * 50, 50, 16, 1, true, RGB(182, 185, 184));
	IMAGE->AddImage("Effect_grass", "images/bulbasaur/grass_20x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 20 * 25, 25, 20, 1, true, RGB(182, 185, 184));

	// ui
	IMAGE->AddImage("UI_open", "images/ui_open.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 200, 100, 1, 1, true, RGB(182, 185, 184));
	IMAGE->AddImage("UI_close", "images/ui_close.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 200, 100, 1, 1, true, RGB(182, 185, 184));

	//SCENE->AddScene("Test", new TestScene);
	//SCENE->ChangeScene("Test");

	SCENE->AddScene("Town1", new Town1Scene);
	SCENE->AddScene("Town2", new Town2Scene);
	SCENE->AddScene("Shop", new ShopScene);
	SCENE->AddScene("Travel", new TravelScene);
	SCENE->AddScene("Battle", new BattleScene);

	SCENE->ChangeScene("Town1");
	//SCENE->ChangeScene("Town2");
	//SCENE->ChangeScene("Shop");
	//SCENE->ChangeScene("Travel");
	//SCENE->ChangeScene("Battle");

	return S_OK;
}

void MainGame::Release()
{
	GameNode::Release();
}

void MainGame::Update()
{
	GameNode::Update();

	SCENE->Update();

	//====================== Debug =====================//
	if (INPUT->GetKeyDown(VK_F11)) {
		isDebug = !isDebug;
	}
	//==================================================//
}

void MainGame::Render()
{
	PatBlt(GetMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//=================================================
	{
		SCENE->Render();
	}
	//==================   Debug   ====================
	if (isDebug)
	{
		SetBkMode(GetMemDC(), TRANSPARENT);
		SetTextColor(GetMemDC(), RGB(255, 255, 255));
		sprintf_s(str, "x : %d y : %d", g_ptMouse.x, g_ptMouse.y);
		TextOut(GetMemDC(), 10, 10, str, strlen(str));		
		SetTextColor(GetMemDC(), RGB(0, 0, 0));
	}
	//=================================================
	this->SetBackBuffer()->Render(GetHDC());
}
