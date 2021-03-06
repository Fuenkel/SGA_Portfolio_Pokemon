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

	//moveFrame = 0;
	
	bg = IMAGE->FindImage("Battle");

	ui[0] = IMAGE->FindImage("UI_open");
	ui[1] = IMAGE->FindImage("UI_close");

	player.SetAni(0, IMAGE->FindImage("Player_battle"));
	player.SetPortrait(IMAGE->FindImage("Player_portrait"));
	player.Init(DIRECTION_UP, WINSIZEX / 2, WINSIZEY / 2, 40, 50);
	player.SetMoveFrame(PLAYER_IDLE);
	player.SetLevel(GAME->GetPlayerLevel());
	player.SetName("지우");
	player.SetHp(100);
	player.SetMaxHp(100);

	//pikachu[STATUS_IDLE] = IMAGE->FindImage("Pikachu_idle");
	//pikachu[STATUS_MOVE] = IMAGE->FindImage("Pikachu_movement");
	//pikachu[STATUS_ATTACK] = IMAGE->FindImage("Pikachu_attack");
	//pikachu[STATUS_SPECIAL_ATTACK] = IMAGE->FindImage("Pikachu_special_attack");
	//pikachu[STATUS_HURT] = IMAGE->FindImage("Pikachu_hurt");

	pokemon = GAME->GetPokemon(GAME->GetSelectNum());

	//pokemon.InitAni(5);
	//pokemon.SetAni(STATUS_IDLE, IMAGE->FindImage("Pikachu_idle"));
	//pokemon.SetAni(STATUS_MOVE, IMAGE->FindImage("Pikachu_movement"));
	//pokemon.SetAni(STATUS_ATTACK, IMAGE->FindImage("Pikachu_attack"));
	//pokemon.SetAni(STATUS_HURT, IMAGE->FindImage("Pikachu_hurt"));
	//pokemon.SetAni(STATUS_SPECIAL_ATTACK, 
	//	IMAGE->FindImage("Pikachu_special_attack"));

	//charmander[STATUS_IDLE] = IMAGE->FindImage("Charmander_idle");
	//charmander[STATUS_MOVE] = IMAGE->FindImage("Charmander_movement");
	//charmander[STATUS_ATTACK] = IMAGE->FindImage("Charmander_attack1");
	//charmander[STATUS_ATTACK2] = IMAGE->FindImage("Charmander_attack2");
	//charmander[STATUS_SPECIAL_ATTACK] = IMAGE->FindImage("Charmander_special_attack");
	//charmander[STATUS_HURT] = IMAGE->FindImage("Charmander_hurt");

	for (int i = 0; i < POKEMON_COUNT; i++) {
		if (i % 2 == 0) {
			enemy[i].SetPortrait(IMAGE->FindImage("Pidgey_portrait"));
			enemy[i].SetAni(STATUS_IDLE, IMAGE->FindImage("Pidgey_idle"));
			enemy[i].SetAniMaxNum(STATUS_IDLE, 2);
			enemy[i].SetAni(STATUS_MOVE, IMAGE->FindImage("Pidgey_movement"));
			enemy[i].SetAniMaxNum(STATUS_MOVE, 3);
			enemy[i].SetAni(STATUS_ATTACK, IMAGE->FindImage("Pidgey_attack"));
			enemy[i].SetAniMaxNum(STATUS_ATTACK, 3);
			enemy[i].SetAni(STATUS_HURT, IMAGE->FindImage("Pidgey_hurt"));
			enemy[i].SetAniMaxNum(STATUS_HURT, 1);
			enemy[i].SetAni(STATUS_SPECIAL_ATTACK,
				IMAGE->FindImage("Pidgey_special_attack"));
			enemy[i].SetAniMaxNum(STATUS_SPECIAL_ATTACK, 2);

			// test
			sprintf_s(str, "구구_%d", i + 1);

			enemy[i].SetName(str);
			enemy[i].SetLevel(5);
			enemy[i].SetMaxHp(28);
			enemy[i].SetHp(28);
			enemy[i].SetAtk(4);
		}
		else {
			enemy[i].SetPortrait(IMAGE->FindImage("Rattata_portrait"));
			enemy[i].SetAni(STATUS_IDLE, IMAGE->FindImage("Rattata_idle"));
			enemy[i].SetAniMaxNum(STATUS_IDLE, 2);
			enemy[i].SetAni(STATUS_MOVE, IMAGE->FindImage("Rattata_movement"));
			enemy[i].SetAniMaxNum(STATUS_MOVE, 3);
			enemy[i].SetAni(STATUS_ATTACK, IMAGE->FindImage("Rattata_attack"));
			enemy[i].SetAniMaxNum(STATUS_ATTACK, 4);
			enemy[i].SetAni(STATUS_HURT, IMAGE->FindImage("Rattata_hurt"));
			enemy[i].SetAniMaxNum(STATUS_HURT, 1);
			enemy[i].SetAni(STATUS_SPECIAL_ATTACK,
				IMAGE->FindImage("Rattata_special_attack"));
			enemy[i].SetAniMaxNum(STATUS_SPECIAL_ATTACK, 4);

			// test
			sprintf_s(str, "꼬렛_%d", i + 1);

			enemy[i].SetName(str);
			enemy[i].SetLevel(5);
			enemy[i].SetMaxHp(32);
			enemy[i].SetHp(32);
			enemy[i].SetAtk(5);

		}
	}

	effect[EFFECT_ELECTRICITY] = IMAGE->FindImage("Effect_electricity");
	effect[EFFECT_FIRE] = IMAGE->FindImage("Effect_fire");
	effect[EFFECT_WATER] = IMAGE->FindImage("Effect_water");
	effect[EFFECT_GRASS] = IMAGE->FindImage("Effect_grass");

	pokemon.SetWidth(50);
	pokemon.SetHeight(50);
	pokemon.SetX(WINSIZEX / 2);
	pokemon.SetY(WINSIZEY / 2 - player.GetHeight());
	pokemon.SetDirection(DIRECTION_UP);
	pokemon.SetStatus(STATUS_IDLE);
	pokemon.SetAttackStatus(STATUS_ATTACK);

	currentEnemy = 0;

	for (int i = 0; i < POKEMON_COUNT; i++) {
		enemy[i].SetX(WINSIZEX / 2);
		enemy[i].SetY(-100 * i);
		enemy[i].SetWidth(50);
		enemy[i].SetHeight(50);
		enemy[i].SetDirection(DIRECTION_DOWN);
		enemy[i].SetStatus(STATUS_IDLE);
		enemy[i].SetAttackStatus(STATUS_ATTACK);

		enemyHpBar[i] = RectMake(enemy[i].GetX(), enemy[i].GetY() - 4,
			enemy[i].GetWidth(), 4);
		enemyHpWidth[i] = enemyHpBar[i].right - enemyHpBar[i].left;
		enemyHpStatus[i] = 0;
	}

	// ui hpBar
	// test
	// pokemon
	hpBar[0] = RectMake(71, 147, 185 - 71, 152 - 148);
	hpBar[1] = RectMake(71 + 200, 147, 185 - 71, 152 - 148);
	hpBar[2] = RectMake(WINSIZEX - 400 + 71, 147, 185 - 71, 152 - 148);
	hpBar[3] = RectMake(WINSIZEX - 200 + 71, 147, 185 - 71, 152 - 148);
	// player
	hpBar[4] = RectMake(71, 740, 185 - 71, 152 - 148);
	// enemy
	hpBar[5] = RectMake(WINSIZEX - 200 + 71, 740, 185 - 71, 152 - 148);

	for (int i = 0; i < 6; i++) {
		hpWidth[i] = hpBar[i].right - hpBar[i].left;
		hpStatus[i] = 0;
	}

	fullHp = RGB(112, 248, 168);
	halfHp = RGB(248, 224, 56);
	littleHp = RGB(208, 40, 40);

	//width = hpBar[0].right - hpBar[0].left;
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

	// hpBar test
	//if (INPUT->GetKeyDown('Q'))
	//	GAME->GetPokemon(0).AddHp(-1);
	//if (INPUT->GetKeyDown('W'))
	//	GAME->GetPokemon(1).AddHp(-1);
	//if (INPUT->GetKeyDown('E'))
	//	GAME->GetPokemon(2).AddHp(-1);
	//if (INPUT->GetKeyDown('R'))
	//	GAME->GetPokemon(3).AddHp(-1);
	//if (INPUT->GetKeyDown('T'))
	//	player.AddHp(-1);
	
	// test위해 모두 정지
	//return;

	if (INPUT->GetKeyDown('X')) {
		if (pokemon.GetAttackStatus() == STATUS_ATTACK) {
			pokemon.SetAttackStatus(STATUS_SPECIAL_ATTACK);
		}
		else if (pokemon.GetAttackStatus() == STATUS_SPECIAL_ATTACK) {
			pokemon.SetAttackStatus(STATUS_ATTACK);
		}
	}

	if (INPUT->GetKeyDown('Z')
		&& pokemon.GetStatus() == STATUS_IDLE) {
		float tempX = pokemon.GetX();
		float tempY = pokemon.GetY();
		Status tempAttackStatus = pokemon.GetAttackStatus();

		if (GAME->CheckGameOver()) {

		}
		else {
			GAME->NextSelectNum();
			pokemon = GAME->GetPokemon(GAME->GetSelectNum());
			pokemon.SetX(tempX);
			pokemon.SetY(tempY);
			pokemon.SetWidth(50);
			pokemon.SetHeight(50);
			pokemon.SetDirection(player.GetDirection());
			pokemon.SetStatus(STATUS_IDLE);
			pokemon.SetAttackStatus(tempAttackStatus);
		}
	}


	// enemy
	for (int i = 0; i < POKEMON_COUNT; i++) {

		if (enemy[i].GetDied() == false) {
			switch (enemy[i].GetStatus())
			{
			case STATUS_IDLE:
				PokemonIdle(enemy[i], enemy[i].GetAniMaxNum(STATUS_IDLE));
				if (GetDistance(
					enemy[i].GetX(), enemy[i].GetY(), player.GetX(), player.GetY()) > 60) {

					if (GetDistance(
						enemy[i].GetX(), enemy[i].GetY(), 
						pokemon.GetX(), pokemon.GetY()) <= 50)
						PokemonAttack(enemy[i], 
							enemy[i].GetAniMaxNum(STATUS_ATTACK), 
							enemy[i].GetAniMaxNum(STATUS_IDLE), true);

					if (enemy[i].GetStatus() == STATUS_IDLE)
						PokemonMove(enemy[i], 
							enemy[i].GetAniMaxNum(STATUS_MOVE), 
							2.5f, FindDirection(enemy[i], player), true);
				}
				else {
					// 캐릭터 바라보게 하기
					if (player.GetX() > enemy[i].GetX() + enemy[i].GetWidth())
						enemy[i].SetDirection(DIRECTION_RIGHT);
					if (player.GetX() + player.GetWidth() < enemy[i].GetX())
						enemy[i].SetDirection(DIRECTION_LEFT);
					if (player.GetY() > enemy[i].GetY() + enemy[i].GetHeight())
						enemy[i].SetDirection(DIRECTION_DOWN);
					if (player.GetY() + player.GetHeight() < enemy[i].GetY())
						enemy[i].SetDirection(DIRECTION_UP);
					//PokemonIdle(enemy[i], 2);
					PokemonAttack(enemy[i], 
						enemy[i].GetAniMaxNum(STATUS_ATTACK),
						enemy[i].GetAniMaxNum(STATUS_IDLE), true);
				}
				break;
			case STATUS_MOVE:
				if (GetDistance(
					enemy[i].GetX(), enemy[i].GetY(), player.GetX(), player.GetY()) > 60) {

					if (GetDistance(
						enemy[i].GetX(), enemy[i].GetY(), pokemon.GetX(), pokemon.GetY()) <= 60)
						PokemonAttack(enemy[i], 
							enemy[i].GetAniMaxNum(STATUS_ATTACK),
							enemy[i].GetAniMaxNum(STATUS_IDLE), true);

					if (enemy[i].GetStatus() == STATUS_MOVE)
						PokemonMove(enemy[i], 
							enemy[i].GetAniMaxNum(STATUS_MOVE), 
							2.5f, FindDirection(enemy[i], player));
				}
				else {
					// 캐릭터 바라보게 하기
					if (player.GetX() > enemy[i].GetX() + enemy[i].GetWidth())
						enemy[i].SetDirection(DIRECTION_RIGHT);
					if (player.GetX() + player.GetWidth() < enemy[i].GetX())
						enemy[i].SetDirection(DIRECTION_LEFT);
					if (player.GetY() > enemy[i].GetY() + enemy[i].GetHeight())
						enemy[i].SetDirection(DIRECTION_DOWN);
					if (player.GetY() + player.GetHeight() < enemy[i].GetY())
						enemy[i].SetDirection(DIRECTION_UP);
					//PokemonIdle(enemy[i], 2);
					PokemonAttack(enemy[i], 
						enemy[i].GetAniMaxNum(STATUS_ATTACK),
						enemy[i].GetAniMaxNum(STATUS_IDLE), true);
				}
				break;
			case STATUS_ATTACK:
				RECT temp2 = enemy[i].GetMeleeAttack().rc;
				// 플레이어를 공격할 때
				if (IntersectRect(&temp, &temp2, &player.GetRect())) {

					if (enemy[i].GetMeleeAttack().isAttack) {
						player.AddHp(-enemy[i].GetAtk());
						if (player.GetHp() <= 0)
							player.SetHp(0);
					}
					enemy[i].MeleeAttack(false);

					if (pokemon.GetMeleeAttack().isAttack == true)
						pokemon.MeleeAttack(false);

					switch (enemy[i].GetDirection())
					{
					case DIRECTION_DOWN:
						pokemon.AddY(SPEED);
						player.AddY(SPEED);

						if (pokemon.GetY() > WINSIZEY || player.GetY() > WINSIZEY)
						{
							player.Init(DIRECTION_UP, 
								WINSIZEX / 2, WINSIZEY / 2, 40, 50);
							pokemon.SetX(WINSIZEX / 2);
							pokemon.SetY(WINSIZEY / 2 - player.GetHeight());
							pokemon.SetDirection(DIRECTION_UP);
							pokemon.SetStatus(STATUS_IDLE);
						}
						break;
					case DIRECTION_UP:
						pokemon.AddY(-SPEED);
						player.AddY(-SPEED);

						if (pokemon.GetY() < 0 || player.GetY() < 0)
						{
							player.Init(DIRECTION_UP,
								WINSIZEX / 2, WINSIZEY / 2, 40, 50);
							pokemon.SetX(WINSIZEX / 2);
							pokemon.SetY(WINSIZEY / 2 - player.GetHeight());
							pokemon.SetDirection(DIRECTION_UP);
							pokemon.SetStatus(STATUS_IDLE);
						}
						break;
					case DIRECTION_LEFT:
						pokemon.AddX(-SPEED);
						player.AddX(-SPEED);

						if (pokemon.GetX() < 0 || player.GetX() < 0) {
							player.Init(DIRECTION_UP,
								WINSIZEX / 2, WINSIZEY / 2, 40, 50);
							pokemon.SetX(WINSIZEX / 2);
							pokemon.SetY(WINSIZEY / 2 - player.GetHeight());
							pokemon.SetDirection(DIRECTION_UP);
							pokemon.SetStatus(STATUS_IDLE);
						}
						break;
					case DIRECTION_RIGHT:
						pokemon.AddX(SPEED);
						player.AddX(SPEED);

						if (pokemon.GetX() > WINSIZEX || player.GetX() > WINSIZEX) {
							player.Init(DIRECTION_UP,
								WINSIZEX / 2, WINSIZEY / 2, 40, 50);
							pokemon.SetX(WINSIZEX / 2);
							pokemon.SetY(WINSIZEY / 2 - player.GetHeight());
							pokemon.SetDirection(DIRECTION_UP);
							pokemon.SetStatus(STATUS_IDLE);
						}
						break;
					}
				}
				// 포켓몬을 공격할 때
				if (IntersectRect(&temp, &pokemon.GetRect(), &temp2)) {
		
					if (enemy[i].GetMeleeAttack().isAttack) {
  						GAME->GetPokemon(GAME->GetSelectNum()).AddHp(-enemy[i].GetAtk());
						if (GAME->GetPokemon(GAME->GetSelectNum()).GetHp() <= 0) {
							GAME->GetPokemon(GAME->GetSelectNum()).SetHp(0);
							GAME->GetPokemon(GAME->GetSelectNum()).SetDied(true);

							if (GAME->CheckGameOver()) {

							}
							else {
								float tempX = pokemon.GetX();
								float tempY = pokemon.GetY();
								Status tempAttackStatus = pokemon.GetAttackStatus();
								GAME->NextSelectNum();
								pokemon = GAME->GetPokemon(GAME->GetSelectNum());
								pokemon.SetX(tempX);
								pokemon.SetY(tempY);
								pokemon.SetWidth(50);
								pokemon.SetHeight(50);
								pokemon.SetDirection(player.GetDirection());
								pokemon.SetStatus(STATUS_IDLE);
								pokemon.SetAttackStatus(tempAttackStatus);
							}
						}
					}
					enemy[i].MeleeAttack(false);

					pokemon.SetStatus(STATUS_HURT);
					if (pokemon.GetMeleeAttack().isAttack == true)
						pokemon.MeleeAttack(false);
					// 포켓몬 마주보게 하기
					switch (enemy[i].GetDirection())
					{
					case DIRECTION_DOWN:
						pokemon.SetDirection(DIRECTION_UP);
						pokemon.AddY(SPEED);
						player.AddY(SPEED);

						if (pokemon.GetY() > WINSIZEY ||player.GetY() > WINSIZEY)
						{
							player.Init(DIRECTION_UP,
								WINSIZEX / 2, WINSIZEY / 2, 40, 50);
							pokemon.SetX(WINSIZEX / 2);
							pokemon.SetY(WINSIZEY / 2 - player.GetHeight());
							pokemon.SetDirection(DIRECTION_UP);
							pokemon.SetStatus(STATUS_IDLE);
						}
						break;
					case DIRECTION_UP:
						pokemon.SetDirection(DIRECTION_DOWN);
						pokemon.AddY(-SPEED);
						player.AddY(-SPEED);

						if (pokemon.GetY() < 0 || player.GetY() < 0)
						{
							player.Init(DIRECTION_UP,
								WINSIZEX / 2, WINSIZEY / 2, 40, 50);
							pokemon.SetX(WINSIZEX / 2);
							pokemon.SetY(WINSIZEY / 2 - player.GetHeight());
							pokemon.SetDirection(DIRECTION_UP);
							pokemon.SetStatus(STATUS_IDLE);
						}
						break;
					case DIRECTION_LEFT:
						pokemon.SetDirection(DIRECTION_RIGHT);
						pokemon.AddX(-SPEED);
						player.AddX(-SPEED);

						if (pokemon.GetX() < 0 || player.GetX() < 0) {
							player.Init(DIRECTION_UP,
								WINSIZEX / 2, WINSIZEY / 2, 40, 50);
							pokemon.SetX(WINSIZEX / 2);
							pokemon.SetY(WINSIZEY / 2 - player.GetHeight());
							pokemon.SetDirection(DIRECTION_UP);
							pokemon.SetStatus(STATUS_IDLE);
						}
						break;
					case DIRECTION_RIGHT:
						pokemon.SetDirection(DIRECTION_LEFT);
						pokemon.AddX(SPEED);
						player.AddX(SPEED);

						if (pokemon.GetX() > WINSIZEX || player.GetX() > WINSIZEX) {
							player.Init(DIRECTION_UP,
								WINSIZEX / 2, WINSIZEY / 2, 40, 50);
							pokemon.SetX(WINSIZEX / 2);
							pokemon.SetY(WINSIZEY / 2 - player.GetHeight());
							pokemon.SetDirection(DIRECTION_UP);
							pokemon.SetStatus(STATUS_IDLE);
						}
						break;
					}
					switch (pokemon.GetDirection())
					{
					case DIRECTION_DOWN:
						pokemon.SetMoveFrame(0);
						break;
					case DIRECTION_UP:
						pokemon.SetMoveFrame(
							pokemon.GetAniMaxNum(STATUS_HURT));
						break;
					case DIRECTION_LEFT:
						pokemon.SetMoveFrame(
							pokemon.GetAniMaxNum(STATUS_HURT) * 2);
						break;
					case DIRECTION_RIGHT:
						pokemon.SetMoveFrame(
							pokemon.GetAniMaxNum(STATUS_HURT) * 3);
						break;
					}
				}
				PokemonAttack(enemy[i],
					enemy[i].GetAniMaxNum(STATUS_ATTACK),
					enemy[i].GetAniMaxNum(STATUS_IDLE));
				break;
			case STATUS_SPECIAL_ATTACK:
				break;
			case STATUS_HURT:
				if (enemy[i].GetHp() <= 0) {
					enemy[i].AddAlpha(-1);
					if (enemy[i].GetAlpha() <= 0) {
						enemy[i].SetDied(true);
					}
				}

				if (enemy[i].GetHp() > 0) {
					enemy[i].SetMoveFrame(enemy[i].GetMoveFrame() + 0.1f);

					switch (enemy[i].GetDirection())
					{
					case DIRECTION_DOWN:
						if (enemy[i].GetMoveFrame() >= 1) {
							//enemy[i].SetStatus(STATUS_IDLE);
							//enemy[i].SetMoveFrame(0);
 							PokemonIdle(enemy[i], enemy[i].GetAniMaxNum(STATUS_IDLE));
						}
						break;
					case DIRECTION_UP:
						if (enemy[i].GetMoveFrame() >= 2) {
							//enemy[i].SetStatus(STATUS_IDLE);
							//enemy[i].SetMoveFrame(2);
							PokemonIdle(enemy[i], enemy[i].GetAniMaxNum(STATUS_IDLE));
						}
						break;
					case DIRECTION_LEFT:
						if (enemy[i].GetMoveFrame() >= 3) {
							//enemy[i].SetStatus(STATUS_IDLE);
							//enemy[i].SetMoveFrame(4);
							PokemonIdle(enemy[i], enemy[i].GetAniMaxNum(STATUS_IDLE));
						}
						break;
					case DIRECTION_RIGHT:
						if (enemy[i].GetMoveFrame() >= 4) {
							//enemy[i].SetStatus(STATUS_IDLE);
							//enemy[i].SetMoveFrame(6);
							PokemonIdle(enemy[i], enemy[i].GetAniMaxNum(STATUS_IDLE));
						}
						break;
					}
				}
				break;
			case STATUS_ATTACK2:
				break;
			}
		}
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
		for (int i = 0; i < POKEMON_COUNT; i++) {
			if (enemy[i].GetDied() == false) {
				RECT temp2 = pokemon.GetMeleeAttack().rc;
				if (IntersectRect(&temp, &enemy[i].GetRect(), &temp2)) {
					currentEnemy = i;

					if (enemy[i].GetStatus() != STATUS_HURT) {
     						enemy[i].AddHp(-GAME->GetPokemon(GAME->GetSelectNum()).GetAtk());
						if (enemy[i].GetHp() <= 0) {
							enemy[i].SetHp(0);
						}
					}

					enemy[i].SetStatus(STATUS_HURT);
					if (enemy[i].GetMeleeAttack().isAttack == true)
						enemy[i].MeleeAttack(false);
					// 포켓몬 마주보게 하기
					switch (pokemon.GetDirection())
					{
					case DIRECTION_DOWN:
						enemy[i].SetDirection(DIRECTION_UP);
						enemy[i].AddY(SPEED);
						break;
					case DIRECTION_UP:
						enemy[i].SetDirection(DIRECTION_DOWN);
						enemy[i].AddY(-SPEED);
						break;
					case DIRECTION_LEFT:
						enemy[i].SetDirection(DIRECTION_RIGHT);
						enemy[i].AddX(-SPEED);
						break;
					case DIRECTION_RIGHT:
						enemy[i].SetDirection(DIRECTION_LEFT);
						enemy[i].AddX(SPEED);
						break;
					}
					switch (enemy[i].GetDirection())
					{
					case DIRECTION_DOWN:
						enemy[i].SetMoveFrame(0);
						break;
					case DIRECTION_UP:
						enemy[i].SetMoveFrame(
							enemy[i].GetAniMaxNum(STATUS_HURT));
						break;
					case DIRECTION_LEFT:
						enemy[i].SetMoveFrame(
							enemy[i].GetAniMaxNum(STATUS_HURT) * 2);
						break;
					case DIRECTION_RIGHT:
						enemy[i].SetMoveFrame(
							enemy[i].GetAniMaxNum(STATUS_HURT) * 3);
						break;
					}
				}
			}
		}
		pokemon.SetMoveFrame(pokemon.GetMoveFrame() + 0.1f);
		switch (pokemon.GetDirection())
		{
		case DIRECTION_DOWN:
			//if (moveFrame >= 1) {
			if(pokemon.GetMoveFrame() >= pokemon.GetAniMaxNum(STATUS_ATTACK)) {
				pokemon.SetStatus(STATUS_IDLE);
				//moveFrame = 0;
				pokemon.SetMoveFrame(0);
				pokemon.MeleeAttack(false);
			}
			break;
		case DIRECTION_UP:
			//if (moveFrame >= 2) {
			if (pokemon.GetMoveFrame() >= 
					pokemon.GetAniMaxNum(STATUS_ATTACK) * 2) {
				pokemon.SetStatus(STATUS_IDLE);
				//moveFrame = 1;
				pokemon.SetMoveFrame(pokemon.GetAniMaxNum(STATUS_IDLE));
				pokemon.MeleeAttack(false);
			}
			break;
		case DIRECTION_LEFT:
			//if (moveFrame >= 3) {
			if (pokemon.GetMoveFrame() >= 
					pokemon.GetAniMaxNum(STATUS_ATTACK) * 3) {
				pokemon.SetStatus(STATUS_IDLE);
				//moveFrame = 2;
				pokemon.SetMoveFrame(pokemon.GetAniMaxNum(STATUS_IDLE) * 2);
				pokemon.MeleeAttack(false);
			}
			break;
		case DIRECTION_RIGHT:
			//if (moveFrame >= 4) {
			if(pokemon.GetMoveFrame() >= 
					pokemon.GetAniMaxNum(STATUS_ATTACK) * 4) {
				pokemon.SetStatus(STATUS_IDLE);
				//moveFrame = 3;
				pokemon.SetMoveFrame(pokemon.GetAniMaxNum(STATUS_IDLE) * 3);
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
			if (pokemon.GetMoveFrame() >= 
					pokemon.GetAniMaxNum(STATUS_SPECIAL_ATTACK)) {
				pokemon.SetStatus(STATUS_IDLE);
				//moveFrame = 0;
				pokemon.SetMoveFrame(0);
			}
			break;
		case DIRECTION_UP:
			//if (moveFrame >= 4) {
			if (pokemon.GetMoveFrame() >= 
					pokemon.GetAniMaxNum(STATUS_SPECIAL_ATTACK) * 2) {
				pokemon.SetStatus(STATUS_IDLE);
				//moveFrame = 1;
				pokemon.SetMoveFrame(pokemon.GetAniMaxNum(STATUS_IDLE));
			}
			break;
		case DIRECTION_LEFT:
			//if (moveFrame >= 6) {
			if (pokemon.GetMoveFrame() >= 
				pokemon.GetAniMaxNum(STATUS_SPECIAL_ATTACK) * 3) {
				pokemon.SetStatus(STATUS_IDLE);
				//moveFrame = 2;
				pokemon.SetMoveFrame(pokemon.GetAniMaxNum(STATUS_IDLE) * 2);
			}
			break;
		case DIRECTION_RIGHT:
			//if (moveFrame >= 8) {
			if (pokemon.GetMoveFrame() >= 
					pokemon.GetAniMaxNum(STATUS_SPECIAL_ATTACK) * 4) {
				pokemon.SetStatus(STATUS_IDLE);
				//moveFrame = 3;
				pokemon.SetMoveFrame(pokemon.GetAniMaxNum(STATUS_IDLE) * 3);
			}
			break;
		}
		break;
	case STATUS_HURT:
		PokemonHurt(pokemon, pokemon.GetAniMaxNum(STATUS_IDLE));
		break;
	}

	pokemon.BulletMove();

	for (int i = 0; i < BULLETMAX; i++) {
		if (pokemon.GetBullet(i)->isFire == false) continue;

		for (int j = 0; j < POKEMON_COUNT; j++) {
			if (enemy[j].GetDied() == true) continue;
			// 죽어가는 시체 무시
			if (enemy[j].GetAlpha() != 255) continue;

			RECT bulletTemp = pokemon.GetBullet(i)->rc;
			RECT temp2 = enemy[j].GetRect();
			if (IntersectRect(&temp, &temp2, &bulletTemp)) {
				currentEnemy = j;

				enemy[i].AddHp(-pokemon.GetSpAtk());
				if (enemy[i].GetHp() <= 0) {
					enemy[i].SetHp(0);
				}

				pokemon.GetBullet(i)->isFire = false;
				enemy[j].SetStatus(STATUS_HURT);
				switch (pokemon.GetBullet(i)->dir)
				{
				case DIRECTION_DOWN:
					enemy[j].SetDirection(DIRECTION_UP);
					break;
				case DIRECTION_UP:
					enemy[j].SetDirection(DIRECTION_DOWN);
					break;
				case DIRECTION_LEFT:
					enemy[j].SetDirection(DIRECTION_RIGHT);
					break;
				case DIRECTION_RIGHT:
					enemy[j].SetDirection(DIRECTION_LEFT);
					break;
				}

				switch (enemy[j].GetDirection())
				{
				case DIRECTION_DOWN:
					enemy[j].SetMoveFrame(0);
					break;
				case DIRECTION_UP:
					enemy[j].SetMoveFrame(
						enemy[j].GetAniMaxNum(STATUS_HURT));
					break;
				case DIRECTION_LEFT:
					enemy[j].SetMoveFrame(
						enemy[j].GetAniMaxNum(STATUS_HURT) * 2);
					break;
				case DIRECTION_RIGHT:
					enemy[j].SetMoveFrame(
						enemy[j].GetAniMaxNum(STATUS_HURT) * 3);
					break;
				}
			}
		}
	}

	// hpBar Change
	//hpBar[0].right = hpBar[0].left + width 
	//	* GAME->GetPokemon(0).GetHp() / GAME->GetPokemon(0).GetMaxHp();
	ChangeHpBar();


	if (INPUT->GetKeyDown(VK_TAB)) {
		isDebug = !isDebug;
	}
}

