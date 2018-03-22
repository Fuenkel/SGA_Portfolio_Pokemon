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
	isDebug = false;
	//isToggle = false;
	isExit = false;



	bgY = 0;

	bg = IMAGE->FindImage("Travel");

	player.InitAni(1);
	player.SetAni(0, IMAGE->FindImage("Player_travel"));
	player.Init(DIRECTION_UP, WINSIZEX / 2, WINSIZEY - 100, 40, 50);
	player.SetMoveFrame(PLAYER_IDLE);

	for (int i = 0; i < POKEMON_COUNT; i++) {
		pattern[i] = DIRECTION_LEFT;

		rattata[i].InitAni(3);
		rattata[i].SetAni(STATUS_IDLE, IMAGE->FindImage("Rattata_idle"));
		rattata[i].SetAni(STATUS_MOVE, IMAGE->FindImage("Rattata_movement"));
		rattata[i].SetAni(STATUS_HURT, IMAGE->FindImage("Rattata_hurt"));
		rattata[i].Init(DIRECTION_DOWN, WINSIZEX + i * 100, i * 50, 50, 50);
		rattata[i].SetStatus(STATUS_IDLE);
		rattata[i].SetMoveFrame(0);
		rattata[i].SetName("部房");
		rattata[i].SetLevel(RND->GetFromInto(1,8));

		PokemonMove(rattata[i], 3, 2.5f, pattern[i], true);
	}
	distance = 21000;
	speed = 0;

	exit = RectMake(WINSIZEX / 2 - 100, 0, 200, 30);


	return S_OK;
}

void TestScene::Release()
{
}

void TestScene::Update()
{
	PlayerMove();
	BgMove();

	for (int i = 0; i < POKEMON_COUNT; i++) {
		if (rattata[i].GetDied() == false) {
			// rattata[i]
			switch (rattata[i].GetSatus()) {
			case STATUS_IDLE:
				PokemonIdle(rattata[i], 2);
				break;
			case STATUS_MOVE:
				PokemonMove(rattata[i], 3, 2.5f, pattern[i]);
				break;
			case STATUS_HURT:
				rattata[i].AddAlpha(-1);
				if (rattata[i].GetAlpha() <= 0) {
					rattata[i].SetDied(true);
				}
				break;
			}


			if (rattata[i].GetX() + rattata[i].GetWidth() < 0) {
				if (distance > 0) {
					rattata[i].SetX(i * 70);
					rattata[i].SetY(-rattata[i].GetHeight());
					pattern[i] = DIRECTION_DOWN;
				}
			}
			if (rattata[i].GetY() > WINSIZEY) {
				if (distance > 0) {
					rattata[i].SetX(WINSIZEX);
					rattata[i].SetY(i * 50);
					pattern[i] = DIRECTION_LEFT;
				}
			}
		}

		// test
		//if (INPUT->GetKeyDown('S')) { 
		//	PokemonMove(rattata[i], 3, 2.5f, DIRECTION_DOWN, true);
		//}
		//if (INPUT->GetKeyDown('W')) { 
		//	PokemonMove(rattata[i], 3, 2.5f, DIRECTION_UP, true);
		//}
		//if (INPUT->GetKeyDown('A')) { 
		//	PokemonMove(rattata[i], 3, 2.5f, DIRECTION_LEFT, true);
		//}
		//if (INPUT->GetKeyDown('D')) { 
		//	PokemonMove(rattata[i], 3, 2.5f, DIRECTION_RIGHT, true);
		//}
		//if (INPUT->GetKey('S')) { 
		//	PokemonMove(rattata[i], 3, 2.5f, DIRECTION_DOWN);
		//}
		//if (INPUT->GetKey('W')) { 
		//	PokemonMove(rattata[i], 3, 2.5f, DIRECTION_UP);
		//}
		//if (INPUT->GetKey('A')) { 
		//	PokemonMove(rattata[i], 3, 2.5f, DIRECTION_LEFT);
		//}
		//if (INPUT->GetKey('D')) { 
		//	PokemonMove(rattata[i], 3, 2.5f, DIRECTION_RIGHT); 
		//}
		//if (INPUT->GetKeyUp('S')) { PokemonIdle(rattata[i], 2); }
		//if (INPUT->GetKeyUp('W')) { PokemonIdle(rattata[i], 2); }
		//if (INPUT->GetKeyUp('A')) { PokemonIdle(rattata[i], 2); }
		//if (INPUT->GetKeyUp('D')) { PokemonIdle(rattata[i], 2); }

		// 面倒 眉农
		if (IntersectRect(&temp, &rattata[i].GetRect(), 
			&RectMake(
				player.GetX() + player.GetWidth()/4, 
				player.GetY() + player.GetHeight()/4,
				player.GetWidth()/2, player.GetHeight()/2))
			&& rattata[i].GetDied() == false) {
			if (rattata[i].GetSatus() != STATUS_HURT) {
				switch (player.GetDirection())
				{
				case DIRECTION_DOWN:
					rattata[i].SetDirection(DIRECTION_UP);
					break;
				case DIRECTION_UP:
					rattata[i].SetDirection(DIRECTION_DOWN);
					break;
				case DIRECTION_LEFT:
					rattata[i].SetDirection(DIRECTION_RIGHT);
					break;
				case DIRECTION_RIGHT:
					rattata[i].SetDirection(DIRECTION_LEFT);
					break;
				}
				rattata[i].SetMoveFrame(rattata[i].GetDirection());
				rattata[i].SetStatus(STATUS_HURT);
			}
		}
	}
	if (IntersectRect(&temp, &exit, &player.GetRect())
		&& isExit) {
		Init();
	}

	//====================== Debug =====================//
	if (INPUT->GetKeyDown(VK_TAB)) {
		isDebug = !isDebug;
	}
	//==================================================//
}

