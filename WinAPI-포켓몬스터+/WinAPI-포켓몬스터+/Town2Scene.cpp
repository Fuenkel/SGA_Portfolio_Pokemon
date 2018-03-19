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

	playerInfo.Init(DIRECTION_UP, WINSIZEX / 2, 550, 70, 100);
	playerInfo.SetMoveFrame(PLAYER_IDLE);

	bgX = 445;
	bgY = 1536;

	sceneInfo[SCENE2_EXIT].x = 385;
	sceneInfo[SCENE2_EXIT].y = WINSIZEY - 50;
	sceneInfo[SCENE2_EXIT].width = 310;
	sceneInfo[SCENE2_EXIT].height = 50;
	sceneInfo[SCENE2_EXIT].rc = RectMake(
		sceneInfo[SCENE2_EXIT].x, sceneInfo[SCENE2_EXIT].y,
		sceneInfo[SCENE2_EXIT].width, sceneInfo[SCENE2_EXIT].height);

	sceneInfo[SCENE2_SHOP].x = WINSIZEX / 2 + 1035;
	sceneInfo[SCENE2_SHOP].y = 550 - (1536-386 + 550-380) - 70;
	sceneInfo[SCENE2_SHOP].width = 75;
	sceneInfo[SCENE2_SHOP].height = 75;
	sceneInfo[SCENE2_SHOP].rc = RectMake(
		sceneInfo[SCENE2_SHOP].x, sceneInfo[SCENE2_SHOP].y,
		sceneInfo[SCENE2_SHOP].width, sceneInfo[SCENE2_SHOP].height);

	return S_OK;
}

void Town2Scene::Release()
{
}

void Town2Scene::Update()
{
	PlayerMove();
	playerInfo.Probe(bgPixel, bgX, bgY, WINSIZEX + bgX, WINSIZEY + bgY);

	if (IntersectRect(&temp, &sceneInfo[SCENE2_EXIT].rc, &playerInfo.GetRect())) {
		bgX = 445;
		bgY = 1536;
		playerInfo.SetX(512);
		playerInfo.SetY(550);
		playerInfo.SetDirection(DIRECTION_UP);
		SCENE->ChangeScene("Town1");
	}

	if (IntersectRect(&temp, &sceneInfo[SCENE2_SHOP].rc, &playerInfo.GetRect())) {
		bgX = 1485.0f;
		bgY = 386.0f;
		playerInfo.SetX(512);
		playerInfo.SetY(385);
		playerInfo.SetDirection(DIRECTION_DOWN);
		SCENE->ChangeScene("Shop");
	}

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
		sprintf_s(str, "bg x,y %f %f", bgX, bgY);
		TextOut(GetMemDC(), 10, 10, str, strlen(str));
		sprintf_s(str, "player x,y %f %f", playerInfo.GetX(), playerInfo.GetY());
		TextOut(GetMemDC(), 10, 30, str, strlen(str));
		sprintf_s(str, "mouse : %d %d", g_ptMouse.x, g_ptMouse.y);
		TextOut(GetMemDC(), 10, 50, str, strlen(str));

		RectangleMake(GetMemDC(), sceneInfo[SCENE2_EXIT].rc);
		RectangleMake(GetMemDC(), sceneInfo[SCENE2_SHOP].rc);
		RectangleMake(GetMemDC(), playerInfo.GetRect());
	}
	//=================================================

	player->FrameRender(GetMemDC(), playerInfo.GetX(), playerInfo.GetY(),
		playerInfo.GetMoveFrame(), playerInfo.GetDirection());
}

