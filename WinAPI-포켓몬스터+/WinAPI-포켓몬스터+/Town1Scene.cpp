#include "stdafx.h"
#include "Town1Scene.h"


Town1Scene::Town1Scene()
{
}


Town1Scene::~Town1Scene()
{
}

HRESULT Town1Scene::Init()
{
	isDebug = false;

	bg = IMAGE->FindImage("Town1");
	bgPixel = IMAGE->FindImage("Town1Pixel");
	player = IMAGE->FindImage("Player");

	playerInfo.Init(DIRECTION_DOWN, WINSIZEX / 2, WINSIZEY / 2, 70, 100);
	playerInfo.SetMoveFrame(PLAYER_IDLE);

	bgX = bgY = 0;

	return S_OK;
}

void Town1Scene::Release()
{
}

void Town1Scene::Update()
{
	PlayerMove();
	playerInfo.Probe(bgPixel, bgX, bgY, WINSIZEX / 2 + bgX, WINSIZEY / 2 + bgY);

	//====================== Debug =====================//
	if (INPUT->GetKeyDown(VK_TAB)) {
		isDebug = !isDebug;
	}
	//==================================================//
}

void Town1Scene::Render()
{
	//=================================================
	{
		//bg->Render(GetMemDC());
		bg->Render(GetMemDC(), 0, 0, 
			WINSIZEX / 2 + bgX, WINSIZEY / 2 + bgY, WINSIZEX, WINSIZEY);
	}
	//==================   Debug   ====================
	if (isDebug)
	{
		bgPixel->Render(GetMemDC(), 0, 0,
			WINSIZEX / 2 + bgX, WINSIZEY / 2 + bgY, WINSIZEX, WINSIZEY);
		sprintf_s(str, "%f %f", bgX, bgY);
		TextOut(GetMemDC(), 10, 10, str, strlen(str));
	}
	//=================================================

	player->FrameRender(GetMemDC(), playerInfo.GetX(), playerInfo.GetY(),
		playerInfo.GetMoveFrame(), playerInfo.GetDirection());
}

void Town1Scene::PlayerMove()
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
			if (bgX > -WINSIZEX / 2)
				OtherMove(DIRECTION_RIGHT);
		}
		if (bgX < -WINSIZEX / 2) {
			bgX = -WINSIZEX / 2;
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
			if (bgX < WINSIZEX / 2)
				OtherMove(DIRECTION_LEFT);
		}
		if (bgX > WINSIZEX / 2) {
			bgX = WINSIZEX / 2;
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
			if (bgY > -WINSIZEY / 2)
				OtherMove(DIRECTION_DOWN);
		}
		if (bgY < -WINSIZEY / 2) {
			bgY = -WINSIZEY / 2;
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
			if (bgY < WINSIZEY / 2)
				OtherMove(DIRECTION_UP);
		}
		if (bgY > WINSIZEY / 2) {
			bgY = WINSIZEY / 2;
			playerInfo.AddY(2.5f);
		}
		if ((int)playerInfo.GetMoveFrame() > 2)
			playerInfo.SetMoveFrame(0);
	}
	if (INPUT->GetKeyUp(VK_DOWN)) {
		playerInfo.SetMoveFrame(PLAYER_IDLE);
	}
}

void Town1Scene::OtherMove(Direction dir)
{
}
