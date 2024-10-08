#include "StatsMenu.h"
#include "../Application.h"
#include "../Sound/Sound.h"

namespace Tetris
{

	StatsMenu::StatsMenu(Game& game)
		: m_Game(game)
	{
		m_PBBack = std::make_unique<PushButton>(20, 5, "BACK", 47, 22);
		setupButtons();
	}

	void StatsMenu::update(float ts)
	{
		if (Application::pastTime.elapsedMiliseconds() < ts)
			return;

		mouseButtonInteraction(m_PBBack.get());

		if (m_Select == 0)
		{
			Sounds::MusicCurrentlyPlaying->stop();
			Sounds::MenuThemes[GameData::getInstance().menuMusicType]->play();
			Sounds::MenuThemes[GameData::getInstance().menuMusicType]->setLoop(true);
			m_Game.SetMenu<MainMenu>();
		}
	}

	void StatsMenu::render()
	{
		ConsoleManager::getInstance().ClearScreen();

		renderTopScores();
		renderMaxLines();
		renderAllTimeData();
		renderAverageData();

		m_PBBack->allowChanges(); m_PBBack->show();
	}

	void StatsMenu::setupButtons()
	{
		m_PBBack->connect
		(
			[&]() { m_Select = 0; }
		);
	}

	void StatsMenu::renderAllTimeData()
	{
		Window allTime(40, 8, 27, 6);
		allTime.addWindowName("ALL-TIME", 14, 0);
		allTime.show();
		
		ConsoleManager::getInstance().SetCursorPosition(30, 8); std::cout << "Hours in game";
		ConsoleManager::getInstance().SetCursorPosition(52, 8); std::cout << GameData::getInstance().TotalTime;
		ConsoleManager::getInstance().SetCursorPosition(30, 9); std::cout << "Total games";
		ConsoleManager::getInstance().SetCursorPosition(52, 9);  std::cout << GameData::getInstance().TotalGames;
		ConsoleManager::getInstance().SetCursorPosition(30, 10); std::cout << "Total Lines Removed";
		ConsoleManager::getInstance().SetCursorPosition(52, 10); std::cout << GameData::getInstance().TotalLinesRemoved;
		ConsoleManager::getInstance().SetCursorPosition(30, 11); std::cout << "Total used figure";
		ConsoleManager::getInstance().SetCursorPosition(52, 11); std::cout << GameData::getInstance().TotalFigures;
	}

	void StatsMenu::renderAverageData()
	{
		Window average(40, 7, 27, 14);
		average.addWindowName("AVERAGE", 14, 0);
		average.show();

		ConsoleManager::getInstance().SetCursorPosition(30, 16); std::cout << "Average score";
		ConsoleManager::getInstance().SetCursorPosition(52, 16); std::cout << GameData::getInstance().AverageScore;
		ConsoleManager::getInstance().SetCursorPosition(30, 17); std::cout << "Average lines Removed";
		ConsoleManager::getInstance().SetCursorPosition(52, 17); std::cout << GameData::getInstance().AverageLinesRemoved;
		ConsoleManager::getInstance().SetCursorPosition(30, 18); std::cout << "Average fiugres";
		ConsoleManager::getInstance().SetCursorPosition(52, 18); std::cout << GameData::getInstance().AverageFigures;
	}

	void StatsMenu::renderMaxLines()
	{
		Window maxLines(20, 3, 7, 18);
		maxLines.addWindowName("MAX LINES", 3, 0);
		maxLines.show();

		std::string s = std::to_string(GameData::getInstance().MaxLines);
		ConsoleManager::getInstance().SetCursorPosition(10 - s.size() / 2 + 7, 19);
		std::cout << GameData::getInstance().MaxLines;
	}

	void StatsMenu::renderTopScores()
	{
		Window highScoresWindow(20, 12, 7, 6);
		highScoresWindow.addWindowName("HIGH SCORES", 3, 0);
		highScoresWindow.show();

		for (int i = 0; i < 5; ++i) {
			std::string s = std::to_string(GameData::getInstance().topScores[i]);
			ConsoleManager::getInstance().SetCursorPosition(10 - s.size() / 2 + 7, 8 + i * 2);
			std::cout << GameData::getInstance().topScores[i];
		}
	}

} // Tetris