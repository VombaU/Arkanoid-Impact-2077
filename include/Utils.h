#pragma once
#include "Framework.h"
#include <string>
 
namespace Display {
	extern const int WIDTH;
	extern const int HEIGHT;
}

namespace BrickArea {
	constexpr int ROW_COUNT = 20;
	constexpr int COLUMN_COUNT = 20;
	extern int remainingBricks;

	struct Brick {
		static const int WIDTH;
		static const int HEIGHT;
		static const int COLOR_COUNT;
		bool isRed = false;
		int colorID = 0;
		int hp = 2;
		Sprite* sprite = nullptr;

		Brick();

		Brick(int id);
	};

	extern Brick bricks[ROW_COUNT][COLUMN_COUNT];
	
	void Build();

	void Clear();

	void Draw();

	bool DealDamageToBrick(int i, int j);

	std::pair<int, int> GetBrickIntersectingPoint(int x, int y);
}

namespace ProtectiveBarrier {
	extern const int WIDTH;
	extern const int HEIGHT;
	extern const int X;
	extern const int Y;
	extern Sprite* instance;
	extern bool active;

	void Init();

	void TryDraw();
}

class MovableSprite {
protected:
	MovableSprite();

	int width, height;
	double x, y;
	double xDir, yDir;
	double f_xDir, f_yDir;

	virtual void Init(int min = 500, int max = 999);

	virtual void AdjustIfOutOfBounds();

	virtual bool TryMove();

	virtual void OffsetAngleRandomly();
};