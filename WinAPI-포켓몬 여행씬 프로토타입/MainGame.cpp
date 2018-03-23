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

	IMAGE->AddImage("Travel", "images/travel.bmp", 0, 0, WINSIZEX, WINSIZEY * 2, 1, 1,
		false, RGB(255, 0, 255));

	IMAGE->AddImage("Player_travel", "images/trainer.bmp", WINSIZEX / 2, WINSIZEY / 2,
		40 * 3, 50 * 4, 3, 4, true, RGB(255, 200, 106));

	IMAGE->AddImage("Rattata_idle", "images/rattata/idle_16x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 50 * 16, 50, 16, 1, true, RGB(182, 185, 184));
	IMAGE->AddImage("Rattata_movement", "images/rattata/movement_24x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 50 * 24, 50, 24, 1, true, RGB(182, 185, 184));
	IMAGE->AddImage("Rattata_hurt", "images/rattata/hurt_8x1.bmp",
		WINSIZEX / 2, WINSIZEY / 2, 50 * 8, 50, 8, 1, true, RGB(182, 185, 184));

	SCENE->AddScene("Test", new TestScene);

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
		sprintf_s(str, "%d %d", g_ptMouse.x, g_ptMouse.y);
		TextOut(GetMemDC(), 10, 10, str, strlen(str));
	}
	//=================================================
	this->SetBackBuffer()->Render(GetHDC());
}
