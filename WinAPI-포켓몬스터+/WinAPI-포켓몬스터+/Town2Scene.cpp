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
	isDrag = false;

	bg = IMAGE->FindImage("Town2");
	bgPixel = IMAGE->FindImage("Town2Pixel");
	player = IMAGE->FindImage("Player");

	ball = IMAGE->FindImage("Item_ball");
	potion = IMAGE->FindImage("Item_potion");
	potion2 = IMAGE->FindImage("Item_potion2");
	booster = IMAGE->FindImage("Item_battleBooster");

	inventory = IMAGE->FindImage("Inventory");
	status = IMAGE->FindImage("Status");

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

	UpdateItem();

	return S_OK;
}

void Town2Scene::Release()
{
}

void Town2Scene::Update()
{
	if (GAME->GetShowInven() == false) {
		PlayerMove();
		playerInfo.Probe(bgPixel, bgX, bgY, WINSIZEX + bgX, WINSIZEY + bgY);
	}

	if (INPUT->GetKeyDown('I')) {
		GAME->SetShowInven(!GAME->GetShowInven());
	}

	if (INPUT->GetKeyDown('C')) {
		GAME->SetShowStatus(!GAME->GetShowStatus());
	}

	// 아이템 구매와 드래그 시작
	if (INPUT->GetKeyDown(VK_LBUTTON)) {
		// 포켓몬 변경
		if (GAME->GetShowStatus()) {
			if (PtInRect(&GAME->GetNextPokemonRc(), g_ptMouse))
				GAME->NextPokemonIndex();
		}

		if (GAME->GetShowStatus() && GAME->GetShowInven()) {
			// 아이템 해제 시작
			if (PtInRect(&GAME->GetStatusBox(), g_ptMouse)) {
				isDrag = true;
				GAME->GetCurrentItem() =
					GAME->GetPokemon(GAME->GetPokemonIndex()).GetEquipItem();
			}

			// 아이템 장착 시작
			for (int i = 0; i < ITEMCOUNT; i++) {
				if (PtInRect(&GAME->GetInvenInfo(i).invenBox, g_ptMouse)) {
					if (GAME->GetInvenInfo(i).item.itemKind >= BOOSTER_CRITICALCUTTER) {
						isDrag = true;
						GAME->GetCurrentItem() = GAME->GetInvenInfo(i).item;
					}
				}
			}
		}
	}

	// 드래그 끝 아이템 장착 혹은 해제
	if (INPUT->GetKeyUp(VK_LBUTTON) && GAME->GetShowStatus()
		&& GAME->GetShowInven()) {
		// 아이템 해제
		if (PtInRect(&GAME->GetInvenRc(), g_ptMouse) &&
			GAME->GetCurrentItem().name.compare(
				GAME->GetPokemon(
					GAME->GetPokemonIndex()).GetEquipItem().name) == 0) {
			GAME->GetPokemon(GAME->GetPokemonIndex()).EquipItem(-1);
			UpdateItem();
		}

		// 아이템 장착
		if (PtInRect(&GAME->GetStatusBox(), g_ptMouse)) {
			for (int i = 0; i < ITEMCOUNT; i++) {
				if (GAME->GetInvenInfo(i).item.name.compare(
					GAME->GetCurrentItem().name) == 0) {
					GAME->GetPokemon(GAME->GetPokemonIndex()).EquipItem(i);
					UpdateItem();
					break;
				}
			}
		}

		isDrag = false;
	}

	if (IntersectRect(&temp, &sceneInfo[SCENE2_EXIT].rc, &playerInfo.GetRect())) {
		bgX = 445;
		bgY = 1536;
		playerInfo.SetX(512);
		playerInfo.SetY(550);
		playerInfo.SetDirection(DIRECTION_UP);
		//SCENE->ChangeScene("Town1");
		GAME->SetBeforeTown(2);
		SCENE->ChangeScene("Travel");
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
		if (isDebug) {
			bgPixel->Render(GetMemDC(), 0, 0,
				WINSIZEX + bgX, WINSIZEY + bgY, WINSIZEX, WINSIZEY);
		}

		player->FrameRender(GetMemDC(), playerInfo.GetX(), playerInfo.GetY(),
			playerInfo.GetMoveFrame(), playerInfo.GetDirection());

		SetBkMode(GetMemDC(), TRANSPARENT);
		SetTextColor(GetMemDC(), RGB(0, 0, 0));

		if (GAME->GetShowStatus()) {
			BeginCreateFont(GetMemDC(), &hFont, 30);
			oldFont = (HFONT)SelectObject(GetMemDC(), hFont);

			SetTextColor(GetMemDC(), RGB(255, 255, 255));
			status->AlphaRender(GetMemDC(), 50, 100, 225);

			GAME->GetPokemon(GAME->GetPokemonIndex()).
				GetPortrait(0)->Render(GetMemDC(), 138, 236);

			sprintf_s(str, "%d", GAME->GetPokemon(
				GAME->GetPokemonIndex()).GetLevel());
			TextOut(GetMemDC(), 85, 162, str, strlen(str));

			sprintf_s(str, "%s", GAME->GetPokemon(
				GAME->GetPokemonIndex()).GetName().c_str());
			TextOut(GetMemDC(), 140, 162, str, strlen(str));

			SetTextColor(GetMemDC(), RGB(0, 0, 0));
			sprintf_s(str, "%d / %d",
				GAME->GetPokemon(GAME->GetPokemonIndex()).GetHp(),
				GAME->GetPokemon(GAME->GetPokemonIndex()).GetMaxHp());
			TextOut(GetMemDC(), 430, 165, str, strlen(str));

			sprintf_s(str, "%d",
				GAME->GetPokemon(GAME->GetPokemonIndex()).GetAtk());
			TextOut(GetMemDC(), 495, 225, str, strlen(str));

			sprintf_s(str, "%d",
				GAME->GetPokemon(GAME->GetPokemonIndex()).GetDef());
			TextOut(GetMemDC(), 495, 265, str, strlen(str));

			sprintf_s(str, "%d",
				GAME->GetPokemon(GAME->GetPokemonIndex()).GetSpAtk());
			TextOut(GetMemDC(), 495, 305, str, strlen(str));

			sprintf_s(str, "%d",
				GAME->GetPokemon(GAME->GetPokemonIndex()).GetSpDef());
			TextOut(GetMemDC(), 495, 345, str, strlen(str));

			sprintf_s(str, "%d",
				GAME->GetPokemon(GAME->GetPokemonIndex()).GetSpeed());
			TextOut(GetMemDC(), 495, 385, str, strlen(str));

			sprintf_s(str, "%8d",
				GAME->GetPokemon(GAME->GetPokemonIndex()).GetExp());
			TextOut(GetMemDC(), 430, 425, str, strlen(str));

			sprintf_s(str, "%8d",
				GAME->GetPokemon(GAME->GetPokemonIndex()).GetMaxExp());
			TextOut(GetMemDC(), 430, 465, str, strlen(str));

			tagItemInfo tempItem =
				GAME->GetPokemon(GAME->GetPokemonIndex()).GetEquipItem();

			SetTextColor(GetMemDC(), RGB(255, 0, 0));

			if (tempItem.itemKind != ITEM_EMPTY) {
				switch (tempItem.itemKind) {
				case BOOSTER_PLUSPOWER:
					sprintf_s(str, "+ %d", tempItem.attribute);
					TextOut(GetMemDC(), 405, 225, str, strlen(str));
					booster->FrameRender(GetMemDC(), 68, 214,
						tempItem.itemKind - 9, 0);
					break;
				case BOOSTER_DEFENDUP:
					sprintf_s(str, "+ %d", tempItem.attribute);
					TextOut(GetMemDC(), 405, 265, str, strlen(str));
					booster->FrameRender(GetMemDC(), 68, 214,
						tempItem.itemKind - 9, 0);
					break;
				case BOOSTER_SPECIALUP:
					sprintf_s(str, "+ %d", tempItem.attribute);
					TextOut(GetMemDC(), 405, 305, str, strlen(str));
					booster->FrameRender(GetMemDC(), 68, 214,
						tempItem.itemKind - 9, 0);
					break;
				case BOOSTER_SPECIALGUARD:
					sprintf_s(str, "+ %d", tempItem.attribute);
					TextOut(GetMemDC(), 405, 345, str, strlen(str));
					booster->FrameRender(GetMemDC(), 68, 214,
						tempItem.itemKind - 9, 0);
					break;
				case BOOSTER_SPEEDUP:
					sprintf_s(str, "+ %d", tempItem.attribute);
					TextOut(GetMemDC(), 405, 385, str, strlen(str));
					booster->FrameRender(GetMemDC(), 68, 214,
						tempItem.itemKind - 9, 0);
					break;
				case BOOSTER_CRITICALCUTTER:
				case BOOSTER_EFFECTGUARD:
					booster->FrameRender(GetMemDC(), 68, 214,
						tempItem.itemKind - 9, 0);
					break;
				}
			}

			SelectObject(GetMemDC(), oldFont);
			DeleteObject(hFont);
		}

		SetTextColor(GetMemDC(), RGB(0, 0, 0));

		if (GAME->GetShowInven()) {
			inventory->AlphaRender(GetMemDC(),
				WINSIZEX - inventory->GetWidth() - 50, 100, 225);

			sprintf_s(str, "인벤토리");
			TextOut(GetMemDC(), 670, 110, str, strlen(str));

			sprintf_s(str, "Gold : %d원", GAME->GetInventory().GetGold());
			TextOut(GetMemDC(), 820, 110, str, strlen(str));

			for (int i = 0; i < ITEMCOUNT; i++) {
				if (GAME->GetInvenInfo(i).item.itemKind == ITEM_EMPTY) continue;
				switch (GAME->GetInvenInfo(i).item.itemKind)
				{
				case ITEM_MONSTERBALL:
					ball->FrameRender(GetMemDC(),
						GAME->GetInvenInfo(i).x, GAME->GetInvenInfo(i).y);
					break;
				case ITEM_POTION:
					potion->FrameRender(GetMemDC(),
						GAME->GetInvenInfo(i).x, GAME->GetInvenInfo(i).y);
					break;
				case ITEM_ANTIDOTE:
				case ITEM_PARLYZEHEAL:
				case ITEM_BURNHEAL:
				case ITEM_ICEHEAL:
				case ITEM_AWAKENING:
				case ITEM_FULLHEAL:
					potion2->FrameRender(GetMemDC(),
						GAME->GetInvenInfo(i).x, GAME->GetInvenInfo(i).y,
						GAME->GetInvenInfo(i).item.itemKind - 3, 0);
					break;
				case BOOSTER_PLUSPOWER:
				case BOOSTER_DEFENDUP:
				case BOOSTER_SPECIALUP:
				case BOOSTER_SPEEDUP:
				case BOOSTER_SPECIALGUARD:
				case BOOSTER_CRITICALCUTTER:
				case BOOSTER_EFFECTGUARD:
					booster->FrameRender(GetMemDC(),
						GAME->GetInvenInfo(i).x, GAME->GetInvenInfo(i).y,
						GAME->GetInvenInfo(i).item.itemKind - 9, 0);
					break;
				}
				TextOut(GetMemDC(),
					GAME->GetInvenInfo(i).x + 50, GAME->GetInvenInfo(i).y + 10,
					GAME->GetInvenInfo(i).item.name.c_str(),
					strlen(GAME->GetInvenInfo(i).item.name.c_str()));
				sprintf_s(str, "%d원", GAME->GetInvenInfo(i).item.price);
				TextOut(GetMemDC(),
					GAME->GetInvenInfo(i).x + 200, GAME->GetInvenInfo(i).y + 10,
					str, strlen(str));
				if (GAME->GetInvenInfo(i).item.count != 0)
					sprintf_s(str, "%d개", GAME->GetInvenInfo(i).item.count);
				TextOut(GetMemDC(),
					GAME->GetInvenInfo(i).x + 275, GAME->GetInvenInfo(i).y + 10,
					str, strlen(str));
			}
		}

		if (isDrag) {
			switch (GAME->GetCurrentItem().itemKind)
			{
			case ITEM_MONSTERBALL:
				ball->FrameRender(GetMemDC(), g_ptMouse.x - 25, g_ptMouse.y - 25);
				break;
			case ITEM_POTION:
				potion->FrameRender(GetMemDC(), g_ptMouse.x - 25, g_ptMouse.y - 25);
				break;
			case ITEM_ANTIDOTE:
			case ITEM_PARLYZEHEAL:
			case ITEM_BURNHEAL:
			case ITEM_ICEHEAL:
			case ITEM_AWAKENING:
			case ITEM_FULLHEAL:
				potion2->FrameRender(GetMemDC(), g_ptMouse.x - 25, g_ptMouse.y - 25,
					GAME->GetCurrentItem().itemKind - 3, 0);
				break;
			case BOOSTER_PLUSPOWER:
			case BOOSTER_DEFENDUP:
			case BOOSTER_SPECIALUP:
			case BOOSTER_SPECIALGUARD:
			case BOOSTER_SPEEDUP:
			case BOOSTER_CRITICALCUTTER:
			case BOOSTER_EFFECTGUARD:
				booster->FrameRender(GetMemDC(), g_ptMouse.x - 25, g_ptMouse.y - 25,
					GAME->GetCurrentItem().itemKind - 9, 0);
				break;
			}
		}
	}
	//==================   Debug   ====================
	if (isDebug)
	{
		sprintf_s(str, "bg x,y %f %f", bgX, bgY);
		TextOut(GetMemDC(), 10, 10, str, strlen(str));
		sprintf_s(str, "player x,y %f %f", playerInfo.GetX(), playerInfo.GetY());
		TextOut(GetMemDC(), 10, 30, str, strlen(str));
		sprintf_s(str, "mouse : %d %d", g_ptMouse.x, g_ptMouse.y);
		TextOut(GetMemDC(), 10, 50, str, strlen(str));

		RectangleMake(GetMemDC(), sceneInfo[SCENE2_EXIT].rc);
		RectangleMake(GetMemDC(), sceneInfo[SCENE2_SHOP].rc);
		RectangleMake(GetMemDC(), playerInfo.GetRect());

		RectangleMake(GetMemDC(), GAME->GetInvenRc());
		RectangleMake(GetMemDC(), GAME->GetStatusBox());
	}
	//=================================================

	
}

