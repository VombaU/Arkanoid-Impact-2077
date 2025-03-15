#include "Game.h"

std::vector<Ball> balls{ Ball() };
std::vector<Ability> abilities;

void Game::PreInit(int& width, int& height, bool& fullscreen) {
	width = Display::WIDTH;
	height = Display::HEIGHT;
	fullscreen = true;
}

bool Game::Init() {
	showCursor(false);

	BrickArea::Build();
	PlayerController::Init();
	UI_HitPoints::Init();
	UI_Score::Init();
	ProtectiveBarrier::Init();
	for (auto& b : balls)
		b.Init();

	return true;
}

void Game::Close() {
	destroySprite(PlayerController::player);
	destroySprite(UI_HitPoints::HEART_SPRITE);
	destroySprite(ProtectiveBarrier::instance);
	for (auto& b : balls) b.Clear();
	for (auto& a : abilities) a.Clear();
	BrickArea::Clear();
	UI_Score::Clear();

	if (BrickArea::remainingBricks == 0)
		std::cout << "\n-------------------Big pro-------------------\n";
	else
		std::cout << "\n-------------------SOOOOOOO BAD-------------------\n";
	std::cout << "-------------------FINAL SCORE: " << UI_Score::score << "-------------------\n";
}

bool Game::Tick() {
	if (BrickArea::remainingBricks == 0)
		return true;
	if (*UI_HitPoints::COUNT == 0)
		return true;

	// If a ball is unable to move, i.e. it falls to the bottom, it is removed
	for (int i = 0; i < balls.size(); ++i)
		if (balls[i].TryMove() == false)
			balls.erase(balls.begin() + i--);

	// If a player hits an ability, its effect is activated and its sprite is removed
	for (int i = 0; i < abilities.size(); ++i)
		if (abilities[i].TryMove() == false)
			abilities.erase(abilities.begin() + i--);

	// If there aren't any balls left, the game ends
	if (balls.empty())
		return true;

	// Triggers ability every 20s
	if (gameStarted && getTickCount() % (4 * 1000) == 0) {
		abilities.push_back(Ability());
		abilities.back().Init();
		// Extra balls
		abilities.push_back(Ability(rand() % 2));
		abilities.back().Init();
	}

	// Draws every sprite component
	ProtectiveBarrier::TryDraw();
	BrickArea::Draw();
	PlayerController::DrawPlayer();
	for (auto& b : balls) b.Draw();
	for (auto& a : abilities) a.Draw();
	UI_HitPoints::DrawInterface();
	UI_Score::DrawInterface();

	return false;
}

void Game::onMouseMove(int x, int y, int xrelative, int yrelative) {
	PlayerController::MovePlayer(x + xrelative);
}

void Game::onMouseButtonClick(FRMouseButton button, bool isReleased) {
	if (button == FRMouseButton::LEFT && !isReleased) {
		gameStarted = true;
		for (auto& b : balls)
			b.Detach();
	}
}

void Game::onKeyPressed(FRKey k) {

}

void Game::onKeyReleased(FRKey k) {

}

const char* Game::GetTitle() {
	return "Arkanoid Impact 2077";
}
