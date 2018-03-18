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

	IMAGE->AddImage("Shop", "images/shop.bmp", 0, 0, WINSIZEX, WINSIZEY, 1, 1,
		false, RGB(255, 0, 255));
	IMAGE->AddImage("ShopPixel", "images/shopPixel.bmp", 0, 0, WINSIZEX, WINSIZEY, 1, 1,
		false, RGB(255, 0, 255));
	IMAGE->AddImage("Player", "images/trainer.bmp", WINSIZEX/2, WINSIZEY/2, 
		70 * 3, 100 * 4, 3, 4, true, RGB(255, 200, 106));

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

	}
	//=================================================
	this->SetBackBuffer()->Render(GetHDC());
}
