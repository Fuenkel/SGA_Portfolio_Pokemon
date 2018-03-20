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
	isDebug = false;
	showShop = false;
	isBuy = false;
	isDrag = false;

	bg = IMAGE->FindImage("Shop");
	bgPixel = IMAGE->FindImage("ShopPixel");
	player = IMAGE->FindImage("Player");

	ball = IMAGE->FindImage("Item_ball");
	potion = IMAGE->FindImage("Item_potion");
	potion2 = IMAGE->FindImage("Item_potion2");
	booster = IMAGE->FindImage("Item_battleBooster");

	inventory = IMAGE->FindImage("Inventory");
	menu = IMAGE->FindImage("Menu");
	status = IMAGE->FindImage("Status");

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

	shop.ItemSetup();
	//playerInfo.InputPlayer();

	for (int i = 0; i < ITEMCOUNT; i++) {
		shopInfo[i].x = 90;
		shopInfo[i].y = 155 + 40 * i;
		shopInfo[i].shopBox = RectMake(
			shopInfo[i].x, shopInfo[i].y, 325, 40);
		shopInfo[i].item.itemKind = ITEM_EMPTY;
	}

	UpdateItem();

	shopRc = RectMake(50, 100, 400, 500);
	shopperBox = RectMake(480, 265, 50, 50);

	return S_OK;
}

void ShopScene::Release()
{
}

