#include "Abilities.h"

const int Ability::D_WIDTH = 120;
const int Ability::D_HEIGHT = 40;

bool Ability::PlayerHit() {
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

void Ability::SpawnThreeSmallerBalls() {
	for (int i = 0; i < 3; ++i) {
		Ball b = Ball(true);
		b.Init(x, y, Ball::State::SMALL);
		balls.push_back(b);
	}
}

void Ability::SpawnOneBiggerBall() {
	Ball b = Ball(true);
	b.Init(x, y, Ball::State::LARGE);
	balls.push_back(b);
}

void Ability::NarrowPlatform() {
	PlayerController::width = PlayerController::D_WIDTH - PlayerController::DIF;
	destroySprite(PlayerController::player);
	PlayerController::player = createSprite("data\\57-Breakout-Tiles.png");
	setSpriteSize(PlayerController::player, PlayerController::width, PlayerController::height);
}

void Ability::WidenPlatform() {
	PlayerController::width = PlayerController::D_WIDTH + 2 * PlayerController::DIF;
	destroySprite(PlayerController::player);
	PlayerController::player = createSprite("data\\56-Breakout-Tiles.png");
	setSpriteSize(PlayerController::player, PlayerController::width, PlayerController::height);
}

void Ability::DamagePlayer() {
	PlayerController::hp--;
}

void Ability::SpawnProtectiveBarrier() {
	ProtectiveBarrier::active = true;
}

Ability::Ability(int abilityID) {
		this->abilityID = abilityID;
	}

void Ability::Init() {
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

bool Ability::TryMove() {
	MovableSprite::TryMove();
	if (PlayerHit()) {
		destroySprite(instance);
		UI_Score::AddScore(0);
		(this->*Trigger[abilityID])();
		return false;
	}
	return true;
}

void Ability::Draw() {
	drawSprite(instance, x, y);
}

void Ability::Clear() {
	destroySprite(instance);
}