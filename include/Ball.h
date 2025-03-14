#pragma once
#include "Framework.h"
#include "UserInterface.h"
#include <cmath>
#include "Utils.h"
#include <vector>
#include <algorithm>
#include <cmath>
class Ball : protected MovableSprite {
private:
	static const int D_WIDTH = 40;
	static const int D_HEIGHT = 40;
	static const int DIF = 20;

	double mod_xDir = 0, mod_yDir = 0;
	Sprite* instance = nullptr;
	bool detached = false;

	void Transform(Sprite** instance, int state) {
		if (*instance != nullptr)
			destroySprite(*instance);

		width = D_WIDTH; height = D_HEIGHT;

		switch (state) {
		case SMALL:
			width -= DIF, height -= DIF;
			*instance = createSprite("data\\63-Breakout-Tiles.png");
			break;
		case NORMAL:
			*instance = createSprite("data\\62-Breakout-Tiles.png");
			break;
		case LARGE:
			width += DIF, height += DIF;
			*instance = createSprite("data\\58-Breakout-Tiles.png");
		}
		setSpriteSize(*instance, width, height);
	}

	void ApplyCurrentZoneEffects() {
		int zoneID = (int)y / (Display::HEIGHT / 3);
		if (zoneID % 2 == 0) {
			mod_xDir = 1.5 * xDir;
			mod_yDir = 1.5 * yDir;
		}
		else {
			mod_xDir = 0.5 * xDir;
			mod_yDir = 0.5 * yDir;
		}
	}

	bool IsGameOver() {
		return y > Display::HEIGHT;
	}

	void BounceAndDamageBrickIfHit() {
		std::vector<std::pair<int, int>> hitBricks;
		bool reverseXDir = true;
		bool reverseYDir = true;

		for (double yi = 0; yi <= 1.; yi += .5)
			for (double xi = 0; xi <= 1.; xi += .5) {
				std::pair<int, int> b = BrickArea::GetBrickIntersectingPoint(x + xi * width, y + yi * height);
				int key = b.first * 100 + b.second;
				if (b.first != -1 && std::find_if(hitBricks.begin(), hitBricks.end(), [&](std::pair<int, int>& a) { return a.first * 100 + a.second == key; }) == hitBricks.end()) {
					hitBricks.push_back(b);
					if (BrickArea::GetBrickIntersectingPoint(x + xi * width - mod_xDir, y + yi * height).first != -1)
						reverseXDir = false;
					if (BrickArea::GetBrickIntersectingPoint(x + xi * width, y + yi * height - mod_yDir).first != -1)
						reverseYDir = false;
				}
			}
		if (hitBricks.empty())
			return;

		if (reverseXDir)
			xDir = -xDir;
		if (reverseYDir)
			yDir = -yDir;

		int hitCnt = 0;
		for (auto& brick : hitBricks)
			if (BrickArea::DealDamageToBrick(brick.first, brick.second) == true)
				hitCnt++;

		if (hitCnt >= 1)
			UI_Score::AddScore(hitCnt);
	}

	void BounceIfPlayerHit() {
		int tl_Xb = x;
		int tr_Xb = x + width;
		int bl_Yb = y + height;
		int tl_Yb = y;

		int tl_Xp = PlayerController::x;
		int tr_Xp = PlayerController::x + PlayerController::width;
		int bl_Yp = PlayerController::y + PlayerController::height;
		int tl_Yp = PlayerController::y;

		if (bl_Yb < tl_Yp || tl_Yb > bl_Yp)
			return;
		if (tl_Xb > tr_Xp || tr_Xb < tl_Xp)
			return;

		if (bl_Yb - mod_yDir < tl_Yp || tl_Yb - mod_yDir > bl_Yp)
			yDir = -yDir;
		if (tr_Xb - mod_xDir < tl_Xp || tl_Xb - mod_xDir > tr_Xp)
			xDir = -xDir;
	}

	void BounceIfProtectiveBarrierHit() {
		if (ProtectiveBarrier::active)
			if (y + height >= ProtectiveBarrier::Y) {
				ProtectiveBarrier::active = false;
				yDir = -yDir;
			}
	}
	
	void BounceIfWallHit() {
		if (x < 0 || x + width > Display::WIDTH)
			xDir = -xDir;
		else if (y < 0)
			yDir = -yDir;
	}

public:
	enum State {
		SMALL,
		NORMAL,
		LARGE
	};

	Ball(bool detached = false) {
		this->detached = detached;
	}

	void Init(int x = 0, int y = 0, State state = NORMAL) {
		MovableSprite::Init();
		this->x = x;
		this->y = y;
		yDir = -yDir;
		Transform(&instance, state);
	}

	void Draw() {
		drawSprite(instance, x, y);
	}

	bool TryMove() override {
		if (!detached) {
			x = PlayerController::x - width / 2 + PlayerController::D_WIDTH / 2;
			y = PlayerController::y - height;
			return true;
		}
		if (IsGameOver())
			return false;

		f_xDir = xDir;
		f_yDir = yDir;

		BounceIfPlayerHit();
		BounceIfWallHit();
		BounceIfProtectiveBarrierHit();
		BounceAndDamageBrickIfHit();
		ApplyCurrentZoneEffects();
		OffsetAngleRandomly();

		x += mod_xDir;
		y += mod_yDir;

		return true;
	}

	void Clear() {
		destroySprite(instance);
	}

	void Detach() {
		detached = true;
	}
};
//double nx = -0 / sqrt(1920 * 1920);
//double ny = 1 / sqrt(1 * 1);

//xDir += 0;
//yDir += -2 * (yDir * ny) * ny;