void TestScene::Render()
{
	//IMAGE->FrameRender("BackGround", GetMemDC(), 0, 0, 0, 0);
	bg->Render(GetMemDC(), -WINSIZEX/4, -WINSIZEY/4);

	DrawUI();

	player.GetAni(0)->FrameRender(GetMemDC(),
		player.GetX(), player.GetY(), 
		(int)player.GetMoveFrame(), player.GetDirection());

	//IMAGE->FrameRender(  "Pikachu_attack", GetMemDC(),
	//	IMAGE->FindImage("Pikachu_attack")->GetX(),
	//	IMAGE->FindImage("Pikachu_attack")->GetY(),
	//	moveFrame, 0);

	//pikachu[pokemon.GetStatus()]->FrameRender(GetMemDC(), 
	//	pokemon.GetX(), pokemon.GetY(), (int)moveFrame, 0);
	//pikachu[pokemon.GetStatus()]->FrameRender(GetMemDC(), 
	//	pokemon.GetX(), pokemon.GetY(), (int)pokemon.GetMoveFrame(), 0);

	pokemon.GetAni(pokemon.GetStatus())->FrameRender(GetMemDC(),
		pokemon.GetX(), pokemon.GetY(), (int)pokemon.GetMoveFrame(), 0);
	//enemy.GetAni(enemy.GetStatus())->FrameRender(GetMemDC(),
	//	enemy.GetX(), enemy.GetY(), (int)enemy.GetMoveFrame(), 0);

	for (int i = 0; i < POKEMON_COUNT; i++) {
		enemy[i].GetAni(enemy[i].GetStatus())->FrameRender(GetMemDC(),
			enemy[i].GetX(), enemy[i].GetY(), (int)enemy[i].GetMoveFrame(), 0,
			enemy[i].GetAlpha());

		switch (enemyHpStatus[i]) {
		case 0:
			BeginSolidColor(GetMemDC(), &hBrush, fullHp);
			break;
		case 1:
			BeginSolidColor(GetMemDC(), &hBrush, halfHp);
			break;
		case 2:
			BeginSolidColor(GetMemDC(), &hBrush, littleHp);
			break;
		}
		hOldBrush = (HBRUSH)SelectObject(GetMemDC(), hBrush);

		RectangleMake(GetMemDC(), enemyHpBar[i]);

		SelectObject(GetMemDC(), hOldBrush);
		DeleteObject(hBrush);

	}

	//charmander[enemy.GetStatus()]->FrameRender(GetMemDC(),
	//	enemy.GetX(), enemy.GetY(), (int)enemy.GetMoveFrame(), 0);

	for (int i = 0; i < BULLETMAX; i++) {
		if (pokemon.GetBullet(i)->isFire == false) continue;
		
		switch (pokemon.GetEffectNum())
		{
		case EFFECT_ELECTRICITY:
			effect[pokemon.GetEffectNum()]->FrameRender(GetMemDC(),
				pokemon.GetBullet(i)->x - 25, pokemon.GetBullet(i)->y - 25,
				(int)pokemon.GetBullet(i)->moveFrame, 0);
			break;
		case EFFECT_FIRE:
			effect[pokemon.GetEffectNum()]->FrameRender(GetMemDC(),
				pokemon.GetBullet(i)->x, pokemon.GetBullet(i)->y,
				(int)pokemon.GetBullet(i)->moveFrame, 0);
			break;
		case EFFECT_WATER:
			effect[pokemon.GetEffectNum()]->FrameRender(GetMemDC(),
				pokemon.GetBullet(i)->x, pokemon.GetBullet(i)->y,
				(int)pokemon.GetBullet(i)->moveFrame, 0);
			break;
		case EFFECT_GRASS:
			effect[pokemon.GetEffectNum()]->FrameRender(GetMemDC(),
				pokemon.GetBullet(i)->x + 12.5f, pokemon.GetBullet(i)->y + 12.5f,
				(int)pokemon.GetBullet(i)->moveFrame, 0);
			break;
		case EFFECT_END:
			break;
		}
	} 

	if (isDebug) {
		if (pokemon.GetMeleeAttack().isAttack)	
			RectangleMake(GetMemDC(), pokemon.GetMeleeAttack().rc);
		
		for (int i = 0; i < POKEMON_COUNT; i++) {
			if (enemy[i].GetMeleeAttack().isAttack)
				RectangleMake(GetMemDC(), enemy[i].GetMeleeAttack().rc);
		}

		for (int i = 0; i < BULLETMAX; i++) {
			if (pokemon.GetBullet(i)->isFire == false) continue;
			RectangleMake(GetMemDC(), pokemon.GetBullet(i)->rc);
		}

		//effect->Render(GetMemDC(), -300, WINSIZEY/2);
	}
}