void ShopScene::Update()
{
	if (showShop == false && GAME->GetShowInven() == false) {
		PlayerMove();
		playerInfo.Probe(bgPixel, bgX, bgY, bgX, bgY);
	}

	if (INPUT->GetKeyDown('I') && showShop == false) {
		GAME->SetShowInven(!GAME->GetShowInven());
	}

	if (INPUT->GetKeyDown('C') && showShop == false) {
		GAME->SetShowStatus(!GAME->GetShowStatus());
	}

	if (INPUT->GetKeyDown(VK_SPACE) &&
		IntersectRect(&temp, &shopperBox,
			&RectMake(playerInfo.GetX(), playerInfo.GetY(), 
				playerInfo.GetWidth(), playerInfo.GetHeight()))) {
		playerInfo.SetX(480);
		playerInfo.SetY(255);
		playerInfo.SetMoveFrame(PLAYER_IDLE);
		playerInfo.SetDirection(DIRECTION_LEFT);
		GAME->SetShowStatus(false);
		GAME->SetShowInven(true);
		showShop = true;
	}

	if (INPUT->GetKeyDown(VK_LBUTTON)) {
		if (GAME->GetShowStatus() && GAME->GetShowInven()) {
			if (PtInRect(&GAME->GetStatusBox(), g_ptMouse)) {
				isDrag = true;
				GAME->GetCurrentItem() = GAME->GetInventory().GetEquipItem();
			}

			for (int i = 0; i < ITEMCOUNT; i++) {
				if (PtInRect(&GAME->GetInvenInfo(i).invenBox, g_ptMouse)) {
					if (GAME->GetInvenInfo(i).item.itemKind >= BOOSTER_CRITICALCUTTER) {
						isDrag = true;
						GAME->GetCurrentItem() = GAME->GetInvenInfo(i).item;
					}
				}
			}
		}

		if (showShop) {
			for (int i = 0; i < ITEMCOUNT; i++) {
				if (i == ITEMCOUNT - 1 &&
					PtInRect(&shopInfo[i].shopBox, g_ptMouse)) {
					GAME->SetShowInven(false);
					showShop = false;
				}
				else if (PtInRect(&shopInfo[i].shopBox, g_ptMouse)) {
					if (shopInfo[i].item.itemKind == ITEM_EMPTY) continue;
					if (shopInfo[i].item.count > 0 &&
						shopInfo[i].item.price <= GAME->GetInventory().GetGold())
						GAME->GetInventory().AddItem(
							shop.BuyItem(i, GAME->GetInventory().GetGold()));
					UpdateItem();
				}
			}
		}
	}

	if (INPUT->GetKeyUp(VK_LBUTTON) && GAME->GetShowStatus()
		&& GAME->GetShowInven()) {
		if (PtInRect(&GAME->GetInvenRc(), g_ptMouse) &&
			GAME->GetCurrentItem().name.compare(
				GAME->GetInventory().GetEquipItem().name) == 0) {
			GAME->GetInventory().EquipItem(-1);
			UpdateItem();
		}

		if (PtInRect(&GAME->GetStatusBox(), g_ptMouse)) {
			for (int i = 0; i < ITEMCOUNT; i++) {
				if (GAME->GetInvenInfo(i).item.name.compare(
					GAME->GetCurrentItem().name) == 0) {
					GAME->GetInventory().EquipItem(i);
					UpdateItem();
					break;
				}
			}
		}

		isDrag = false;
	}

	// 마우스 버튼 클릭으로 판매 구매
	//if (INPUT->GetKeyDown(VK_LBUTTON) 
	//	&& GAME->GetShowInven() && showShop == true) {
	//	for (int i = 0; i < ITEMCOUNT; i++) {
	//		if (i == ITEMCOUNT - 1 &&
	//			PtInRect(&shopInfo[i].shopBox, g_ptMouse)) {
	//			GAME->SetShowInven(false);
	//			showShop = false;
	//		}
	//		else if (PtInRect(&shopInfo[i].shopBox, g_ptMouse)) {
	//			if (shopInfo[i].item.itemKind == ITEM_EMPTY) continue;
	//			if(shopInfo[i].item.count > 0 && 
	//				shopInfo[i].item.price <= GAME->GetInventory().GetGold())
	//				GAME->GetInventory().AddItem(shop.BuyItem(i, GAME->GetInventory().GetGold()));
	//			UpdateItem();
	//		}
	//	}
	//}

	if (INPUT->GetKeyDown(VK_RBUTTON) 
		&& GAME->GetShowInven() == true && showShop == true) {
		for (int i = 0; i < ITEMCOUNT; i++) {
			if (PtInRect(&GAME->GetInvenInfo(i).invenBox, g_ptMouse)) {
				if (GAME->GetInvenInfo(i).item.itemKind == ITEM_EMPTY) continue;
				shop.AddItem(GAME->GetInventory().SellItem(i, 
					GAME->GetInventory().GetGold()));
				UpdateItem();
			}
		}
	}

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

		if (isDebug) {
			bgPixel->Render(GetMemDC(), 0, 0,
				bgX, bgY, WINSIZEX, WINSIZEY);
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

			sprintf_s(str, "%d", GAME->GetPokemon(0).GetLevel());
			TextOut(GetMemDC(), 85, 162, str, strlen(str));

			sprintf_s(str, "%s", GAME->GetPokemon(0).GetName().c_str());
			TextOut(GetMemDC(), 140, 162, str, strlen(str));

			SetTextColor(GetMemDC(), RGB(0, 0, 0));
			sprintf_s(str, "%d / %d",
				GAME->GetPokemon(0).GetHp(), GAME->GetPokemon(0).GetMaxHp());
			TextOut(GetMemDC(), 430, 165, str, strlen(str));

			sprintf_s(str, "%d", GAME->GetPokemon(0).GetAtk());
			TextOut(GetMemDC(), 495, 225, str, strlen(str));

			sprintf_s(str, "%d", GAME->GetPokemon(0).GetDef());
			TextOut(GetMemDC(), 495, 265, str, strlen(str));

			sprintf_s(str, "%d", GAME->GetPokemon(0).GetSpAtk());
			TextOut(GetMemDC(), 495, 305, str, strlen(str));

			sprintf_s(str, "%d", GAME->GetPokemon(0).GetSpDef());
			TextOut(GetMemDC(), 495, 345, str, strlen(str));

			sprintf_s(str, "%d", GAME->GetPokemon(0).GetSpeed());
			TextOut(GetMemDC(), 495, 385, str, strlen(str));

			sprintf_s(str, "%8d", GAME->GetPokemon(0).GetExp());
			TextOut(GetMemDC(), 430, 425, str, strlen(str));

			sprintf_s(str, "%8d", GAME->GetPokemon(0).GetMaxExp());
			TextOut(GetMemDC(), 430, 465, str, strlen(str));

			tagItemInfo tempItem = GAME->GetInventory().GetEquipItem();

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

		if (showShop) {
			menu->AlphaRender(GetMemDC(), 50, 100, 225);
			sprintf_s(str, "상점");
			TextOut(GetMemDC(), 120, 110, str, strlen(str));
			sprintf_s(str, "구매/판매 마우스 L/R버튼");
			TextOut(GetMemDC(), 200, 110, str, strlen(str));
			for (int i = 0; i < ITEMCOUNT; i++) {
				if (shopInfo[i].item.itemKind == ITEM_EMPTY) continue;
				switch (shopInfo[i].item.itemKind)
				{
				case ITEM_MONSTERBALL:
					ball->FrameRender(GetMemDC(), shopInfo[i].x, shopInfo[i].y);
					break;
				case ITEM_POTION:
					potion->FrameRender(GetMemDC(), shopInfo[i].x, shopInfo[i].y);
					break;
				case ITEM_ANTIDOTE:
				case ITEM_PARLYZEHEAL:
				case ITEM_BURNHEAL:
				case ITEM_ICEHEAL:
				case ITEM_AWAKENING:
				case ITEM_FULLHEAL:
					potion2->FrameRender(GetMemDC(), shopInfo[i].x, shopInfo[i].y,
						shopInfo[i].item.itemKind - 3, 0);
					break;
				case BOOSTER_PLUSPOWER:
				case BOOSTER_DEFENDUP:
				case BOOSTER_SPECIALUP:
				case BOOSTER_SPEEDUP:
				case BOOSTER_SPECIALGUARD:
				case BOOSTER_CRITICALCUTTER:
				case BOOSTER_EFFECTGUARD:
					booster->FrameRender(GetMemDC(), shopInfo[i].x, shopInfo[i].y,
						shopInfo[i].item.itemKind - 9, 0);
					break;
				}
				TextOut(GetMemDC(), shopInfo[i].x + 50, shopInfo[i].y + 10,
					shopInfo[i].item.name.c_str(), strlen(shopInfo[i].item.name.c_str()));
				sprintf_s(str, "%d원", shopInfo[i].item.price);
				TextOut(GetMemDC(), shopInfo[i].x + 200, shopInfo[i].y + 10,
					str, strlen(str));
				if (shopInfo[i].item.count != 0)
					sprintf_s(str, "%d개", shopInfo[i].item.count);
				else
					sprintf_s(str, "매진");
				TextOut(GetMemDC(), shopInfo[i].x + 275, shopInfo[i].y + 10,
					str, strlen(str));
			}
		}

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

		RectangleMake(GetMemDC(), sceneInfo[SCENE3_EXIT].rc);
		RectangleMake(GetMemDC(), playerInfo.GetRect());

		for (int i = 0; i < ITEMCOUNT; i++) {
			RectangleMake(GetMemDC(), shopInfo[i].shopBox);
			RectangleMake(GetMemDC(), GAME->GetInvenInfo(i).invenBox);
		}
		RectangleMake(GetMemDC(), shopperBox);

		RectangleMake(GetMemDC(), shopRc);
		RectangleMake(GetMemDC(), GAME->GetInvenRc());
		RectangleMake(GetMemDC(), GAME->GetStatusBox());
	}
	//=================================================
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

void ShopScene::UpdateItem()
{
	for (int i = 0; i < shop.GetItemCount(); i++) {
		shopInfo[i].item = shop.GetItem(i);
	}

	for (int i = 0; i < ITEMCOUNT; i++) {
		if (i < GAME->GetInventory().GetItemCount()) {
			GAME->GetInvenInfo(i).item = GAME->GetInventory().GetItem(i);
		}
		else {
			GAME->GetInvenInfo(i).item.itemKind = ITEM_EMPTY;
		}
	}
}
