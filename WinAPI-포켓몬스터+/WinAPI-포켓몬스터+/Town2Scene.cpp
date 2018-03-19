#include "stdafx.h"
#include "Town2Scene.h"


Town2Scene::Town2Scene()
{
}


Town2Scene::~Town2Scene()
{
}

HRESULT Town2Scene::Init()
{
	isDebug = false;

	bg = IMAGE->FindImage("Town2");
	bgPixel = IMAGE->FindImage("Town2Pixel");
	player = IMAGE->FindImage("Player");

	playerInfo.Init(DIRECTION_DOWN, WINSIZEX / 2, WINSIZEY / 2, 70, 100);
	playerInfo.SetMoveFrame(PLAYER_IDLE);

	bgX = 200;
	bgY = -50;

	return S_OK;
}

void Town2Scene::Release()
{
}

void Town2Scene::Update()
{
	PlayerMove();
	playerInfo.Probe(bgPixel, bgX, bgY, WINSIZEX + bgX, WINSIZEY + bgY);

	//====================== Debug =====================//
	if (INPUT->GetKeyDown(VK_TAB)) {
		isDebug = !isDebug;
	}
	//==================================================//
}

void Town2Scene::Render()
{
	//=================================================
	{
		//bg->Render(GetMemDC());
		bg->Render(GetMemDC(), 0, 0,
			WINSIZEX + bgX, WINSIZEY + bgY, WINSIZEX, WINSIZEY);
	}
	//==================   Debug   ====================
	if (isDebug)
	{
		bgPixel->Render(GetMemDC(), 0, 0,
			WINSIZEX + bgX, WINSIZEY + bgY, WINSIZEX, WINSIZEY);
		sprintf_s(str, "%f %f", bgX, bgY);
		TextOut(GetMemDC(), 10, 10, str, strlen(str));
	}
	//=================================================

	player->FrameRender(GetMemDC(), playerInfo.GetX(), playerInfo.GetY(),
		playerInfo.GetMoveFrame(), playerInfo.GetDirection());
}

void Town2Scene::PlayerMove()
{
	// left
	if (INPUT->GetKeyDown(VK_LEFT)) {
		playerInfo.SetMoveFrame(PLAYER_IDLE);
		playerInfo.SetDirection(DIRECTION_LEFT);
	}
	if (INPUT->GetKey(VK_LEFT)) {
		playerInfo.AddMoveFrame(0.1f);

		//playerInfo.AddX(-2.5f);

		if (playerInfo.GetX() > WINSIZEX / 2) {
			playerInfo.AddX(-2.5f);
		}
		else {
			bgX -= PLAYER_SPEED;
			if (bgX > -WINSIZEX)
				OtherMove(DIRECTION_RIGHT);
		}
		if (bgX < -WINSIZEX) {
			bgX = -WINSIZEX;
			playerInfo.AddX(-2.5f);
		}
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

		//playerInfo.AddX(2.5f);

		if (playerInfo.GetX() < WINSIZEX / 2) {
			playerInfo.AddX(2.5f);
		}
		else {
			bgX += PLAYER_SPEED;
			if (bgX < WINSIZEX * 2)
				OtherMove(DIRECTION_LEFT);
		}
		if (bgX > WINSIZEX * 2) {
			bgX = WINSIZEX * 2;
			playerInfo.AddX(2.5f);
		}
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
		//playerInfo.AddY(-2.5f);

		if (playerInfo.GetY() > WINSIZEY / 2) {
			playerInfo.AddY(-2.5f);
		}
		else {
			bgY -= PLAYER_SPEED;
			if (bgY > -WINSIZEY)
				OtherMove(DIRECTION_DOWN);
		}
		if (bgY < -WINSIZEY) {
			bgY = -WINSIZEY;
			playerInfo.AddY(-2.5f);
		}
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
		//playerInfo.AddY(2.5f);

		if (playerInfo.GetY() < WINSIZEY / 2) {
			playerInfo.AddY(2.5f);
		}
		else {
			bgY += PLAYER_SPEED;
			if (bgY < WINSIZEY * 2)
				OtherMove(DIRECTION_UP);
		}
		if (bgY > WINSIZEY * 2) {
			bgY = WINSIZEY * 2;
			playerInfo.AddY(2.5f);
		}
		if ((int)playerInfo.GetMoveFrame() > 2)
			playerInfo.SetMoveFrame(0);
	}
	if (INPUT->GetKeyUp(VK_DOWN)) {
		playerInfo.SetMoveFrame(PLAYER_IDLE);
	}
}

void Town2Scene::OtherMove(Direction dir)
{
}
