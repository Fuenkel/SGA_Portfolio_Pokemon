#include "stdafx.h"
#include "MainGame.h"

#include "TestScene.h"
#include "Town1Scene.h"
#include "Town2Scene.h"
#include "ShopScene.h"

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

	IMAGE->AddImage("Player", "images/trainer.bmp", WINSIZEX / 2, WINSIZEY / 2,
		70 * 3, 100 * 4, 3, 4, true, RGB(255, 200, 106));

	//SCENE->AddScene("Test", new TestScene);
	//SCENE->ChangeScene("Test");

	SCENE->AddScene("Town1", new Town1Scene);
	SCENE->AddScene("Town2", new Town2Scene);
	SCENE->AddScene("Shop", new ShopScene);

	SCENE->ChangeScene("Town1");
	//SCENE->ChangeScene("Town2");
	//SCENE->ChangeScene("Shop");

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

	}
	//=================================================
	this->SetBackBuffer()->Render(GetHDC());
}
