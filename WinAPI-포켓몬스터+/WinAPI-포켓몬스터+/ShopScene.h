#pragma once

#include "GameNode.h"

#include "Player.h"

#define PLAYER_SPEED 5.0f

enum ChangeSceneStatus3 {
	SCENE3_EXIT,
	SCENE3_END
};

struct tagChangeSceneInfo3 {
	RECT rc;
	float x, y;
	float width, height;
};

class ShopScene : public GameNode
{
private:
	bool isDebug;

	Image* bg;
	Image* bgPixel;
	Image* player;

	Player playerInfo;

	float bgX, bgY;

	char str[128];
	RECT temp;

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
};

