#include "stdafx.h"
#include "TestScene.h"


TestScene::TestScene()
{
}


TestScene::~TestScene()
{
}

HRESULT TestScene::Init()
{
	isDebug = true;

	bg = IMAGE->FindImage("Shop");
	bgPixel = IMAGE->FindImage("ShopPixel");
	player = IMAGE->FindImage("Player");

	playerInfo.Init(DIRECTION_DOWN, WINSIZEX / 2, WINSIZEY / 2, 70, 100);
	playerInfo.SetMoveFrame(PLAYER_IDLE);

	return S_OK;
}

void TestScene::Release()
{
}

void TestScene::Update()
{
	PlayerMove();
	playerInfo.Probe(bgPixel);

	if (INPUT->GetKeyDown(VK_TAB)) {
		isDebug = !isDebug;
	}
}

void TestScene::Render()
{
	bg->Render(GetMemDC());

	if (isDebug) {
		bgPixel->Render(GetMemDC());
	}

	player->FrameRender(GetMemDC(), playerInfo.GetX(), playerInfo.GetY(), 
		playerInfo.GetMoveFrame(), playerInfo.GetDirection());
}

void TestScene::PlayerMove()
{
	// left
	if (INPUT->GetKeyDown(VK_LEFT)) {
		playerInfo.SetMoveFrame(PLAYER_IDLE);
		playerInfo.SetDirection(DIRECTION_LEFT);
	}
	if (INPUT->GetKey(VK_LEFT)) {
		playerInfo.AddMoveFrame(0.1f);
		playerInfo.AddX(-2.5f);
		if ((int)playerInfo.GetMoveFrame() > 2)
			playerInfo.SetMoveFrame(0);
	}
	if (INPUT->GetKeyUp(VK_LEFT)) {
		playerInfo.SetMoveFrame(PLAYER_IDLE);
	}

	// right
	if (INPUT->GetKeyDown(VK_RIGHT)) {
		playerInfo.SetMoveFrame(PLAYER_IDLE);
		playerInfo.SetDirection(DIRECTION_RIGHT);
	}
	if (INPUT->GetKey(VK_RIGHT)) {
		playerInfo.AddMoveFrame(0.1f);
		playerInfo.AddX(2.5f);
		if ((int)playerInfo.GetMoveFrame() > 2)
			playerInfo.SetMoveFrame(0);
	}
	if (INPUT->GetKeyUp(VK_RIGHT)) {
		playerInfo.SetMoveFrame(PLAYER_IDLE);
	}

	// up
	if (INPUT->GetKeyDown(VK_UP)) {
		playerInfo.SetMoveFrame(PLAYER_IDLE);
		playerInfo.SetDirection(DIRECTION_UP);
	}
	if (INPUT->GetKey(VK_UP)) {
		playerInfo.AddMoveFrame(0.1f);
		playerInfo.AddY(-2.5f);
		if ((int)playerInfo.GetMoveFrame() > 2)
			playerInfo.SetMoveFrame(0);
	}
	if (INPUT->GetKeyUp(VK_UP)) {
		playerInfo.SetMoveFrame(PLAYER_IDLE);
	}

	// down
	if (INPUT->GetKeyDown(VK_DOWN)) {
		playerInfo.SetMoveFrame(PLAYER_IDLE);
		playerInfo.SetDirection(DIRECTION_DOWN);
	}
	if (INPUT->GetKey(VK_DOWN)) {
		playerInfo.AddMoveFrame(0.1f);
		playerInfo.AddY(2.5f);
		if ((int)playerInfo.GetMoveFrame() > 2)
			playerInfo.SetMoveFrame(0);
	}
	if (INPUT->GetKeyUp(VK_DOWN)) {
		playerInfo.SetMoveFrame(PLAYER_IDLE);
	}
}
