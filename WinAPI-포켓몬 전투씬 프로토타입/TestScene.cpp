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

	//moveFrame = 0;
	
	pikachu[STATUS_IDLE] = IMAGE->FindImage("Pikachu_idle");
	pikachu[STATUS_MOVE] = IMAGE->FindImage("Pikachu_movement");
	pikachu[STATUS_ATTACK] = IMAGE->FindImage("Pikachu_attack");
	pikachu[STATUS_SPECIAL_ATTACK] = IMAGE->FindImage("Pikachu_special_attack");
	pikachu[STATUS_HURT] = IMAGE->FindImage("Pikachu_hurt");

	charmander[STATUS_IDLE] = IMAGE->FindImage("Charmander_idle");
	charmander[STATUS_MOVE] = IMAGE->FindImage("Charmander_movement");
	charmander[STATUS_ATTACK] = IMAGE->FindImage("Charmander_attack1");
	charmander[STATUS_ATTACK2] = IMAGE->FindImage("Charmander_attack2");
	charmander[STATUS_SPECIAL_ATTACK] = IMAGE->FindImage("Charmander_special_attack");
	charmander[STATUS_HURT] = IMAGE->FindImage("Charmander_hurt");

	effect[0] = IMAGE->FindImage("Effect_electricity");
	effect[1] = IMAGE->FindImage("Effect_fire");

	pokemon.SetX(WINSIZEX / 2);
	pokemon.SetY(WINSIZEY / 2);
	pokemon.SetWidth(50);
	pokemon.SetHeight(50);
	pokemon.SetDirection(DIRECTION_DOWN);
	pokemon.SetStatus(STATUS_IDLE);
	pokemon.SetAttackStatus(STATUS_ATTACK);

	enemy.SetX(WINSIZEX / 2);
	enemy.SetY(WINSIZEY / 2 - 100);
	enemy.SetWidth(50);
	enemy.SetHeight(50);
	enemy.SetDirection(DIRECTION_DOWN);
	enemy.SetStatus(STATUS_IDLE);
	enemy.SetAttackStatus(STATUS_ATTACK);

	return S_OK;
}

void TestScene::Release()
{
}

