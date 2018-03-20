#pragma once

#include "GameNode.h"

#include "Player.h"

#define PLAYER_SPEED 5.0f

enum ChangeSceneStatus {
	SCENE_EXIT,
	SCENE_END
};

struct tagChangeSceneInfo {
	RECT rc;
	float x, y;
	float width, height;
};

class Town1Scene : public GameNode
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
	Image * status;

	Player playerInfo;

	float bgX, bgY;

	char str[128];
	RECT temp;
	HFONT hFont;
	HFONT oldFont;

	tagChangeSceneInfo sceneInfo[SCENE_END];

	bool isDrag;
public:
	Town1Scene();
	~Town1Scene();

	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;

	void PlayerMove();
	void OtherMove(Direction dir);

	void UpdateItem();
};

