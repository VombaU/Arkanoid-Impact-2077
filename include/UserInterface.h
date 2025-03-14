#pragma once
#include "PlayerController.h"
#include <vector>
extern long long score;
namespace UI_HitPoints {
	const int* COUNT = &PlayerController::hp;

	const int HEART_WIDTH = 80;
	const int HEART_HEIGHT = 80;
	Sprite* HEART_SPRITE;

	const int X_START = 10;
	const int Y_START = Display::HEIGHT - HEART_HEIGHT - 10;

	void Init() {
		HEART_SPRITE = createSprite("data\\60-Breakout-Tiles.png");
		setSpriteSize(HEART_SPRITE, HEART_WIDTH, HEART_HEIGHT);
	}

	void DrawInterface() {
		for (int i = 0; i < *COUNT; ++i)
			drawSprite(HEART_SPRITE, X_START + HEART_WIDTH * i, Y_START);
	}
}
namespace UI_Score {
	std::vector<std::pair<int, int>> scores;
	const int WIDTH = 150;
	const int HEIGHT = 50;
	const int X_START = Display::WIDTH - WIDTH;
	const int Y_START = Display::HEIGHT - HEIGHT;
	const char* BOARDS[4] = {
		"data\\38-Breakout-Tiles.png", // Ability gain
		"data\\31-Breakout-Tiles.png", // 1 Hit Brick
		"data\\39-Breakout-Tiles.png", // 2 Hit Bricks
		"data\\40-Breakout-Tiles.png"  // 3 Hit Bricks or more
	};
	const int POINTS[4] = { 100, 50, 250, 500 };
	Sprite* displays[4];

	void AddScore(int iScore) {
		score += POINTS[std::min(iScore, 3)];
		scores.push_back({ iScore, 0 });
	}
	
	void Init() {
		for (int i = 0; i < 4; ++i) {
			displays[i] = createSprite(BOARDS[i]);
			setSpriteSize(displays[i], WIDTH, HEIGHT);
		}
	}

	void DrawInterface() {
		for (int i = 0; i < scores.size(); ++i) {
			if (scores[i].second > 1000)
				scores.erase(scores.begin() + i--);
			else {
				int iSprite = scores[i].first;
				scores[i].second++;
				drawSprite(displays[iSprite], X_START, Y_START - HEIGHT * i);
			}
		}
			
	}

	void Clear() {
		for (int i = 0; i < 4; ++i)
			destroySprite(displays[i]);
	}
}