void TestScene::Update()
{
	//if (INPUT->GetKeyDown(VK_SPACE)) {
	//	moveFrame++;
	//	if (moveFrame == IMAGE->FindImage("Pikachu_attack")->GetMaxFrameX())
	//		moveFrame = 0;
	//}

	// enemy
	switch (enemy.GetStatus())
	{
	case STATUS_IDLE:
		break;
	case STATUS_MOVE:
		break;
	case STATUS_ATTACK:
		break;
	case STATUS_SPECIAL_ATTACK:
		break;
	case STATUS_HURT:
		enemy.SetMoveFrame(enemy.GetMoveFrame() + 0.1f);
		switch (enemy.GetDirection())
			{
			case DIRECTION_DOWN:
				if (enemy.GetMoveFrame() >= 1) {
					enemy.SetStatus(STATUS_IDLE);
					enemy.SetMoveFrame(0);
				}
				break;
			case DIRECTION_UP:
				if (enemy.GetMoveFrame() >= 2) {
					enemy.SetStatus(STATUS_IDLE);
					enemy.SetMoveFrame(1);
				}
				break;
			case DIRECTION_LEFT:
				if (enemy.GetMoveFrame() >= 3) {
					enemy.SetStatus(STATUS_IDLE);
					enemy.SetMoveFrame(2);
				}
				break;
			case DIRECTION_RIGHT:
				if (enemy.GetMoveFrame() >= 4) {
					enemy.SetStatus(STATUS_IDLE);
					enemy.SetMoveFrame(3);
				}
				break;
			}
		break;
	case STATUS_ATTACK2:
		break;
	}

	// pokemon
	switch (pokemon.GetStatus())
	{
	case STATUS_IDLE:
		Idle();
		Attack();
		break;
	case STATUS_MOVE:
		Move();
		Attack(); 
		break;
	case STATUS_ATTACK:
		//moveFrame += 0.1f;
		RECT temp2 = pokemon.GetMeleeAttack().rc;
		if (IntersectRect(&temp, &enemy.GetRect(), &temp2)) {
			enemy.SetStatus(STATUS_HURT);
			// 포켓몬 마주보게 하기
			switch (pokemon.GetDirection())
			{
			case DIRECTION_DOWN:
				enemy.SetDirection(DIRECTION_UP);
				break;
			case DIRECTION_UP:
				enemy.SetDirection(DIRECTION_DOWN);
				break;
			case DIRECTION_LEFT:
				enemy.SetDirection(DIRECTION_RIGHT);
				break;
			case DIRECTION_RIGHT:
				enemy.SetDirection(DIRECTION_LEFT);
				break;
			}
			switch (enemy.GetDirection())
			{
			case DIRECTION_DOWN:
				enemy.SetMoveFrame(0);
				break;
			case DIRECTION_UP:
				enemy.SetMoveFrame(1);
				break;
			case DIRECTION_LEFT:
				enemy.SetMoveFrame(2);
				break;
			case DIRECTION_RIGHT:
				enemy.SetMoveFrame(3);
				break;
			}
		}
		pokemon.SetMoveFrame(pokemon.GetMoveFrame() + 0.1f);
		switch (pokemon.GetDirection())
		{
		case DIRECTION_DOWN:
			//if (moveFrame >= 1) {
			if(pokemon.GetMoveFrame() >= 1) {
				pokemon.SetStatus(STATUS_IDLE);
				//moveFrame = 0;
				pokemon.SetMoveFrame(0);
				pokemon.MeleeAttack(false);
			}
			break;
		case DIRECTION_UP:
			//if (moveFrame >= 2) {
			if (pokemon.GetMoveFrame() >= 2) {
				pokemon.SetStatus(STATUS_IDLE);
				//moveFrame = 1;
				pokemon.SetMoveFrame(1);
				pokemon.MeleeAttack(false);
			}
			break;
		case DIRECTION_LEFT:
			//if (moveFrame >= 3) {
			if (pokemon.GetMoveFrame() >= 3) {
				pokemon.SetStatus(STATUS_IDLE);
				//moveFrame = 2;
				pokemon.SetMoveFrame(2);
				pokemon.MeleeAttack(false);
			}
			break;
		case DIRECTION_RIGHT:
			//if (moveFrame >= 4) {
			if(pokemon.GetMoveFrame() >= 4) {
				pokemon.SetStatus(STATUS_IDLE);
				//moveFrame = 3;
				pokemon.SetMoveFrame(3);
				pokemon.MeleeAttack(false);
			}
			break;
		}
		break;
	case STATUS_SPECIAL_ATTACK:
		//moveFrame += 0.1f;
		pokemon.SetMoveFrame(pokemon.GetMoveFrame() + 0.1f);
		switch (pokemon.GetDirection())
		{
		case DIRECTION_DOWN:
			//if (moveFrame >= 2) {
			if (pokemon.GetMoveFrame() >= 2) {
				pokemon.SetStatus(STATUS_IDLE);
				//moveFrame = 0;
				pokemon.SetMoveFrame(0);
			}
			break;
		case DIRECTION_UP:
			//if (moveFrame >= 4) {
			if (pokemon.GetMoveFrame() >= 4) {
				pokemon.SetStatus(STATUS_IDLE);
				//moveFrame = 1;
				pokemon.SetMoveFrame(1);
			}
			break;
		case DIRECTION_LEFT:
			//if (moveFrame >= 6) {
			if (pokemon.GetMoveFrame() >= 6) {
				pokemon.SetStatus(STATUS_IDLE);
				//moveFrame = 2;
				pokemon.SetMoveFrame(2);
			}
			break;
		case DIRECTION_RIGHT:
			//if (moveFrame >= 8) {
			if (pokemon.GetMoveFrame() >= 8) {
				pokemon.SetStatus(STATUS_IDLE);
				//moveFrame = 3;
				pokemon.SetMoveFrame(3);
			}
			break;
		}
		break;
	case STATUS_HURT:
		break;
	}

	pokemon.BulletMove();

	for (int i = 0; i < BULLETMAX; i++) {
		if (pokemon.GetBullet(i)->isFire == false) continue;

		RECT bulletTemp = pokemon.GetBullet(i)->rc;
		RECT temp2 = enemy.GetRect();
		if (IntersectRect(&temp, &temp2, &bulletTemp)) {
			pokemon.GetBullet(i)->isFire = false;
			enemy.SetStatus(STATUS_HURT);
			switch (pokemon.GetBullet(i)->dir)
			{
			case DIRECTION_DOWN:
				enemy.SetDirection(DIRECTION_UP);
				break;
			case DIRECTION_UP:
				enemy.SetDirection(DIRECTION_DOWN);
				break;
			case DIRECTION_LEFT:
				enemy.SetDirection(DIRECTION_RIGHT);
				break;
			case DIRECTION_RIGHT:
				enemy.SetDirection(DIRECTION_LEFT);
				break;
			}

			switch (enemy.GetDirection())
			{
			case DIRECTION_DOWN:
				enemy.SetMoveFrame(0);
				break;
			case DIRECTION_UP:
				enemy.SetMoveFrame(1);
				break;
			case DIRECTION_LEFT:
				enemy.SetMoveFrame(2);
				break;
			case DIRECTION_RIGHT:
				enemy.SetMoveFrame(3);
				break;
			}
		}
	}

	if (INPUT->GetKeyDown('X')) {
		if (pokemon.GetAttackStatus() == STATUS_ATTACK) {
			pokemon.SetAttackStatus(STATUS_SPECIAL_ATTACK);
		}
		else if (pokemon.GetAttackStatus() == STATUS_SPECIAL_ATTACK) {
			pokemon.SetAttackStatus(STATUS_ATTACK);
		}
	}

	if (INPUT->GetKeyDown(VK_TAB)) {
		isDebug = !isDebug;
	}
}