void Town2Scene::PlayerMove()
{
	bool isFrameMove = false;

	// left
	if (INPUT->GetKeyDown(VK_LEFT)) {
		playerInfo.SetMoveFrame(0);
		playerInfo.SetDirection(DIRECTION_LEFT);
	}
	if (INPUT->GetKey(VK_LEFT)) {
		if (playerInfo.GetDirection() != DIRECTION_LEFT)
			playerInfo.SetDirection(DIRECTION_LEFT);
		
		isFrameMove = true;
		//playerInfo.AddMoveFrame(0.1f);

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
		
		isFrameMove = true;
		//playerInfo.AddMoveFrame(0.1f);

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

		isFrameMove = true;
		//playerInfo.AddMoveFrame(0.1f);
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

		isFrameMove = true;
		//playerInfo.AddMoveFrame(0.1f);
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

	if (isFrameMove)
		playerInfo.AddMoveFrame(0.1f);
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

void Town2Scene::UpdateItem()
{
	for (int i = 0; i < ITEMCOUNT; i++) {
		if (i < GAME->GetInventory().GetItemCount()) {
			GAME->GetInvenInfo(i).item = GAME->GetInventory().GetItem(i);
		}
		else {
			GAME->GetInvenInfo(i).item.itemKind = ITEM_EMPTY;
		}
	}
}
