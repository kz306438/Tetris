#include "dataManagment.h"
#include "algorithm"
#include "Variables.h"
#include "FileManager.h"
#include "consoleGUI/GUI.h"
void warningWindow()
{
	Window warningWindow(40, 8, 16, 10);
	warningWindow.show();
	StandartButton OK(16, 3, "OK", 38, 14);
	OK.connect([&]() { exit(0); });

	setcur(21, 11); std::cout << "FILE INTEGRITY CHECK FAILED.";
	setcur(21, 12); std::cout << "THE FILE MAY BE TAMPERED WITH.";

	setupInputHandling();

	while (true)
	{
		invisibleCursor();
		mouseButtonInteraction(&OK);
	}
}

void loadUserData()
{
	if (!global::fileManager.isEmpty())
	{
		bool flag = true;
		if(!global::fileManager.loadVariable("firstHighScore", global::highScores[0]))flag = false;
		if(!global::fileManager.loadVariable("secondHighScore", global::highScores[1]))flag = false;
		if(!global::fileManager.loadVariable("thirdHighScore", global::highScores[2]))flag = false;
		if(!global::fileManager.loadVariable("fourthHighScore", global::highScores[3]))flag = false;
		if(!global::fileManager.loadVariable("fifthHighScore", global::highScores[4]))flag = false;

		if (!global::fileManager.loadVariable("moveRightKey", global::moveRightKey))flag = false;
		if (!global::fileManager.loadVariable("moveLeftKey", global::moveLeftKey))flag = false;
		if(!global::fileManager.loadVariable("rotateKey", global::rotateKey))flag = false;
		if(!global::fileManager.loadVariable("softDropKey", global::softDropKey))flag = false;
		if(!global::fileManager.loadVariable("hardDropKey", global::hardDropKey))flag = false;
		if(!global::fileManager.loadVariable("holdKey", global::holdKey))flag = false;
		if(!global::fileManager.loadVariable("leftSideTexture", global::leftSideTexture))flag = false;
		if (!global::fileManager.loadVariable("rightSideTexture", global::rightSideTexture))flag = false;

		if (!flag)warningWindow();
	}
}

void saveUserData()
{
	global::fileManager.saveVariable("firstHighScore", global::highScores[0]);
	global::fileManager.saveVariable("secondHighScore", global::highScores[1]);
	global::fileManager.saveVariable("thirdHighScore", global::highScores[2]);
	global::fileManager.saveVariable("fourthHighScore", global::highScores[3]);
	global::fileManager.saveVariable("fifthHighScore", global::highScores[4]);

	global::fileManager.saveVariable("moveRightKey", global::moveRightKey);
	global::fileManager.saveVariable("moveLeftKey", global::moveLeftKey);
	global::fileManager.saveVariable("rotateKey", global::rotateKey);
	global::fileManager.saveVariable("softDropKey", global::softDropKey);
	global::fileManager.saveVariable("hardDropKey", global::hardDropKey);
	global::fileManager.saveVariable("holdKey", global::holdKey);

	global::fileManager.saveVariable("leftSideTexture", global::leftSideTexture);
	global::fileManager.saveVariable("rightSideTexture", global::rightSideTexture);

}

void updateHighScores()
{
	global::highScores.push_back(global::score);
	std::sort(global::highScores.begin(), global::highScores.end(), [](int a, int b) {
		return a > b;
		});
	global::highScores.pop_back();
}