void TestScene::Render()
{
	IMAGE->FrameRender("BackGround", GetMemDC(), 0, 0, 0, 0);

	//IMAGE->FrameRender(  "Pikachu_attack", GetMemDC(),
	//	IMAGE->FindImage("Pikachu_attack")->GetX(),
	//	IMAGE->FindImage("Pikachu_attack")->GetY(),
	//	moveFrame, 0);

	//pikachu[pokemon.GetStatus()]->FrameRender(GetMemDC(), 
	//	pokemon.GetX(), pokemon.GetY(), (int)moveFrame, 0);
	pikachu[pokemon.GetStatus()]->FrameRender(GetMemDC(), 
		pokemon.GetX(), pokemon.GetY(), (int)pokemon.GetMoveFrame(), 0);

	charmander[enemy.GetStatus()]->FrameRender(GetMemDC(),
		enemy.GetX(), enemy.GetY(), (int)enemy.GetMoveFrame(), 0);

	for (int i = 0; i < BULLETMAX; i++) {
		if (pokemon.GetBullet(i)->isFire == false) continue;
		effect[0]->FrameRender(GetMemDC(),
			pokemon.GetBullet(i)->x - 25, pokemon.GetBullet(i)->y - 25,
			(int)pokemon.GetBullet(i)->moveFrame, 0);
	} 

	if (isDebug) {
		if (pokemon.GetMeleeAttack().isAttack)
			RectangleMake(GetMemDC(), pokemon.GetMeleeAttack().rc);
		
		for (int i = 0; i < BULLETMAX; i++) {
			if (pokemon.GetBullet(i)->isFire == false) continue;
			RectangleMake(GetMemDC(), pokemon.GetBullet(i)->rc);
		}

		//effect->Render(GetMemDC(), -300, WINSIZEY/2);
	}
}

void TestScene::Idle()
{
	switch (pokemon.GetDirection())
	{
	case DIRECTION_DOWN:
		//moveFrame = 0;
		pokemon.SetMoveFrame(0);
		break;
	case DIRECTION_UP:
		//moveFrame = 1;
		pokemon.SetMoveFrame(1);
		break;
	case DIRECTION_LEFT:
		//moveFrame = 2;
		pokemon.SetMoveFrame(2);
		break;
	case DIRECTION_RIGHT:
		//moveFrame = 3;
		pokemon.SetMoveFrame(3);
		break;
	}

	// move
	if (INPUT->GetKey(VK_DOWN)) {
		pokemon.SetDirection(DIRECTION_DOWN);
		pokemon.SetStatus(STATUS_MOVE);
		//moveFrame = 0;
		pokemon.SetMoveFrame(0);
	}
	if (INPUT->GetKey(VK_UP)) {
		pokemon.SetDirection(DIRECTION_UP);
		pokemon.SetStatus(STATUS_MOVE);
		//moveFrame = 3;
		pokemon.SetMoveFrame(3);
	}
	if (INPUT->GetKey(VK_LEFT)) {
		pokemon.SetDirection(DIRECTION_LEFT);
		pokemon.SetStatus(STATUS_MOVE);
		//moveFrame = 6;
		pokemon.SetMoveFrame(6);
	}
	if (INPUT->GetKey(VK_RIGHT)) {
		pokemon.SetDirection(DIRECTION_RIGHT);
		pokemon.SetStatus(STATUS_MOVE);
		//moveFrame = 9;
		pokemon.SetMoveFrame(9);
	}


}

