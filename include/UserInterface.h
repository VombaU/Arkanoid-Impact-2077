#pragma once
#include "PlayerController.h"
#include "Framework.h"
#include <vector>

namespace UI_HitPoints {
    extern const int* COUNT;
    extern const int HEART_WIDTH;
    extern const int HEART_HEIGHT;
    extern Sprite* HEART_SPRITE;
    extern const int X_START;
    extern const int Y_START;

    void Init();
    void DrawInterface();
}

namespace UI_Score {
    extern std::vector<std::pair<int, int>> scores;
    extern int score;
    extern const int WIDTH;
    extern const int HEIGHT;
    extern const int X_START;
    extern const int Y_START;
    extern const char* BOARDS[4];
    extern const int POINTS[4];
    extern Sprite* displays[4];

    void AddScore(int iScore);
    void Init();
    void DrawInterface();
    void Clear();
}