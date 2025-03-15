#pragma once
#include <iostream>
#include <cstring>
#include <time.h>
#include <string>
#include <vector>
#include "Framework.h"
#include "Utils.h"
#include "PlayerController.h"
#include "Ball.h"
#include "Abilities.h"
#include "UserInterface.h"

extern std::vector<Ball> balls;
extern std::vector<Ability> abilities;

class Game : public Framework {
private:
	bool gameStarted = false;

public:
	void PreInit(int& width, int& height, bool& fullscreen) override;

	bool Init() override;

	void Close() override;

	bool Tick() override;

	void onMouseMove(int x, int y, int xrelative, int yrelative) override;

	void onMouseButtonClick(FRMouseButton button, bool isReleased) override;

	void onKeyPressed(FRKey k) override;

	void onKeyReleased(FRKey k) override;

	const char* GetTitle() override;
};