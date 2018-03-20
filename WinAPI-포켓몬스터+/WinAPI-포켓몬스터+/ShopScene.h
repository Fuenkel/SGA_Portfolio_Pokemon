#pragma once

#include "GameNode.h"

#include "Player.h"
#include "Shop.h"
#include "Item.h"

#define PLAYER_SPEED 5.0f
#define ITEMCOUNT 10

enum ChangeSceneStatus3 {
	SCENE3_EXIT,
	SCENE3_END
};

struct tagChangeSceneInfo3 {
	RECT rc;
	float x, y;
	float width, height;
};

struct tagShopInfo {
	RECT shopBox;
	tagItemInfo item;
	float x, y;
};

class ShopScene : public GameNode
{
private:
	bool isDebug;

	Image* bg;
	Image* bgPixel;
	Image* player;

	Image * ball;
	Image * potion;
	Image * potion2;
	Image * booster;

	Image * inventory;
	Image * menu;
	Image * status;

	Player playerInfo;

	float bgX, bgY;

	char str[128];
	RECT temp;
	HFONT hFont;
	HFONT oldFont;

	Shop shop;
	tagShopInfo shopInfo[ITEMCOUNT];
	
	RECT shopRc;
	RECT shopperBox;

	bool isBuy;
	bool isDrag;
	bool showShop;

	tagChangeSceneInfo3 sceneInfo[SCENE3_END];
public:
	ShopScene();
	~ShopScene();

	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;

	void PlayerMove();
	void OtherMove(Direction dir);

	void UpdateItem();
};

