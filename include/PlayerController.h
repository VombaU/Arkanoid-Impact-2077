#pragma once
#include "Framework.h"
#include "Utils.h"
namespace PlayerController {
	const int D_WIDTH = 140;
	const int D_HEIGHT = 30;
	const int DIF = 70;
	int hp = 3;
	Sprite* player;
	int width = D_WIDTH;
	int height = D_HEIGHT;
	double x = Display::WIDTH / 2, y = 3 * (Display::HEIGHT / 4);

	void Init() {
		player = createSprite("data\\52-Breakout-Tiles.png");
		setSpriteSize(player, D_WIDTH, D_HEIGHT);
	}

	void MovePlayer(int newX) {
		x = newX;
	}

	void DrawPlayer() {
		drawSprite(player, x, y);
	}
}