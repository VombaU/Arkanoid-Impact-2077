#pragma once
#include "Utils.h"
#include "PlayerController.h"
#include "Ball.h"
#include "UserInterface.h"
#include <random>
extern std::vector<Ball> balls;

class Ability : protected MovableSprite {
private:
	static const int D_WIDTH;
	static const int D_HEIGHT;
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

	bool PlayerHit();

	void SpawnThreeSmallerBalls();

	void SpawnOneBiggerBall();

	void NarrowPlatform();

	void WidenPlatform();

	void DamagePlayer();

	void SpawnProtectiveBarrier();

	void (Ability::*Trigger[6])() = {
		&Ability::SpawnThreeSmallerBalls,
		&Ability::SpawnOneBiggerBall,
		&Ability::NarrowPlatform,
		&Ability::WidenPlatform,
		&Ability::DamagePlayer,
		&Ability::SpawnProtectiveBarrier
	};

public:
	Ability(int abilityID = 0);

	void Init();

	bool TryMove() override;

	void Draw();

	void Clear();
};