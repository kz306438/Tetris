#include "GameData.h"
#include "algorithm"
#include "ConsoleManager.h"

namespace Tetris
{
	GameData::GameData()
	{
		topScores = { 0, 0, 0, 0, 0 };
		loadUserData();
	}

	void GameData::loadUserData()
	{
		if (!FileManager::getInstance("userData.txt").isEmpty())
		{
			bool flag = true;
			if (!FileManager::getInstance("userData.txt").loadVariable("firstHighScore", topScores[0]) ||
				!FileManager::getInstance("userData.txt").loadVariable("secondHighScore", topScores[1]) ||
				!FileManager::getInstance("userData.txt").loadVariable("thirdHighScore", topScores[2]) ||
				!FileManager::getInstance("userData.txt").loadVariable("fourthHighScore", topScores[3]) ||
				!FileManager::getInstance("userData.txt").loadVariable("fifthHighScore", topScores[4]) ||

				!FileManager::getInstance("userData.txt").loadVariable("moveRightKey", moveRightKey) ||
				!FileManager::getInstance("userData.txt").loadVariable("moveLeftKey", moveLeftKey) ||
				!FileManager::getInstance("userData.txt").loadVariable("rotateKey", rotateKey) ||
				!FileManager::getInstance("userData.txt").loadVariable("softDropKey", softDropKey) ||
				!FileManager::getInstance("userData.txt").loadVariable("hardDropKey",hardDropKey) ||
				!FileManager::getInstance("userData.txt").loadVariable("holdKey", holdKey) ||
				!FileManager::getInstance("userData.txt").loadVariable("motionDelay", motionDelay) ||

				!FileManager::getInstance("userData.txt").loadVariable("musicVolume", musicVolume) ||
				!FileManager::getInstance("userData.txt").loadVariable("soundVolume", soundVolume) || 
				!FileManager::getInstance("userData.txt").loadVariable("menuMusicType", menuMusicType) ||
				!FileManager::getInstance("userData.txt").loadVariable("gameMusicType", gameMusicType) || 
				
				!FileManager::getInstance("userData.txt").loadVariable("MaxLines", MaxLines) ||

			    !FileManager::getInstance("userData.txt").loadVariable("TotalTime", TotalTime) ||
			    !FileManager::getInstance("userData.txt").loadVariable("TotalGames", TotalGames) ||
			    !FileManager::getInstance("userData.txt").loadVariable("TotalLinesRemoved", TotalLinesRemoved) ||
			    !FileManager::getInstance("userData.txt").loadVariable("TotalFigures", TotalFigures) ||
				!FileManager::getInstance("userData.txt").loadVariable("TotalScore", TotalScore) ||

			    !FileManager::getInstance("userData.txt").loadVariable("AverageScore", AverageScore) ||
			    !FileManager::getInstance("userData.txt").loadVariable("AverageLinesRemoved", AverageLinesRemoved) ||
			    !FileManager::getInstance("userData.txt").loadVariable("AverageFigures", AverageFigures))
				flag = false;

			if (!flag)warningWindow();
		}
	}


	void GameData::saveUserData()
	{
		FileManager::getInstance("userData.txt").saveVariable("firstHighScore", topScores[0]);
		FileManager::getInstance("userData.txt").saveVariable("secondHighScore", topScores[1]);
		FileManager::getInstance("userData.txt").saveVariable("thirdHighScore", topScores[2]);
		FileManager::getInstance("userData.txt").saveVariable("fourthHighScore", topScores[3]);
		FileManager::getInstance("userData.txt").saveVariable("fifthHighScore", topScores[4]);

		FileManager::getInstance("userData.txt").saveVariable("moveRightKey", moveRightKey);
		FileManager::getInstance("userData.txt").saveVariable("moveLeftKey", moveLeftKey);
		FileManager::getInstance("userData.txt").saveVariable("rotateKey", rotateKey);
		FileManager::getInstance("userData.txt").saveVariable("softDropKey", softDropKey);
		FileManager::getInstance("userData.txt").saveVariable("hardDropKey", hardDropKey);
		FileManager::getInstance("userData.txt").saveVariable("holdKey", holdKey);
		FileManager::getInstance("userData.txt").saveVariable("motionDelay", motionDelay);

		FileManager::getInstance("userData.txt").saveVariable("musicVolume", musicVolume);
		FileManager::getInstance("userData.txt").saveVariable("soundVolume", soundVolume);
		FileManager::getInstance("userData.txt").saveVariable("menuMusicType", menuMusicType);
		FileManager::getInstance("userData.txt").saveVariable("gameMusicType", gameMusicType);

		FileManager::getInstance("userData.txt").saveVariable("MaxLines", MaxLines);

		FileManager::getInstance("userData.txt").saveVariable("TotalTime", TotalTime);
		FileManager::getInstance("userData.txt").saveVariable("TotalGames", TotalGames);
		FileManager::getInstance("userData.txt").saveVariable("TotalLinesRemoved", TotalLinesRemoved);
		FileManager::getInstance("userData.txt").saveVariable("TotalFigures", TotalFigures);
		FileManager::getInstance("userData.txt").saveVariable("TotalScore", TotalScore);

		FileManager::getInstance("userData.txt").saveVariable("AverageScore", AverageScore);
		FileManager::getInstance("userData.txt").saveVariable("AverageLinesRemoved", AverageLinesRemoved);
		FileManager::getInstance("userData.txt").saveVariable("AverageFigures", AverageFigures);
	}

	void GameData::updateTopScores(uint64_t score)
	{
		topScores.push_back(score);
		std::sort(topScores.begin(), topScores.end(), [](uint64_t a, uint64_t b) {return a > b;});
		topScores.pop_back();
	}

	GameData::~GameData()
	{
		saveUserData();
	}

	void warningWindow()
	{
		Window warningWindow(40, 8, 16, 10);
		warningWindow.show();
		PushButton OK(16, 3, "OK", 38, 14);
		OK.connect([&]() { exit(0); });

		ConsoleManager::getInstance().SetCursorPosition(21, 11);
		std::cout << "FILE INTEGRITY CHECK FAILED.";
		ConsoleManager::getInstance().SetCursorPosition(21, 12); 
		std::cout << "THE FILE MAY BE TAMPERED WITH.";

		setupInputHandling();

		while (true)
		{
			mouseButtonInteraction(&OK);
		}
	}

} // Tetris