void TestScene::Render()
{
	//=================================================
	{
		//bg->Render(GetMemDC());
		bg->LoopRender(GetMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY),
			0, bgY);

		player.GetAni(0)->FrameRender(GetMemDC(), player.GetX(), player.GetY(),
			(int)player.GetMoveFrame(), player.GetDirection());

		//rattata.GetAni(rattata.GetSatus())->FrameRender(GetMemDC(),
		//	rattata.GetX(), rattata.GetY(), (int)rattata.GetMoveFrame(), 0);
		//if (rattata.GetDied() == false) {
		//	rattata.GetAni(rattata.GetSatus())->FrameRender(GetMemDC(),
		//		rattata.GetX(), rattata.GetY(), (int)rattata.GetMoveFrame(), 0,
		//		rattata.GetAlpha());
		//}

		SetBkMode(GetMemDC(), TRANSPARENT);
		SetTextColor(GetMemDC(), RGB(255, 255, 255));

		for (int i = 0; i < POKEMON_COUNT; i++) {
			if (rattata[i].GetDied() == true) continue;
			rattata[i].GetAni(rattata[i].GetSatus())->FrameRender(GetMemDC(),
				rattata[i].GetX(), rattata[i].GetY(), (int)rattata[i].GetMoveFrame(), 0,
				rattata[i].GetAlpha());
			sprintf_s(str, "Lv%d %s", rattata[i].GetLevel(), rattata[i].GetName().c_str());
			TextOut(GetMemDC(), 
				rattata[i].GetX() - 10, rattata[i].GetY() - 10, str, strlen(str));
		}

		sprintf_s(str, "distance : %dm", (int)distance);
		TextOut(GetMemDC(), WINSIZEX - 200, WINSIZEY - 100, str, strlen(str));
		
		sprintf_s(str, "speed : %dkm/h", (int)speed+1);
		TextOut(GetMemDC(), WINSIZEX - 200, WINSIZEY - 50, str, strlen(str));

		SetTextColor(GetMemDC(), RGB(0, 0, 0));
	}
	//==================   Debug   ====================
	if (isDebug)
	{
		RectangleMake(GetMemDC(), exit);
		//RectangleMake(GetMemDC(), player.GetRect());
		RectangleMake(GetMemDC(), RectMake(
			player.GetX() + player.GetWidth() / 4,
			player.GetY() + player.GetHeight() / 4,
			player.GetWidth() / 2, player.GetHeight() / 2));
		for (int i = 0; i < POKEMON_COUNT; i++)
			RectangleMake(GetMemDC(), rattata[i].GetRect());
	}
	//=================================================
}

void TestScene::BgMove()
{
	speed = (WINSIZEY - player.GetY()) / WINSIZEY * PLAYER_SPEED * 3;
	if (distance > 0) {
		bgY -= speed;
		distance -= speed;
	}
	else {
		distance = 0;
		isExit = true;
	}
}

