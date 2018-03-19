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

	bg = IMAGE->FindImage("Forest");
	player = IMAGE->FindImage("Player");

	playerInfo.Init(DIRECTION_DOWN, WINSIZEX / 2, WINSIZEY / 2, 70, 100);
	playerInfo.SetMoveFrame(PLAYER_IDLE);

	x = y = 0;

	testX = WINSIZEX / 2;
	testY = WINSIZEY / 2 - 200;
	test = RectMake(testX, testY, 50, 50);

	return S_OK;
}

void TestScene::Release()
{
}

void TestScene::Update()
{
	PlayerMove();

	//if (INPUT->GetKey('W')) { y += 1; }
	//if (INPUT->GetKey('S')) { y -= 1; }
	//if (INPUT->GetKey('A')) { x -= 1; }
	//if (INPUT->GetKey('D')) { x += 1; }

	if (INPUT->GetKeyDown(VK_TAB)) {
		isDebug = !isDebug;
	}
}

void TestScene::Render()
{
	//bg->Render(GetMemDC());'
	bg->Render(GetMemDC(), 0, 0, WINSIZEX / 2 + x, WINSIZEY / 2 + y, WINSIZEX, WINSIZEY);
	//bg->Render(GetMemDC(), 0, 0, playerInfo.GetX(), playerInfo.GetY(), WINSIZEX, WINSIZEY);

	sprintf_s(str, "bg : %f %f", x, y);
	TextOut(GetMemDC(), 10, 10, str, strlen(str));

	sprintf_s(str, "player : %f %f", playerInfo.GetX(), playerInfo.GetY());
	TextOut(GetMemDC(), 10, 30, str, strlen(str));

	if (isDebug) {
		RectangleMake(GetMemDC(), test);
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
		//playerInfo.AddX(-2.5f);
		if (playerInfo.GetX() > WINSIZEX / 2) {
			playerInfo.AddX(-2.5f);
		}
		else {
			x -= SPEED;
			if (x > -WINSIZEX / 2)
				OtherMove(DIRECTION_RIGHT);
		}
		if (x < -WINSIZEX / 2) {
			x = -WINSIZEX / 2;
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
			x += SPEED;
			if (x < WINSIZEX / 2)
				OtherMove(DIRECTION_LEFT);
		}
		if (x > WINSIZEX / 2) {
			x = WINSIZEX / 2;
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
			y -= SPEED;
			if (y > -WINSIZEY / 2)
				OtherMove(DIRECTION_DOWN);
		}
		if (y < -WINSIZEY / 2) {
			y = -WINSIZEY / 2;
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
			y += SPEED;
			if (y < WINSIZEY / 2)
				OtherMove(DIRECTION_UP);
		}
		if (y > WINSIZEY / 2) {
			y = WINSIZEY / 2;
			playerInfo.AddY(2.5f);
		}
		if ((int)playerInfo.GetMoveFrame() > 2)
			playerInfo.SetMoveFrame(0);
	}
	if (INPUT->GetKeyUp(VK_DOWN)) {
		playerInfo.SetMoveFrame(PLAYER_IDLE);
	}
}

void TestScene::OtherMove(Direction dir)
{
	switch (dir)
	{
	case DIRECTION_DOWN:
		testY += SPEED;
		break;
	case DIRECTION_UP:
		testY -= SPEED;
		break;
	case DIRECTION_LEFT:
		testX -= SPEED;
		break;
	case DIRECTION_RIGHT:
		testX += SPEED;
		break;
	}

	test = RectMake(testX, testY, 50, 50);
}

