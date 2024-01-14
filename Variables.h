#pragma once
#include <vector>
#include "FileManager.h"
namespace global
{
	extern std::vector<std::vector<std::vector<char>>> imageFigures;
	extern std::vector<int> highScores;
	extern int score;

	extern char leftSideTexture;
	extern char rightSideTexture;

	extern bool stopMenu;
	extern bool stopGameLoop;
	extern bool stopSettings;
	extern bool stopPause;
	extern bool stopGame;
	extern bool restart;

	extern FileManager fileManager;

	extern int moveRightKey;
	extern int moveLeftKey;
	extern int rotateKey;
	extern int holdKey;
	extern int softDropKey;
	extern int hardDropKey;
	extern int holdKey;
	extern int soundVolume;
}
void updateImageFigures();