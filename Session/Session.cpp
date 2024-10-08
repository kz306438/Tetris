#include "Session.h"

#include "../ConsoleManager.h"
#include "../Images.h"
#include "../GameData.h"
#include "../Sound/Sound.h"
#include "../Menu/GameOVerMenu.h"

namespace Tetris
{
	Session::Session(Game& game)
		: m_Game(game),
		Field(m_Height, m_Width, m_FieldPosX, m_FieldPosY)
	{
		setupButton();
	}

	bool Session::isFallen()
	{
		int posX = m_Logic->getActiveFigure()->getPosition().first - m_FieldPosX;
		int posY = m_Logic->getActiveFigure()->getPosition().second - m_FieldPosY;

		for (int i = 0; i < 4; i++)
		{
			int cellX = m_Logic->getActiveFigure()->coord[i].getPosition().first;
			int cellY = m_Logic->getActiveFigure()->coord[i].getPosition().second;

			if (posY + cellY + 1 == m_Height ||
				Field.getCell((posX + cellX) / 2,
					posY + cellY + 1).state == true)
			{
				return true;
			}
		}
		return false;
	}

	bool Session::isDead()
	{
		int posX = m_Logic->getActiveFigure()->getPosition().first - m_FieldPosX;
		int posY = m_Logic->getActiveFigure()->getPosition().second - m_FieldPosY;

		for (int i = 0; i < 4; i++)
		{
			int cellX = m_Logic->getActiveFigure()->coord[i].getPosition().first;
			int cellY = m_Logic->getActiveFigure()->coord[i].getPosition().second;

			if (Field.getCell((posX + cellX) / 2,
				posY + cellY).state == true)
				return true;

			if (posY + cellY >= m_Height ||
				(posX + cellX) / 2 >= m_Width ||
				(posX + cellX) / 2 < 0)
				return true;
		}
		return false;
	}

	void Session::renderGameWindow()
	{
		Window gameWindow(1 + m_Width * 2 + 1, 1 + m_Height + 1, m_FieldPosX - 1, m_FieldPosY - 1);
		gameWindow.setTexture(char(220), char(220), char(223), char(223),
			char(220), char(223), char(219), char(219));
		gameWindow.show();
	}

	void Session::renderNextFiguteWindow()
	{
		Window nextFigureWindow(14, 7, m_FieldPosX + m_Width * 2 + 8, 5);
		nextFigureWindow.setTexture(char(220), char(220), char(223), char(223),
			char(220), char(223), char(219), char(219));
		nextFigureWindow.addWindowName("NEXT", 5, 1);
		nextFigureWindow.show();
	}

	void Session::renderHoldFigureWindow()
	{
		Window holdFigureWindow(14, 7, 4, 5);
		holdFigureWindow.setTexture(char(220), char(220), char(223), char(223),
			char(220), char(223), char(219), char(219));
		holdFigureWindow.addWindowName("HOLD", 5, 1);
		holdFigureWindow.show();
	}

	void Session::renderDataWindow()
	{
		Window dataWindow(14, 13, 4, 14);
		dataWindow.setTexture(char(220), char(220), char(223), char(223),
			char(220), char(223), char(219), char(219));
		dataWindow.show();
	}

	void Session::setupButton()
	{
		std::vector<std::vector<char>> pauseImagePressed = Tile::PressedPauseImage.getMatrix();

		std::vector<std::vector<char>> pauseImageDefault = Tile::DefaultPauseImage.getMatrix();

		m_CBPause = std::make_unique<CustomButton>(pauseImageDefault,
			pauseImagePressed,
			m_FieldPosX + m_Width * 2 + 10, 22);
		m_CBPause->connect([&]() { m_Select = 0; });
	}

	void Session::clear()
	{
		m_Logic->clear();
		Field.clear();

		if (Sounds::MusicCurrentlyPlaying)
			Sounds::MusicCurrentlyPlaying->stop();

		GameData::getInstance().score = data.getScore();
		GameData::getInstance().updateTopScores(data.getScore());

		if (GameData::getInstance().score == GameData::getInstance().topScores[0])
			Sounds::WinSound.play();
		else
			Sounds::GameOverSound.play();

		m_Game.SetMenu<GameOverMenu>();

		GameData::getInstance().TotalGames++;
		GameData::getInstance().TotalScore += GameData::getInstance().score;

		if (GameData::getInstance().MaxLines < data.getLines())
			GameData::getInstance().MaxLines = data.getLines();

		GameData::getInstance().AverageFigures =
			static_cast<float>(GameData::getInstance().TotalFigures / GameData::getInstance().TotalGames);

		GameData::getInstance().AverageLinesRemoved =
			static_cast<float>(GameData::getInstance().TotalLinesRemoved / GameData::getInstance().TotalGames);

		GameData::getInstance().AverageScore =
			static_cast<float>(GameData::getInstance().TotalScore / GameData::getInstance().TotalGames);
	}


	void Session::setupGame()
	{
		if (Sounds::MusicCurrentlyPlaying)
			Sounds::MusicCurrentlyPlaying->stop();
		Sounds::GameThemes[GameData::getInstance().gameMusicType]->play();
		Sounds::GameThemes[GameData::getInstance().gameMusicType]->setLoop(true);

		m_Logic->GetFigureOutOfBag();

		data.resetData();

		render();
	}

} // Tetris