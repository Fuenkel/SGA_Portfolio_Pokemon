#include "stdafx.h"
#include "MainGame.h"

#include "TestScene.h"

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

	SCENE->AddScene("Test", new TestScene);

	// player
	IMAGE->AddImage("Player_battle", "images/trainer.bmp", WINSIZEX / 2, WINSIZEY / 2,
		50 * 3, 60 * 4, 3, 4, true, RGB(255, 200, 106));
	IMAGE->AddImage("Player_portrait", "images/trainerPortrait.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 100, 100, 1, 1, false, RGB(255, 0, 255));

	// pikachu img
	IMAGE->AddImage("Pikachu_portrait", "images/pikachu/portrait.bmp",
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

	// bg
	IMAGE->AddImage("Battle", "images/forest.bmp",
		0, 0, WINSIZEX + WINSIZEX/2, WINSIZEY + WINSIZEY/2, 1, 1, true, RGB(255, 0, 255));

	// effect
	IMAGE->AddImage("Effect_electricity", "images/pikachu/electricity_14x1.bmp", 
		WINSIZEX/2, WINSIZEY/2, 100 * 14, 100, 14, 1, true, RGB(182, 185, 184));
	IMAGE->AddImage("Effect_fire", "images/charmander/fire_12x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 12 * 50, 50, 12, 1, true, RGB(182, 185, 184));

	// ui
	IMAGE->AddImage("UI_open", "images/ui_open.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 200, 100, 1, 1, true, RGB(182, 185, 184));
	IMAGE->AddImage("UI_close", "images/ui_close.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 200, 100, 1, 1, true, RGB(182, 185, 184));

	SCENE->ChangeScene("Test");

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

		sprintf_s(str, "%d %d", g_ptMouse.x, g_ptMouse.y);
		TextOut(GetMemDC(), 10, 10, str, strlen(str));
	}
	//=================================================
	this->SetBackBuffer()->Render(GetHDC());
}
