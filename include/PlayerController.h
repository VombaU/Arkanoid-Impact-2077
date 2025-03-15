#pragma once
#include "Framework.h"
#include "Utils.h"

namespace PlayerController {
	extern const int D_WIDTH;
	extern const int D_HEIGHT;
	extern const int DIF;
	extern int hp;
	extern Sprite* player;
	extern int width;
	extern int height;
	extern double x, y;

	void Init();

	void MovePlayer(int newX);

	void DrawPlayer();
}