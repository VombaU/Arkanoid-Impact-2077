#pragma once
#include "Framework.h"
#include "UserInterface.h"
#include "Utils.h"
#include <vector>
#include <algorithm>
#include <cmath>
class Ball : protected MovableSprite {
private:
	static const int D_WIDTH;
	static const int D_HEIGHT;
	static const int DIF;

	double mod_xDir = 0, mod_yDir = 0;
	Sprite* instance = nullptr;
	bool detached = false;

	void Transform(Sprite** instance, int state);

	void ApplyCurrentZoneEffects();

	bool IsGameOver();

	void BounceAndDamageBrickIfHit();

	void BounceIfPlayerHit();

	void BounceIfProtectiveBarrierHit();

	void BounceIfWallHit();

public:
	enum State {
		SMALL,
		NORMAL,
		LARGE
	};

	Ball(bool detached = false);

	void Init(int x = 0, int y = 0, State state = NORMAL);

	void Draw();

	bool TryMove() override;

	void Clear();

	void Detach();
};