void TestScene::Idle()
{
	switch (player.GetDirection())
	{
	case DIRECTION_DOWN:
		//moveFrame = 0;
		pokemon.SetMoveFrame(0);
		break;
	case DIRECTION_UP:
		//moveFrame = 1;
		pokemon.SetMoveFrame(
			pokemon.GetAniMaxNum(STATUS_IDLE));
		break;
	case DIRECTION_LEFT:
		//moveFrame = 2;
		pokemon.SetMoveFrame(
			pokemon.GetAniMaxNum(STATUS_IDLE) * 2);
		break;
	case DIRECTION_RIGHT:
		//moveFrame = 3;
		pokemon.SetMoveFrame(
			pokemon.GetAniMaxNum(STATUS_IDLE) * 3);
		break;
	}

	// move
	if (INPUT->GetKey(VK_DOWN)) {
		player.SetDirection(DIRECTION_DOWN);
		player.SetMoveFrame(0);

		pokemon.SetDirection(DIRECTION_DOWN);
		pokemon.SetStatus(STATUS_MOVE);
		//moveFrame = 0;
		pokemon.SetMoveFrame(0);
	}
	if (INPUT->GetKey(VK_UP)) {
		player.SetDirection(DIRECTION_UP);
		player.SetMoveFrame(0);

		pokemon.SetDirection(DIRECTION_UP);
		pokemon.SetStatus(STATUS_MOVE);
		//moveFrame = 3;
		pokemon.SetMoveFrame(
			pokemon.GetAniMaxNum(STATUS_MOVE));
	}
	if (INPUT->GetKey(VK_LEFT)) {
		player.SetDirection(DIRECTION_LEFT);
		player.SetMoveFrame(0);

		pokemon.SetDirection(DIRECTION_LEFT);
		pokemon.SetStatus(STATUS_MOVE);
		//moveFrame = 6;
		pokemon.SetMoveFrame(
			pokemon.GetAniMaxNum(STATUS_MOVE) * 2);
	}
	if (INPUT->GetKey(VK_RIGHT)) {
		player.SetDirection(DIRECTION_RIGHT);
		player.SetMoveFrame(0);

		pokemon.SetDirection(DIRECTION_RIGHT);
		pokemon.SetStatus(STATUS_MOVE);
		//moveFrame = 9;
		pokemon.SetMoveFrame(
			pokemon.GetAniMaxNum(STATUS_MOVE) * 3);
	}
}

