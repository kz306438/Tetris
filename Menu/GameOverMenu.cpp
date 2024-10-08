#include "GameOverMenu.h"
#include "../ConsoleManager.h"
#include "../Images.h"
#include "MainMenu.h"
#include "../Sound/Sound.h"

namespace Tetris
{

	GameOverMenu::GameOverMenu(Game& game)
		: m_Game(game),
		m_PBHome(std::make_unique<PushButton>(18, 5, "HOME", 16, 20)),
		m_PBRestart(std::make_unique<PushButton>(18, 5, "RESTART", 37, 20))
	{
		setupButtons();
	}

	void GameOverMenu::render()
	{
		ConsoleManager::getInstance().ClearScreen();

		Tile::TitleGameOver.render(16, 5);

		ConsoleManager::getInstance().SetCursorPosition(16, 14);
		std::cout << "YOUR SCORE " << GameData::getInstance().score;
		ConsoleManager::getInstance().SetCursorPosition(16, 17); 
		std::cout << "HIGH SCORE " << GameData::getInstance().topScores[0];

		m_PBHome->allowChanges();    m_PBHome->show();
		m_PBRestart->allowChanges(); m_PBRestart->show();
	}

	void GameOverMenu::update(float ts)
	{
		if (Application::pastTime.elapsedSeconds() > ts)
		{
			mouseButtonInteraction(m_PBHome.get(), m_PBRestart.get());
			Application::pastTime.reset();
		}

		if (m_Select == 0)
		{
			//ConsoleManager::getInstance().ClearScreen();
			Sounds::MenuThemes[GameData::getInstance().menuMusicType]->play();
			Sounds::MenuThemes[GameData::getInstance().menuMusicType]->setLoop(true);
			m_Game.SetMenu<MainMenu>();
		}

		if (m_Select == 1)
		{
			m_Game.finishGame();
			m_Game.run();
		}
	}

	void GameOverMenu::setupButtons()
	{
		m_PBHome->connect([&]() { m_Select = 0; });
		m_PBRestart->connect([&]() { m_Select = 1; });
	}

} // Tetris