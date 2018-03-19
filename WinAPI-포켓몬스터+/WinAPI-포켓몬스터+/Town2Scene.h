#pragma once

#include "GameNode.h"

#include "Player.h"

#define PLAYER_SPEED 2.5f

class Town2Scene : public GameNode
{
private:
	bool isDebug;

	Image* bg;
	Image* bgPixel;
	Image* player;

	Player playerInfo;

	float bgX, bgY;
	char str[128];
public:
	Town2Scene();
	~Town2Scene();

	virtual HRESULT Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void Render() override;

	void PlayerMove();
	void OtherMove(Direction dir);
};

