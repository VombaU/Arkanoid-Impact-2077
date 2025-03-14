#pragma once
#include "Framework.h"
namespace Display {
	const int WIDTH = 1920;
	const int HEIGHT = 1080;
}

namespace BrickArea {
	const int ROW_COUNT = 20;
	const int COLUMN_COUNT = 20;
	int remainingBricks = ROW_COUNT * COLUMN_COUNT;

	struct Brick {
		static const int WIDTH = Display::WIDTH / BrickArea::COLUMN_COUNT;
		static const int HEIGHT = (Display::HEIGHT / 2) / BrickArea::ROW_COUNT;
		static const int COLOR_COUNT = 9;
		bool isRed = false;
		int colorID = 0;
		int hp = 2;
		Sprite* sprite = nullptr;

		Brick() {}

		Brick(int id) {
			std::string path = "data\\" + (id < 10 ? "0" + std::to_string(id) : std::to_string(id)) + "-Breakout-Tiles.png";
			hp = (id % 2 == 0 ? 1 : 2);

			colorID = id;
			sprite = createSprite(path.c_str());
			setSpriteSize(sprite, WIDTH, HEIGHT);
		}
	};

	Brick bricks[ROW_COUNT][COLUMN_COUNT];
	
	void Build() {
		int colorID = rand() % Brick::COLOR_COUNT;
		int target = rand() % COLUMN_COUNT;
		
		for (auto& row : bricks) {
			int f_target = target;

			for (auto& brick : row) {
				if (target == 0) {
					brick = Brick(2 * Brick::COLOR_COUNT + 1);
					brick.isRed = true;
					target = INT_MAX;
				}
				else {
					brick = Brick(2 * colorID + 1);
					--target;
				}
			}
			
			target = rand() % COLUMN_COUNT;
			if (abs(f_target - target) <= 2)
				target = (target + 5) % COLUMN_COUNT;

			colorID = (colorID + 1) % Brick::COLOR_COUNT;
		}
	}

	void Clear() {
		for (int i = 0; i < ROW_COUNT; ++i)
			for (int j = 0; j < COLUMN_COUNT; ++j)
				destroySprite(bricks[i][j].sprite);
	}

	void Draw() {
		for (int i = 0; i < ROW_COUNT; ++i)
			for (int j = 0; j < COLUMN_COUNT; ++j)
				if (bricks[i][j].colorID != 0)
					drawSprite(bricks[i][j].sprite, j * Brick::WIDTH, i * Brick::HEIGHT);
	}

	bool DealDamageToBrick(int i, int j) {
		if (bricks[i][j].hp == 0 || (bricks[i][j].isRed && remainingBricks > ROW_COUNT))
			return false;
		--bricks[i][j].hp;

		if (bricks[i][j].hp == 0) {
			--remainingBricks;
			bricks[i][j].colorID = 0;
		}
		else
			bricks[i][j] = Brick(bricks[i][j].colorID + 1);

		return true;
	}

	std::pair<int, int> GetBrickIntersectingPoint(int x, int y) {
		int i = y / Brick::HEIGHT;
		int j = x / Brick::WIDTH;

		if (i < ROW_COUNT && j < COLUMN_COUNT && bricks[i][j].hp > 0)
			return { i, j };
		return { -1, -1 };
	}
}

namespace ProtectiveBarrier {
	const int WIDTH = Display::WIDTH;
	const int HEIGHT = Display::HEIGHT / 4;
	const int X = 0;
	const int Y = Display::HEIGHT / 5 * 4;
	Sprite* instance;
	bool active = false;

	void Init() {
		instance = createSprite("data\\19-Breakout-Tiles.png");
		setSpriteSize(instance, WIDTH, HEIGHT);
	}

	void TryDraw() {
		if (active)
			drawSprite(instance, X, Y);
	}
}

class MovableSprite {
protected:
	MovableSprite() {}

	int width, height;
	double x, y;
	double xDir, yDir;
	double f_xDir, f_yDir;

	virtual void Init(int min = 500, int max = 999) {
		x = y = 0;
		xDir = (-2 * min + rand() % (max - (-2 * min) + 1)) / 1000.;
		yDir = (min + rand() % (max - min + 1)) / 1000.;
		while (abs(xDir) < .3)
			xDir *= 2;
		while (abs(xDir) > .6)
			xDir /= 2;
		while (abs(yDir) < .3)
			yDir *= 2;
		while (abs(yDir) > .6)
			yDir /= 2;
	}
	virtual void AdjustIfOutOfBounds() {
		if (x < 0 || x + width > Display::WIDTH)
			xDir = -xDir;
		else if (y < 0 || y + height > Display::HEIGHT)
			yDir = -yDir;
	}
	virtual bool TryMove() {
		f_xDir = xDir;
		f_yDir = yDir;
		AdjustIfOutOfBounds();
		OffsetAngleRandomly();
		x += xDir;
		y += yDir;
		return true;
	}
	virtual void OffsetAngleRandomly() {
		if (xDir != f_xDir)
			yDir += (yDir < 0 ? -1 : 1) * rand() % 150 / 1000.;
		else if (yDir != f_yDir)
			xDir += (xDir < 0 ? -1 : 1) * rand() % 150 / 1000.;
	}
};