void Town2Scene::PlayerMove()
{
	// left
	if (INPUT->GetKeyDown(VK_LEFT)) {
		playerInfo.SetMoveFrame(0);
		playerInfo.SetDirection(DIRECTION_LEFT);
	}
	if (INPUT->GetKey(VK_LEFT)) {
		if (playerInfo.GetDirection() != DIRECTION_LEFT)
			playerInfo.SetDirection(DIRECTION_LEFT);
		playerInfo.AddMoveFrame(0.1f);

		//playerInfo.AddX(-2.5f);

		if (playerInfo.GetX() > WINSIZEX / 2) {
			playerInfo.AddX(-PLAYER_SPEED);
		}
		else {
			bgX -= PLAYER_SPEED;
			if (bgX > -WINSIZEX)
				OtherMove(DIRECTION_RIGHT);
		}
		if (bgX < -WINSIZEX) {
			bgX = -WINSIZEX;
			playerInfo.AddX(-PLAYER_SPEED);
		}
		if ((int)playerInfo.GetMoveFrame() > 2)
			playerInfo.SetMoveFrame(0);
	}
	if (INPUT->GetKeyUp(VK_LEFT)) {
		playerInfo.SetMoveFrame(PLAYER_IDLE);
	}

	// right
	if (INPUT->GetKeyDown(VK_RIGHT)) {
		playerInfo.SetMoveFrame(0);
		playerInfo.SetDirection(DIRECTION_RIGHT);
	}
	if (INPUT->GetKey(VK_RIGHT)) {
		if (playerInfo.GetDirection() != DIRECTION_RIGHT)
			playerInfo.SetDirection(DIRECTION_RIGHT);
		playerInfo.AddMoveFrame(0.1f);

		//playerInfo.AddX(2.5f);

		if (playerInfo.GetX() < WINSIZEX / 2) {
			playerInfo.AddX(PLAYER_SPEED);
		}
		else {
			bgX += PLAYER_SPEED;
			if (bgX < WINSIZEX * 2)
				OtherMove(DIRECTION_LEFT);
		}
		if (bgX > WINSIZEX * 2) {
			bgX = WINSIZEX * 2;
			playerInfo.AddX(PLAYER_SPEED);
		}
		if ((int)playerInfo.GetMoveFrame() > 2)
			playerInfo.SetMoveFrame(0);
	}
	if (INPUT->GetKeyUp(VK_RIGHT)) {
		playerInfo.SetMoveFrame(PLAYER_IDLE);
	}

	// up
	if (INPUT->GetKeyDown(VK_UP)) {
		playerInfo.SetMoveFrame(0);
		playerInfo.SetDirection(DIRECTION_UP);
	}
	if (INPUT->GetKey(VK_UP)) {
		if (playerInfo.GetDirection() != DIRECTION_UP)
			playerInfo.SetDirection(DIRECTION_UP);

		playerInfo.AddMoveFrame(0.1f);
		//playerInfo.AddY(-2.5f);

		if (playerInfo.GetY() > WINSIZEY / 2) {
			playerInfo.AddY(-PLAYER_SPEED);
		}
		else {
			bgY -= PLAYER_SPEED;
			if (bgY > -WINSIZEY)
				OtherMove(DIRECTION_DOWN);
		}
		if (bgY < -WINSIZEY) {
			bgY = -WINSIZEY;
			playerInfo.AddY(-PLAYER_SPEED);
		}
		if ((int)playerInfo.GetMoveFrame() > 2)
			playerInfo.SetMoveFrame(0);
	}
	if (INPUT->GetKeyUp(VK_UP)) {
		playerInfo.SetMoveFrame(PLAYER_IDLE);
	}

	// down
	if (INPUT->GetKeyDown(VK_DOWN)) {
		playerInfo.SetMoveFrame(0);
		playerInfo.SetDirection(DIRECTION_DOWN);
	}
	if (INPUT->GetKey(VK_DOWN)) {
		if (playerInfo.GetDirection() != DIRECTION_DOWN)
			playerInfo.SetDirection(DIRECTION_DOWN);

		playerInfo.AddMoveFrame(0.1f);
		//playerInfo.AddY(2.5f);

		if (playerInfo.GetY() < WINSIZEY / 2) {
			playerInfo.AddY(PLAYER_SPEED);
		}
		else {
			bgY += PLAYER_SPEED;
			if (bgY < WINSIZEY * 2)
				OtherMove(DIRECTION_UP);
		}
		if (bgY > WINSIZEY * 2) {
			bgY = WINSIZEY * 2;
			playerInfo.AddY(PLAYER_SPEED);
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
	switch (dir)
	{
	case DIRECTION_DOWN:
		sceneInfo[SCENE2_EXIT].y += PLAYER_SPEED;
		sceneInfo[SCENE2_SHOP].y += PLAYER_SPEED;
		break;
	case DIRECTION_UP:
		sceneInfo[SCENE2_EXIT].y -= PLAYER_SPEED;
		sceneInfo[SCENE2_SHOP].y -= PLAYER_SPEED;
		break;
	case DIRECTION_LEFT:
		sceneInfo[SCENE2_EXIT].x -= PLAYER_SPEED;
		sceneInfo[SCENE2_SHOP].x -= PLAYER_SPEED;
		break;
	case DIRECTION_RIGHT:
		sceneInfo[SCENE2_EXIT].x += PLAYER_SPEED;
		sceneInfo[SCENE2_SHOP].x += PLAYER_SPEED;
		break;
	}

	sceneInfo[SCENE2_EXIT].rc = RectMake(
		sceneInfo[SCENE2_EXIT].x, sceneInfo[SCENE2_EXIT].y,
		sceneInfo[SCENE2_EXIT].width, sceneInfo[SCENE2_EXIT].height);

	sceneInfo[SCENE2_SHOP].rc = RectMake(
		sceneInfo[SCENE2_SHOP].x, sceneInfo[SCENE2_SHOP].y,
		sceneInfo[SCENE2_SHOP].width, sceneInfo[SCENE2_SHOP].height);
}
