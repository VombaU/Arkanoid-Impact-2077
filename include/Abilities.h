#pragma once
#include "Utils.h"
#include "PlayerController.h"
#include "Ball.h"
#include <random>
#include "UserInterface.h"
extern std::vector<Ball> balls;

class Ability : protected MovableSprite {
private:
	static const int D_WIDTH = 120;
	static const int D_HEIGHT = 40;
	const char* ABILITIES[6] = {
		"data\\43-Breakout-Tiles.png",   // Spawn 3 smaller balls
		"data\\44-Breakout-Tiles.png",   // Spawn 1 bigger ball
		"data\\46-Breakout-Tiles.png",   // Narrow platform
		"data\\47-Breakout-Tiles.png",   // Widen platform
		"data\\59-Breakout-Tiles.png",   // Damage player
		"data\\48-Breakout-Tiles.png"    // Spawn protective barrier
	};
	int abilityID = -1;
	Sprite* instance = nullptr;

	bool PlayerHit() {
		int tl_Xb = x;
		int tr_Xb = x + width;
		int bl_Yb = y + height;
		int tl_Yb = y;

		int tl_Xp = PlayerController::x;
		int tr_Xp = PlayerController::x + PlayerController::D_WIDTH;
		int bl_Yp = PlayerController::y + PlayerController::D_HEIGHT;
		int tl_Yp = PlayerController::y;

		if (bl_Yb < tl_Yp || tl_Yb > bl_Yp)
			return false;
		if (tl_Xb > tr_Xp || tr_Xb < tl_Xp)
			return false;
		return true;
	}

	void SpawnThreeSmallerBalls() {
		for (int i = 0; i < 3; ++i) {
			Ball b = Ball(true);
			b.Init(x, y, Ball::State::SMALL);
			balls.push_back(b);
		}
	}
	void SpawnOneBiggerBall() {
		Ball b = Ball(true);
		b.Init(x, y, Ball::State::LARGE);
		balls.push_back(b);
	}
	void NarrowPlatform() {
		PlayerController::width = PlayerController::D_WIDTH - PlayerController::DIF;
		destroySprite(PlayerController::player);
		PlayerController::player = createSprite("data\\57-Breakout-Tiles.png");
		setSpriteSize(PlayerController::player, PlayerController::width, PlayerController::height);
	}
	void WidenPlatform() {
		PlayerController::width = PlayerController::D_WIDTH + 2 * PlayerController::DIF;
		destroySprite(PlayerController::player);
		PlayerController::player = createSprite("data\\56-Breakout-Tiles.png");
		setSpriteSize(PlayerController::player, PlayerController::width, PlayerController::height);
	}
	void DamagePlayer() {
		PlayerController::hp--;
	}
	void SpawnProtectiveBarrier() {
		ProtectiveBarrier::active = true;
	}
	void (Ability::*Trigger[6])() = {
		&Ability::SpawnThreeSmallerBalls,
		&Ability::SpawnOneBiggerBall,
		&Ability::NarrowPlatform,
		&Ability::WidenPlatform,
		&Ability::DamagePlayer,
		&Ability::SpawnProtectiveBarrier
	};

public:
	Ability(int abilityID = 0) {
		this->abilityID = abilityID;
	}
	void Init() {
		MovableSprite::Init(-1000, 1000);

		x = Display::WIDTH / 2;
		y = Display::HEIGHT / 2;
		width = D_WIDTH;
		height = D_HEIGHT;

		if (abilityID == 0)
			abilityID = rand() % 6;

		if (abilityID == 4)
			width -= 50, height += 30;

		instance = createSprite(ABILITIES[abilityID]);
		setSpriteSize(instance, width, height);
	}

	bool TryMove() override {
		MovableSprite::TryMove();
		if (PlayerHit()) {
			destroySprite(instance);
			UI_Score::AddScore(0);
			(this->*Trigger[abilityID])();
			return false;
		}
		return true;
	}

	void Draw() {
		drawSprite(instance, x, y);
	}

	void Clear() {
		destroySprite(instance);
	}
};