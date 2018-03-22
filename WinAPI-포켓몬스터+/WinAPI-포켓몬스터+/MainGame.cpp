#include "stdafx.h"
#include "MainGame.h"

#include "TestScene.h"
#include "Town1Scene.h"
#include "Town2Scene.h"
#include "ShopScene.h"
#include "TravelScene.h"

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

	// player
	IMAGE->AddImage("Player", "images/trainer.bmp", WINSIZEX / 2, WINSIZEY / 2,
		70 * 3, 100 * 4, 3, 4, true, RGB(255, 200, 106));
	IMAGE->AddImage("Player_travel", "images/trainer.bmp", WINSIZEX / 2, WINSIZEY / 2,
		50 * 3, 60 * 4, 3, 4, true, RGB(255, 200, 106));

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
	IMAGE->AddImage("Pikachu_img", "images/pikachu/pikachu_img.bmp",
		0, 0, 90, 130, 1, 1, true, RGB(182, 185, 184));
	IMAGE->AddImage("Charmander_img", "images/charmander/charmander_img.bmp",
		0, 0, 90, 130, 1, 1, true, RGB(182, 185, 184));

	// rattata
	IMAGE->AddImage("Rattata_idle", "images/rattata/idle_16x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 50 * 16, 50, 16, 1, true, RGB(182, 185, 184));
	IMAGE->AddImage("Rattata_movement", "images/rattata/movement_24x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 50 * 24, 50, 24, 1, true, RGB(182, 185, 184));
	IMAGE->AddImage("Rattata_hurt", "images/rattata/hurt_8x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 50 * 8, 50, 8, 1, true, RGB(182, 185, 184));

	//SCENE->AddScene("Test", new TestScene);
	//SCENE->ChangeScene("Test");

	SCENE->AddScene("Town1", new Town1Scene);
	SCENE->AddScene("Town2", new Town2Scene);
	SCENE->AddScene("Shop", new ShopScene);
	SCENE->AddScene("Travel", new TravelScene);

	SCENE->ChangeScene("Town1");
	//SCENE->ChangeScene("Town2");
	//SCENE->ChangeScene("Shop");
	//SCENE->ChangeScene("Travel");

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
		SetTextColor(GetMemDC(), RGB(255, 255, 255));
		sprintf_s(str, "x : %d y : %d", g_ptMouse.x, g_ptMouse.y);
		TextOut(GetMemDC(), 10, 10, str, strlen(str));		
		SetTextColor(GetMemDC(), RGB(0, 0, 0));
	}
	//=================================================
	this->SetBackBuffer()->Render(GetHDC());
}