void TestScene::Move()
{
	bool isFrameMove = false;

	if (INPUT->GetKey(VK_DOWN) && 
		pokemon.GetY() + pokemon.GetHeight() < WINSIZEY) { 
		player.AddY(SPEED);
		isFrameMove = true;
		//pokemon.SetY(pokemon.GetY() + SPEED); 
		pokemon.SetX(player.GetX() + 5);
		pokemon.SetY(player.GetY() + player.GetHeight());
	}
	if (INPUT->GetKey(VK_UP) &&
		pokemon.GetY() > 0) {
		player.AddY(-SPEED);
		isFrameMove = true;
		//pokemon.SetY(pokemon.GetY() - SPEED); 
		pokemon.SetX(player.GetX());
		pokemon.SetY(player.GetY() - pokemon.GetHeight());
	}
	if (INPUT->GetKey(VK_LEFT) &&
		pokemon.GetX() > 0) { 
		player.AddX(-SPEED);
		isFrameMove = true;
		//pokemon.SetX(pokemon.GetX() - SPEED); 
		pokemon.SetX(player.GetX() - pokemon.GetWidth());
		pokemon.SetY(player.GetY() + 10);
	}
	if (INPUT->GetKey(VK_RIGHT) &&
		pokemon.GetX() + pokemon.GetWidth() < WINSIZEX) { 
		player.AddX(SPEED);
		isFrameMove = true;
		//pokemon.SetX(pokemon.GetX() + SPEED); 
		pokemon.SetX(player.GetX() + player.GetWidth() + 10);
		pokemon.SetY(player.GetY() + 10);
	}

	if (isFrameMove) {
		player.AddMoveFrame(0.1f);
		if ((int)player.GetMoveFrame() > 2)
			player.SetMoveFrame(0);
	}

	// 방향키 땠을 때 다시 idle로
	if (INPUT->GetKeyUp(VK_DOWN)) {
		player.SetMoveFrame(PLAYER_IDLE);

		pokemon.SetStatus(STATUS_IDLE);
		pokemon.SetDirection(DIRECTION_DOWN);
		//moveFrame = 0;
		pokemon.SetMoveFrame(0);
	}
	if (INPUT->GetKeyUp(VK_UP)) {
		player.SetMoveFrame(PLAYER_IDLE);
		
		pokemon.SetStatus(STATUS_IDLE);
		pokemon.SetDirection(DIRECTION_UP);
		//moveFrame = 1;
		pokemon.SetMoveFrame(
			pokemon.GetAniMaxNum(STATUS_IDLE));
	}
	if (INPUT->GetKeyUp(VK_LEFT)) {
		player.SetMoveFrame(PLAYER_IDLE);

		pokemon.SetStatus(STATUS_IDLE);
		pokemon.SetDirection(DIRECTION_LEFT);
		//moveFrame = 2;
		pokemon.SetMoveFrame(
			pokemon.GetAniMaxNum(STATUS_IDLE) * 2);
	}
	if (INPUT->GetKeyUp(VK_RIGHT)) {
		player.SetMoveFrame(PLAYER_IDLE);
		
		pokemon.SetStatus(STATUS_IDLE);
		pokemon.SetDirection(DIRECTION_RIGHT);
		//moveFrame = 3;
		pokemon.SetMoveFrame(
			pokemon.GetAniMaxNum(STATUS_IDLE) * 3);
	}

	if (pokemon.GetStatus() == STATUS_MOVE) {
		//moveFrame += 0.1f;
		pokemon.SetMoveFrame(pokemon.GetMoveFrame() + 0.1f);
		switch (pokemon.GetDirection())
		{
		case DIRECTION_DOWN:
			//if (moveFrame > 2)
			if (pokemon.GetMoveFrame() >= 
					pokemon.GetAniMaxNum(STATUS_MOVE))
				//moveFrame = 0;
				pokemon.SetMoveFrame(0);
			break;
		case DIRECTION_UP:
			//if (moveFrame > 5)
			if (pokemon.GetMoveFrame() >= 
					pokemon.GetAniMaxNum(STATUS_MOVE) * 2)
				//moveFrame = 3;
				pokemon.SetMoveFrame(
					pokemon.GetAniMaxNum(STATUS_MOVE));
			break;
		case DIRECTION_LEFT:
			//if (moveFrame > 8)
			if (pokemon.GetMoveFrame() >=
				pokemon.GetAniMaxNum(STATUS_MOVE) * 3)
				//moveFrame = 6;
				pokemon.SetMoveFrame(
					pokemon.GetAniMaxNum(STATUS_MOVE) * 2);
			break;
		case DIRECTION_RIGHT:
			//if (moveFrame > 11)
			if (pokemon.GetMoveFrame() >= 
				pokemon.GetAniMaxNum(STATUS_MOVE) * 4)
				//moveFrame = 9;
				pokemon.SetMoveFrame(
					pokemon.GetAniMaxNum(STATUS_MOVE) * 3);
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
				pokemon.SetMoveFrame(
					pokemon.GetAniMaxNum(STATUS_ATTACK));
				pokemon.MeleeAttack(true);
				break;
			case STATUS_SPECIAL_ATTACK:
				//moveFrame = 2;
				pokemon.SetMoveFrame(
					pokemon.GetAniMaxNum(STATUS_SPECIAL_ATTACK));
				pokemon.BulletFire();
				break;
			}
			break;
		case DIRECTION_LEFT:
			switch (pokemon.GetStatus()) {
			case STATUS_ATTACK:
				//moveFrame = 2;
				pokemon.SetMoveFrame(
					pokemon.GetAniMaxNum(STATUS_ATTACK) * 2);
				pokemon.MeleeAttack(true);
				break;
			case STATUS_SPECIAL_ATTACK:
				//moveFrame = 4;
				pokemon.SetMoveFrame(
					pokemon.GetAniMaxNum(STATUS_SPECIAL_ATTACK) * 2);
				pokemon.BulletFire();
				break;
			}
			break;
		case DIRECTION_RIGHT:
			switch (pokemon.GetStatus()) {
			case STATUS_ATTACK:
				//moveFrame = 3;
				pokemon.SetMoveFrame(
					pokemon.GetAniMaxNum(STATUS_ATTACK) * 3);
				pokemon.MeleeAttack(true);
				break;
			case STATUS_SPECIAL_ATTACK:
				//moveFrame = 6;
				pokemon.SetMoveFrame(
					pokemon.GetAniMaxNum(STATUS_SPECIAL_ATTACK) * 3);
				pokemon.BulletFire();
				break;
			}
			break;
		}
	}
}