void TestScene::Move()
{

	if (INPUT->GetKey(VK_DOWN)) { pokemon.SetY(pokemon.GetY() + SPEED); }
	if (INPUT->GetKey(VK_UP)) { pokemon.SetY(pokemon.GetY() - SPEED); }
	if (INPUT->GetKey(VK_LEFT)) { pokemon.SetX(pokemon.GetX() - SPEED); }
	if (INPUT->GetKey(VK_RIGHT)) { pokemon.SetX(pokemon.GetX() + SPEED); }

	// 방향키 땠을 때 다시 idle로
	if (INPUT->GetKeyUp(VK_DOWN)) {
		pokemon.SetStatus(STATUS_IDLE);
		pokemon.SetDirection(DIRECTION_DOWN);
		//moveFrame = 0;
		pokemon.SetMoveFrame(0);
	}
	if (INPUT->GetKeyUp(VK_UP)) {
		pokemon.SetStatus(STATUS_IDLE);
		pokemon.SetDirection(DIRECTION_UP);
		//moveFrame = 1;
		pokemon.SetMoveFrame(1);
	}
	if (INPUT->GetKeyUp(VK_LEFT)) {
		pokemon.SetStatus(STATUS_IDLE);
		pokemon.SetDirection(DIRECTION_LEFT);
		//moveFrame = 2;
		pokemon.SetMoveFrame(2);
	}
	if (INPUT->GetKeyUp(VK_RIGHT)) {
		pokemon.SetStatus(STATUS_IDLE);
		pokemon.SetDirection(DIRECTION_RIGHT);
		//moveFrame = 3;
		pokemon.SetMoveFrame(3);
	}

	if (pokemon.GetStatus() == STATUS_MOVE) {
		//moveFrame += 0.1f;
		pokemon.SetMoveFrame(pokemon.GetMoveFrame() + 0.1f);
		switch (pokemon.GetDirection())
		{
		case DIRECTION_DOWN:
			//if (moveFrame > 2)
			if (pokemon.GetMoveFrame() > 2)
				//moveFrame = 0;
				pokemon.SetMoveFrame(0);
			break;
		case DIRECTION_UP:
			//if (moveFrame > 5)
			if (pokemon.GetMoveFrame() > 5)
				//moveFrame = 3;
				pokemon.SetMoveFrame(3);
			break;
		case DIRECTION_LEFT:
			//if (moveFrame > 8)
			if (pokemon.GetMoveFrame() > 8)
				//moveFrame = 6;
				pokemon.SetMoveFrame(6);
			break;
		case DIRECTION_RIGHT:
			//if (moveFrame > 11)
			if (pokemon.GetMoveFrame() > 11)
				//moveFrame = 9;
				pokemon.SetMoveFrame(9);
			break;
		}

	}
}

void TestScene::Attack()
{
	if (INPUT->GetKeyDown(VK_SPACE)) {
		pokemon.SetStatus(pokemon.GetAttackStatus());
		switch (pokemon.GetDirection())
		{
		case DIRECTION_DOWN:
			switch (pokemon.GetStatus()) {
			case STATUS_ATTACK:
				//moveFrame = 0;
				pokemon.SetMoveFrame(0);
				pokemon.MeleeAttack(true);
				break;
			case STATUS_SPECIAL_ATTACK:
				//moveFrame = 0;
				pokemon.SetMoveFrame(0);
				pokemon.BulletFire();
				break;
			}
			break;
		case DIRECTION_UP:
			switch (pokemon.GetStatus()) {
			case STATUS_ATTACK:
				//moveFrame = 1;
				pokemon.SetMoveFrame(1);
				pokemon.MeleeAttack(true);
				break;
			case STATUS_SPECIAL_ATTACK:
				//moveFrame = 2;
				pokemon.SetMoveFrame(2);
				pokemon.BulletFire();
				break;
			}
			break;
		case DIRECTION_LEFT:
			switch (pokemon.GetStatus()) {
			case STATUS_ATTACK:
				//moveFrame = 2;
				pokemon.SetMoveFrame(2);
				pokemon.MeleeAttack(true);
				break;
			case STATUS_SPECIAL_ATTACK:
				//moveFrame = 4;
				pokemon.SetMoveFrame(4);
				pokemon.BulletFire();
				break;
			}
			break;
		case DIRECTION_RIGHT:
			switch (pokemon.GetStatus()) {
			case STATUS_ATTACK:
				//moveFrame = 3;
				pokemon.SetMoveFrame(3);
				pokemon.MeleeAttack(true);
				break;
			case STATUS_SPECIAL_ATTACK:
				//moveFrame = 6;
				pokemon.SetMoveFrame(6);
				pokemon.BulletFire();
				break;
			}
			break;
		}
	}
}