void TestScene::PlayerMove() {
	bool isMoveFrame = true;

	// left
	if (INPUT->GetKeyDown(VK_LEFT)) {
		player.SetMoveFrame(0);
		player.SetDirection(DIRECTION_LEFT);
	}
	if (INPUT->GetKey(VK_LEFT)) {
		if (player.GetDirection() != DIRECTION_LEFT)
			player.SetDirection(DIRECTION_LEFT);
		
		isMoveFrame = true;
		//player.AddMoveFrame(0.1f);

		player.AddX(-PLAYER_SPEED);
		if (player.GetX() < 0)
			player.SetX(0);

		//if (player.GetX() > WINSIZEX / 2) {
		//	player.AddX(-PLAYER_SPEED);
		//}
		//else {
		//	bgX -= PLAYER_SPEED;
		//	if (bgX > -WINSIZEX)
		//		OtherMove(DIRECTION_RIGHT);
		//}
		//if (bgX < -WINSIZEX) {
		//	bgX = -WINSIZEX;
		//	player.AddX(-PLAYER_SPEED);
		//}
		if ((int)player.GetMoveFrame() > 2)
			player.SetMoveFrame(0);
	}
	if (INPUT->GetKeyUp(VK_LEFT)) {
		//player.SetMoveFrame(PLAYER_IDLE);
		//isMoveFrame = false;
		player.SetDirection(DIRECTION_UP);
	}

	// right
	if (INPUT->GetKeyDown(VK_RIGHT)) {
		player.SetMoveFrame(0);
		player.SetDirection(DIRECTION_RIGHT);
	}
	if (INPUT->GetKey(VK_RIGHT)) {
		if (player.GetDirection() != DIRECTION_RIGHT)
			player.SetDirection(DIRECTION_RIGHT);
		
		//player.AddMoveFrame(0.1f);
		isMoveFrame = true;

		player.AddX(PLAYER_SPEED);
		if (player.GetX() + player.GetWidth() > WINSIZEX)
			player.SetX(WINSIZEX - player.GetWidth());
		

		//if (player.GetX() < WINSIZEX / 2) {
		//	player.AddX(PLAYER_SPEED);
		//}
		//else {
		//	bgX += PLAYER_SPEED;
		//	if (bgX < WINSIZEX * 2)
		//		OtherMove(DIRECTION_LEFT);
		//}
		//if (bgX > WINSIZEX * 2) {
		//	bgX = WINSIZEX * 2;
		//	player.AddX(PLAYER_SPEED);
		//}
		if ((int)player.GetMoveFrame() > 2)
			player.SetMoveFrame(0);
	}
	if (INPUT->GetKeyUp(VK_RIGHT)) {
		//player.SetMoveFrame(PLAYER_IDLE);
		//isMoveFrame = false;
		player.SetDirection(DIRECTION_UP);
	}

	// up
	if (INPUT->GetKeyDown(VK_UP)) {
	//if(!isToggle && INPUT->GetKeyDown(VK_SPACE)) {
		player.SetMoveFrame(0);
		player.SetDirection(DIRECTION_UP);
		//isToggle = true;
	}
	if (INPUT->GetKey(VK_UP)) {
	//if(isToggle) {
		if (player.GetDirection() != DIRECTION_UP)
			player.SetDirection(DIRECTION_UP);

		//player.AddMoveFrame(0.1f);
		isMoveFrame = true;

		player.AddY(-PLAYER_SPEED);
		if (player.GetY() < 0)
			player.SetY(0);

		//if (player.GetY() > WINSIZEY / 2) {
		//	player.AddY(-PLAYER_SPEED);
		//}
		//else {
		//	bgY -= PLAYER_SPEED;
		//	if (bgY > -WINSIZEY)
		//		OtherMove(DIRECTION_DOWN);
		//}
		//if (bgY < -WINSIZEY) {
		//	bgY = -WINSIZEY;
		//	player.AddY(-PLAYER_SPEED);
		//}

		//bgY -= PLAYER_SPEED;
		//OtherMove(DIRECTION_DOWN);

		if ((int)player.GetMoveFrame() > 2)
			player.SetMoveFrame(0);
	}
	if (INPUT->GetKeyUp(VK_UP)) {
	//if(isToggle && INPUT->GetKeyDown(VK_SPACE)) {
		//player.SetMoveFrame(PLAYER_IDLE);
		//isMoveFrame = false;
		//isToggle = false;
	}

	// down
	if (INPUT->GetKeyDown(VK_DOWN)) {
		player.SetMoveFrame(0);
		player.SetDirection(DIRECTION_DOWN);
	}
	if (INPUT->GetKey(VK_DOWN)) {
		if (player.GetDirection() != DIRECTION_DOWN)
			player.SetDirection(DIRECTION_DOWN);

		isMoveFrame = true;
		//player.AddMoveFrame(0.1f);
		
		player.AddY(PLAYER_SPEED);
		if (player.GetY() + player.GetHeight() > WINSIZEY)
			player.SetY(WINSIZEY - player.GetHeight());

		//if (player.GetY() < WINSIZEY / 2) {
		//	player.AddY(PLAYER_SPEED);
		//}
		//else {
		//	bgY += PLAYER_SPEED;
		//	if (bgY < WINSIZEY * 2)
		//		OtherMove(DIRECTION_UP);
		//}
		//if (bgY > WINSIZEY * 2) {
		//	bgY = WINSIZEY * 2;
		//	player.AddY(PLAYER_SPEED);
		//}
		if ((int)player.GetMoveFrame() > 2)
			player.SetMoveFrame(0);
	}
	if (INPUT->GetKeyUp(VK_DOWN)) {
		//player.SetMoveFrame(PLAYER_IDLE);
		//isMoveFrame = false;
		player.SetDirection(DIRECTION_UP);
	}

	if (isMoveFrame)
		player.AddMoveFrame(0.1f);

	if(player.GetDirection() == DIRECTION_UP &&
		(int)player.GetMoveFrame() > 2)
		player.SetMoveFrame(0);
}

