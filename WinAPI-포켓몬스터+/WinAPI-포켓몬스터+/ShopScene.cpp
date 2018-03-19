#include "stdafx.h"
#include "ShopScene.h"


ShopScene::ShopScene()
{
}


ShopScene::~ShopScene()
{
}

HRESULT ShopScene::Init()
{
	bg = IMAGE->FindImage("Shop");
	bgPixel = IMAGE->FindImage("ShopPixel");
	player = IMAGE->FindImage("Player");

	playerInfo.Init(DIRECTION_UP, 487, 494, 70, 100);
	playerInfo.SetMoveFrame(PLAYER_IDLE);

	bgX = 0;
	bgY = 0;

	sceneInfo[SCENE3_EXIT].x = 460;
	sceneInfo[SCENE3_EXIT].y = 600;
	sceneInfo[SCENE3_EXIT].width = 105;
	sceneInfo[SCENE3_EXIT].height = 65;
	sceneInfo[SCENE3_EXIT].rc = RectMake(
		sceneInfo[SCENE3_EXIT].x, sceneInfo[SCENE3_EXIT].y,
		sceneInfo[SCENE3_EXIT].width, sceneInfo[SCENE3_EXIT].height);

	return S_OK;
}

void ShopScene::Release()
{
}

void ShopScene::Update()
{
	PlayerMove();
	playerInfo.Probe(bgPixel, bgX, bgY, bgX, bgY);

	if (IntersectRect(&temp, &sceneInfo[SCENE3_EXIT].rc, &playerInfo.GetRect())) {
		playerInfo.SetX(487);
		playerInfo.SetY(494);
		playerInfo.SetDirection(DIRECTION_UP);
		SCENE->ChangeScene("Town2");
	}

	//====================== Debug =====================//
	if (INPUT->GetKeyDown(VK_TAB)) {
		isDebug = !isDebug;
	}
	//==================================================//
}

void ShopScene::Render()
{
	//=================================================
	{
		//bg->Render(GetMemDC());
		bg->Render(GetMemDC(), 0, 0,
			bgX, bgY, WINSIZEX, WINSIZEY);
	}
	//==================   Debug   ====================
	if (isDebug)
	{
		bgPixel->Render(GetMemDC(), 0, 0,
			bgX, bgY, WINSIZEX, WINSIZEY);
		sprintf_s(str, "bg x,y %f %f", bgX, bgY);
		TextOut(GetMemDC(), 10, 10, str, strlen(str));
		sprintf_s(str, "player x,y %f %f", playerInfo.GetX(), playerInfo.GetY());
		TextOut(GetMemDC(), 10, 30, str, strlen(str));
		sprintf_s(str, "mouse : %d %d", g_ptMouse.x, g_ptMouse.y);
		TextOut(GetMemDC(), 10, 50, str, strlen(str));

		RectangleMake(GetMemDC(), sceneInfo[SCENE3_EXIT].rc);
		RectangleMake(GetMemDC(), playerInfo.GetRect());
	}
	//=================================================

	player->FrameRender(GetMemDC(), playerInfo.GetX(), playerInfo.GetY(),
		playerInfo.GetMoveFrame(), playerInfo.GetDirection());
}

void ShopScene::PlayerMove()
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
			if (bgX > 0)
				OtherMove(DIRECTION_RIGHT);
		}
		if (bgX < 0) {
			bgX = 0;
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
			if (bgX < 0)
				OtherMove(DIRECTION_LEFT);
		}
		if (bgX > 0) {
			bgX = 0;
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
			if (bgY > 0)
				OtherMove(DIRECTION_DOWN);
		}
		if (bgY < 0) {
			bgY = 0;
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
			if (bgY < 0)
				OtherMove(DIRECTION_UP);
		}
		if (bgY > 0) {
			bgY = 0;
			playerInfo.AddY(PLAYER_SPEED);
		}
		if ((int)playerInfo.GetMoveFrame() > 2)
			playerInfo.SetMoveFrame(0);
	}
	if (INPUT->GetKeyUp(VK_DOWN)) {
		playerInfo.SetMoveFrame(PLAYER_IDLE);
	}
}

void ShopScene::OtherMove(Direction dir)
{
	//switch (dir)
	//{
	//case DIRECTION_DOWN:
	//	sceneInfo[SCENE3_EXIT].y += PLAYER_SPEED;
	//	break;
	//case DIRECTION_UP:
	//	sceneInfo[SCENE3_EXIT].y -= PLAYER_SPEED;
	//	break;
	//case DIRECTION_LEFT:
	//	sceneInfo[SCENE3_EXIT].x -= PLAYER_SPEED;
	//	break;
	//case DIRECTION_RIGHT:
	//	sceneInfo[SCENE3_EXIT].x += PLAYER_SPEED;
	//	break;
	//}

	//sceneInfo[SCENE3_EXIT].rc = RectMake(
	//	sceneInfo[SCENE3_EXIT].x, sceneInfo[SCENE3_EXIT].y,
	//	sceneInfo[SCENE3_EXIT].width, sceneInfo[SCENE3_EXIT].height);
}