void TestScene::PokemonIdle(Pokemon& pokemon, int maxNum) {
	float moveFrame = 0.05f;

	switch (pokemon.GetDirection())
	{
	case DIRECTION_DOWN:
		if (pokemon.GetStatus() != STATUS_IDLE) {
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
		if (pokemon.GetStatus() != STATUS_IDLE) {
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
		if (pokemon.GetStatus() != STATUS_IDLE) {
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
		if (pokemon.GetStatus() != STATUS_IDLE) {
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

void TestScene::PokemonMove(Pokemon& pokemon, int maxNum,
	float speed, Direction dir, bool isStart) {
	if (isStart) {
		if (pokemon.GetStatus() != STATUS_MOVE)
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

void TestScene::PokemonAttack(Pokemon & pokemon, int maxNum, int idleMaxNum, bool isStart)
{
	if (isStart) {
		pokemon.SetStatus(pokemon.GetAttackStatus());
		switch (pokemon.GetDirection())
		{
		case DIRECTION_DOWN:
			pokemon.SetMoveFrame(0);
			pokemon.MeleeAttack(true);
			break;
		case DIRECTION_UP:
			pokemon.SetMoveFrame(maxNum);
			pokemon.MeleeAttack(true);
			break;
		case DIRECTION_LEFT:
			pokemon.SetMoveFrame(maxNum * 2);
			pokemon.MeleeAttack(true);
			break;
		case DIRECTION_RIGHT:
			pokemon.SetMoveFrame(maxNum * 3);
			pokemon.MeleeAttack(true);
			break;
		}
	}

	pokemon.AddMoveFrame(0.1f);

	switch (pokemon.GetDirection())
	{
	case DIRECTION_DOWN:
		if (pokemon.GetMoveFrame() >= maxNum) {
			pokemon.SetStatus(STATUS_IDLE);
			pokemon.SetMoveFrame(0);
			pokemon.MeleeAttack(false);
		}
		break;
	case DIRECTION_UP:
		if (pokemon.GetMoveFrame() >= maxNum * 2) {
			pokemon.SetStatus(STATUS_IDLE);
			pokemon.SetMoveFrame(idleMaxNum);
			pokemon.MeleeAttack(false);
		}
		break;
	case DIRECTION_LEFT:
		if (pokemon.GetMoveFrame() >= maxNum * 3) {
			pokemon.SetStatus(STATUS_IDLE);
			pokemon.SetMoveFrame(idleMaxNum * 2);
			pokemon.MeleeAttack(false);
		}
		break;
	case DIRECTION_RIGHT:
		if (pokemon.GetMoveFrame() >= maxNum * 4) {
			pokemon.SetStatus(STATUS_IDLE);
			pokemon.SetMoveFrame(idleMaxNum * 3);
			pokemon.MeleeAttack(false);
		}
		break;
	}
}

void TestScene::PokemonHurt(Pokemon & pokemon, int maxNum)
{
	pokemon.AddMoveFrame(0.1f);
	switch (pokemon.GetDirection())
	{
	case DIRECTION_DOWN:
		if (pokemon.GetMoveFrame() >= 1) {
			pokemon.SetStatus(STATUS_IDLE);
			pokemon.SetMoveFrame(0);
		}
		break;
	case DIRECTION_UP:
		if (pokemon.GetMoveFrame() >= 2) {
			pokemon.SetStatus(STATUS_IDLE);
			pokemon.SetMoveFrame(maxNum);
		}
		break;
	case DIRECTION_LEFT:
		if (pokemon.GetMoveFrame() >= 3) {
			pokemon.SetStatus(STATUS_IDLE);
			pokemon.SetMoveFrame(maxNum * 2);
		}
		break;
	case DIRECTION_RIGHT:
		if (pokemon.GetMoveFrame() >= 4) {
			pokemon.SetStatus(STATUS_IDLE);
			pokemon.SetMoveFrame(maxNum * 3);
		}
		break;
	}
}

Direction TestScene::FindDirection(Pokemon& pokemon, Unit& unit)
{
	if (abs(pokemon.GetX() - player.GetX()) > 10) {
		if (pokemon.GetX() < player.GetX()) {
			return DIRECTION_RIGHT;
		}
		else {
			return DIRECTION_LEFT;
		}
	}
	else if (abs(pokemon.GetY() - player.GetY()) > 10) {
		if (pokemon.GetY() < player.GetY()) {
			return DIRECTION_DOWN;
		}
		else
			return DIRECTION_UP;
	}
}

void TestScene::ChangeHpBar()
{
	for (int i = 0; i < 6; i++) {
		switch (i) {
		case 0:
			hpBar[i].right = hpBar[i].left + hpWidth[i]
				* GAME->GetPokemon(i).GetHp() / GAME->GetPokemon(i).GetMaxHp();

			if ((float)GAME->GetPokemon(i).GetHp()
				/ GAME->GetPokemon(i).GetMaxHp()
				<= 0.1f)
				hpStatus[i] = 2;
			else if ((float)GAME->GetPokemon(i).GetHp()
				/ GAME->GetPokemon(i).GetMaxHp()
				<= 0.5f)
				hpStatus[i] = 1;
			else
				hpStatus[i] = 0;

			break;
		case 1:
			if (GAME->GetPokemonCount() > i) {
				hpBar[i].right = hpBar[i].left + hpWidth[i]
					* GAME->GetPokemon(i).GetHp() / GAME->GetPokemon(i).GetMaxHp();

				if ((float)GAME->GetPokemon(i).GetHp()
					/ GAME->GetPokemon(i).GetMaxHp()
					<= 0.1f)
					hpStatus[i] = 2;
				else if ((float)GAME->GetPokemon(i).GetHp()
					/ GAME->GetPokemon(i).GetMaxHp()
					<= 0.5f)
					hpStatus[i] = 1;
				else
					hpStatus[i] = 0;
			}
			break;
		case 2:
			if (GAME->GetPokemonCount() > i) {
				hpBar[i].right = hpBar[i].left + hpWidth[i]
					* GAME->GetPokemon(i).GetHp() / GAME->GetPokemon(i).GetMaxHp();

				if ((float)GAME->GetPokemon(i).GetHp()
					/ GAME->GetPokemon(i).GetMaxHp()
					<= 0.1f)
					hpStatus[i] = 2;
				else if ((float)GAME->GetPokemon(i).GetHp()
					/ GAME->GetPokemon(i).GetMaxHp()
					<= 0.5f)
					hpStatus[i] = 1;
				else
					hpStatus[i] = 0;
			}
			break;
		case 3:
			if (GAME->GetPokemonCount() > i) {
				hpBar[i].right = hpBar[i].left + hpWidth[i]
					* GAME->GetPokemon(i).GetHp() / GAME->GetPokemon(i).GetMaxHp();

				if ((float)GAME->GetPokemon(i).GetHp()
					/ GAME->GetPokemon(i).GetMaxHp()
					<= 0.1f)
					hpStatus[i] = 2;
				else if ((float)GAME->GetPokemon(i).GetHp()
					/ GAME->GetPokemon(i).GetMaxHp()
					<= 0.5f)
					hpStatus[i] = 1;
				else
					hpStatus[i] = 0;
			}
			break;
		case 4:
			hpBar[i].right = hpBar[i].left + hpWidth[i]
				* player.GetHp() / player.GetMaxHp();

			if ((float)player.GetHp() / player.GetMaxHp()
				<= 0.1f)
				hpStatus[i] = 2;
			else if ((float)player.GetHp() / player.GetMaxHp()
				<= 0.5f)
				hpStatus[i] = 1;
			else
				hpStatus[i] = 0;
			break;
		case 5:
			hpBar[i].right = hpBar[i].left + hpWidth[i]
				* enemy[currentEnemy].GetHp() / enemy[currentEnemy].GetMaxHp();

			if ((float)enemy[currentEnemy].GetHp() / enemy[currentEnemy].GetMaxHp()
				<= 0.1f)
				hpStatus[i] = 2;
			else if ((float)enemy[currentEnemy].GetHp() / enemy[currentEnemy].GetMaxHp()
				<= 0.5f)
				hpStatus[i] = 1;
			else
				hpStatus[i] = 0;
			break;
		}
	}

	for (int i = 0; i < POKEMON_COUNT; i++) {
		enemyHpBar[i] = RectMake(enemy[i].GetX(), enemy[i].GetY() - 5,
			enemy[i].GetWidth(), 5);

		enemyHpBar[i].right = enemyHpBar[i].left + enemyHpWidth[i]
			* enemy[i].GetHp() / enemy[i].GetMaxHp();

		if ((float)enemy[i].GetHp() / enemy[i].GetMaxHp()
			<= 0.1f)
			enemyHpStatus[i] = 2;
		else if ((float)enemy[i].GetHp() / enemy[i].GetMaxHp()
			<= 0.5f)
			enemyHpStatus[i] = 1;
		else
			enemyHpStatus[i] = 0;
	}
}

void TestScene::DrawUI()
{
	float alpha = 225;

	SetBkMode(GetMemDC(), TRANSPARENT);
	SetTextColor(GetMemDC(), RGB(255, 255, 255));

	BeginCreateFont(GetMemDC(), &hFont, 20);
	oldFont = (HFONT)SelectObject(GetMemDC(), hFont);

	//ui[0]->Render(GetMemDC());
	//ui[0]->AlphaRender(GetMemDC(), 255);
	// pokemon
	for (int i = 0; i < GAME->GetPokemonCount(); i++) {
		if (i == 0) {
			if (i == GAME->GetSelectNum())
				ui[0]->AlphaRender(GetMemDC(), 0, 75, alpha);
			else
				ui[1]->AlphaRender(GetMemDC(), 0, 75, alpha);

			GAME->GetPokemon(i).GetPortrait()->
				AlphaRender(GetMemDC(), 70, 0, alpha);

			sprintf_s(str, "%s", GAME->GetPokemon(i).GetName().c_str());
			TextOut(GetMemDC(), 90, 105, str, strlen(str));

			sprintf_s(str, "%d", GAME->GetPokemon(i).GetLevel());
			TextOut(GetMemDC(), 135, 123, str, strlen(str));
		}
		if (i == 1) {
			if (i == GAME->GetSelectNum())
				ui[0]->AlphaRender(GetMemDC(), 200, 75, alpha);
			else
				ui[1]->AlphaRender(GetMemDC(), 200, 75, alpha);

			GAME->GetPokemon(i).GetPortrait()->
				AlphaRender(GetMemDC(), 270, 0, alpha);

			sprintf_s(str, "%s", GAME->GetPokemon(i).GetName().c_str());
			TextOut(GetMemDC(), 90 + 200, 105, str, strlen(str));

			sprintf_s(str, "%d", GAME->GetPokemon(i).GetLevel());
			TextOut(GetMemDC(), 135 + 200, 123, str, strlen(str));
		}
		if (i == 2) {
			if (i == GAME->GetSelectNum())
				ui[0]->AlphaRender(GetMemDC(), WINSIZEX - 400, 75, alpha);
			else
				ui[1]->AlphaRender(GetMemDC(), WINSIZEX - 400, 75, alpha);

			GAME->GetPokemon(i).GetPortrait()->
				AlphaRender(GetMemDC(), WINSIZEX - 330, 0, alpha);

			sprintf_s(str, "%s", GAME->GetPokemon(i).GetName().c_str());
			TextOut(GetMemDC(), WINSIZEX - 400 + 90, 105, str, strlen(str));

			sprintf_s(str, "%d", GAME->GetPokemon(i).GetLevel());
			TextOut(GetMemDC(), WINSIZEX - 400 + 135, 123, str, strlen(str));
		}
		if (i == 3) {
			if (i == GAME->GetSelectNum())
				ui[0]->AlphaRender(GetMemDC(), WINSIZEX - 200, 75, alpha);
			else
				ui[1]->AlphaRender(GetMemDC(), WINSIZEX - 200, 75, alpha);

			GAME->GetPokemon(i).GetPortrait()->
				AlphaRender(GetMemDC(), WINSIZEX - 130, 0, alpha);

			sprintf_s(str, "%s", GAME->GetPokemon(i).GetName().c_str());
			TextOut(GetMemDC(), WINSIZEX - 200 + 90, 105, str, strlen(str));

			sprintf_s(str, "%d", GAME->GetPokemon(i).GetLevel());
			TextOut(GetMemDC(), WINSIZEX - 200 + 135, 123, str, strlen(str));
		}
	}
	// player
	ui[1]->AlphaRender(GetMemDC(), 0, WINSIZEY - 100, alpha);
	player.GetPortrait()->AlphaRender(
		GetMemDC(), 70, WINSIZEY - 175, alpha);

	sprintf_s(str, "%s", player.GetName().c_str());
	TextOut(GetMemDC(), 100, 696, str, strlen(str));

	sprintf_s(str, "%d", player.GetLevel());
	TextOut(GetMemDC(), 135, 715, str, strlen(str));

	// enemy
	ui[1]->AlphaRender(GetMemDC(), WINSIZEX - 200, WINSIZEY - 100, alpha);
	enemy[currentEnemy].GetPortrait()->AlphaRender(
		GetMemDC(), WINSIZEX - 130, WINSIZEY - 175, alpha);

	sprintf_s(str, "%s", enemy[currentEnemy].GetName().c_str());
	TextOut(GetMemDC(), WINSIZEX - 200 + 100, 696, str, strlen(str));

	sprintf_s(str, "%d", enemy[currentEnemy].GetLevel());
	TextOut(GetMemDC(), WINSIZEX - 200 + 135, 715, str, strlen(str));

	SetTextColor(GetMemDC(), RGB(0, 0, 0));

	SelectObject(GetMemDC(), oldFont);
	DeleteObject(hFont);

	// hpBar
	for (int i = 0; i < 6; i++) {
		switch (hpStatus[i]) {
		case 0:
			BeginSolidColor(GetMemDC(), &hBrush, fullHp);
			break;
		case 1:
			BeginSolidColor(GetMemDC(), &hBrush, halfHp);
			break;
		case 2:
			BeginSolidColor(GetMemDC(), &hBrush, littleHp);
			break;
		}
		hOldBrush = (HBRUSH)SelectObject(GetMemDC(), hBrush);

		RectangleMake(GetMemDC(), hpBar[i]);

		SelectObject(GetMemDC(), hOldBrush);
		DeleteObject(hBrush);

	}

	// hp , maxHp
	for (int i = 0; i < GAME->GetPokemonCount(); i++) {
		if (i == 0) {
			sprintf_s(str, "%d", GAME->GetPokemon(i).GetHp());
			TextOut(GetMemDC(), 112, 155, str, strlen(str));
			sprintf_s(str, "%d", GAME->GetPokemon(i).GetMaxHp());
			TextOut(GetMemDC(), 155, 155, str, strlen(str));
		}
		if (i == 1) {
			sprintf_s(str, "%d", GAME->GetPokemon(i).GetHp());
			TextOut(GetMemDC(), 112 + 200, 155, str, strlen(str));
			sprintf_s(str, "%d", GAME->GetPokemon(i).GetMaxHp());
			TextOut(GetMemDC(), 155 + 200, 155, str, strlen(str));
		}
		if (i == 2) {
			sprintf_s(str, "%d", GAME->GetPokemon(i).GetHp());
			TextOut(GetMemDC(), WINSIZEX - 400 + 112, 155, str, strlen(str));
			sprintf_s(str, "%d", GAME->GetPokemon(i).GetMaxHp());
			TextOut(GetMemDC(), WINSIZEX - 400 + 155, 155, str, strlen(str));
		}
		if (i == 3) {
			sprintf_s(str, "%d", GAME->GetPokemon(i).GetHp());
			TextOut(GetMemDC(), WINSIZEX - 200 + 112, 155, str, strlen(str));
			sprintf_s(str, "%d", GAME->GetPokemon(i).GetMaxHp());
			TextOut(GetMemDC(), WINSIZEX - 200 + 155, 155, str, strlen(str));
		}
	}

	// player
	sprintf_s(str, "%d", player.GetHp());
	TextOut(GetMemDC(), 112, WINSIZEY - 175 + 155, str, strlen(str));
	sprintf_s(str, "%d", player.GetMaxHp());
	TextOut(GetMemDC(), 155, WINSIZEY - 175 + 155, str, strlen(str));

	// enemy
	sprintf_s(str, "%d", enemy[currentEnemy].GetHp());
	TextOut(GetMemDC(), WINSIZEX - 200 + 112, WINSIZEY - 175 + 155, str, strlen(str));
	sprintf_s(str, "%d", enemy[currentEnemy].GetMaxHp());
	TextOut(GetMemDC(), WINSIZEX - 200 + 155, WINSIZEY - 175 + 155, str, strlen(str));
}