void TestScene::OtherMove(Direction dir) {

}

void TestScene::PokemonIdle(Pokemon & pokemon, int maxNum)
{
	float moveFrame = 0.05f;

	switch (pokemon.GetDirection())
	{
	case DIRECTION_DOWN:
		if (pokemon.GetSatus() != STATUS_IDLE) {
			pokemon.SetStatus(STATUS_IDLE);
			pokemon.SetMoveFrame(0);
		}
		else {
			pokemon.AddMoveFrame(moveFrame);
			if (pokemon.GetMoveFrame() >= maxNum)
				pokemon.SetMoveFrame(0);
		}
		break;
	case DIRECTION_UP:
		if (pokemon.GetSatus() != STATUS_IDLE) {
			pokemon.SetStatus(STATUS_IDLE);
			pokemon.SetMoveFrame(maxNum);
		}
		else {
			pokemon.AddMoveFrame(moveFrame);
			if (pokemon.GetMoveFrame() >= maxNum * 2
				|| pokemon.GetMoveFrame() < maxNum)
				pokemon.SetMoveFrame(maxNum);
		}
		break;
	case DIRECTION_LEFT:
		if (pokemon.GetSatus() != STATUS_IDLE) {
			pokemon.SetStatus(STATUS_IDLE);
			pokemon.SetMoveFrame(maxNum * 2);
		}
		else {
			pokemon.AddMoveFrame(moveFrame);
			if (pokemon.GetMoveFrame() >= maxNum * 3 
				|| pokemon.GetMoveFrame() < maxNum * 2)
				pokemon.SetMoveFrame(maxNum * 2);
		}
		break;
	case DIRECTION_RIGHT:
		if (pokemon.GetSatus() != STATUS_IDLE) {
			pokemon.SetStatus(STATUS_IDLE);
			pokemon.SetMoveFrame(maxNum * 3);
		}
		else {
			pokemon.AddMoveFrame(moveFrame);
			if (pokemon.GetMoveFrame() >= maxNum * 4
				|| pokemon.GetMoveFrame() < maxNum * 3)
				pokemon.SetMoveFrame(maxNum * 3);
		}
		break;
	}
}

void TestScene::PokemonMove(Pokemon & pokemon, int maxNum, 
	float speed, Direction dir, bool isStart)
{
	if (isStart) {
		if (pokemon.GetSatus() != STATUS_MOVE)
			pokemon.SetStatus(STATUS_MOVE);
		pokemon.SetDirection(dir);
		switch (dir)
		{
		case DIRECTION_DOWN:
			pokemon.SetMoveFrame(0);
			break;
		case DIRECTION_UP:
			pokemon.SetMoveFrame(maxNum);
			break;
		case DIRECTION_LEFT:
			pokemon.SetMoveFrame(maxNum * 2);
			break;
		case DIRECTION_RIGHT:
			pokemon.SetMoveFrame(maxNum * 3);
			break;
		default:
			break;
		}
	}

	if (pokemon.GetDirection() != dir)
		pokemon.SetDirection(dir);

	pokemon.AddMoveFrame(0.1f);

	switch (dir)
	{
	case DIRECTION_DOWN:
		pokemon.AddY(speed);
		if (pokemon.GetMoveFrame() > maxNum)
			pokemon.SetMoveFrame(0);
		break;
	case DIRECTION_UP:
		pokemon.AddY(-speed);
		if (pokemon.GetMoveFrame() > maxNum * 2
			|| pokemon.GetMoveFrame() < maxNum)
			pokemon.SetMoveFrame(maxNum);
		break;
	case DIRECTION_LEFT:
		pokemon.AddX(-speed);
		if (pokemon.GetMoveFrame() > maxNum * 3
			|| pokemon.GetMoveFrame() < maxNum * 2)
			pokemon.SetMoveFrame(maxNum * 2);
		break;
	case DIRECTION_RIGHT:
		pokemon.AddX(speed);
		if (pokemon.GetMoveFrame() > maxNum * 4
			|| pokemon.GetMoveFrame() < maxNum * 3)
			pokemon.SetMoveFrame(maxNum * 3);
		break;
	}
}
