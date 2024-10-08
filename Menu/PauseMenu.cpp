#include "PauseMenu.h"
#include "../Application.h"
#include "MainMenu.h"
#include "../Sound/Sound.h"
#include "../GameData.h"
#include "PauseOptionsMenu.h"
#include "GameOverMenu.h"

namespace Tetris
{

	PauseMenu::PauseMenu(Game& game)
		:m_Game(game)
	{
		setupButtons();
	}

	void PauseMenu::render()
	{
		Window pauseWindow(42, 27, 15, 2);
		pauseWindow.addWindowName("PAUSE", 17, 0);
		pauseWindow.show();

		m_PBResume->allowChanges();  m_PBResume->show();
		m_PBOptions->allowChanges(); m_PBOptions->show();
		m_PBQuit->allowChanges();    m_PBQuit->show();
	}

	void PauseMenu::update(float ts)
	{
		if (Application::pastTime.elapsedMiliseconds() > ts)
		{
			mouseButtonInteraction(m_PBResume.get(), m_PBOptions.get(), m_PBQuit.get());
			Application::pastTime.reset();
		}

		if (m_Select == 0)
		{
			m_Game.SetMenu<std::nullptr_t>();
			m_Game.isChange = true;
			Sounds::GameThemes[GameData::getInstance().gameMusicType]->play();
			Sounds::GameThemes[GameData::getInstance().gameMusicType]->setLoop(true);
		}

		if (m_Select == 1)
		{
			m_Game.SetMenu<PauseOptionsMenu>();
		}

		if (m_Select == 2)
		{
			m_Game.finishGame();
			m_Game.SetMenu<GameOverMenu>();
		}
	}

	void PauseMenu::setupButtons()
	{
		m_PBResume = std::make_unique<PushButton>(20, 5, "RESUME", 26, 7);
		m_PBOptions = std::make_unique<PushButton>(20, 5, "OPTIONS", 26, 13);
		m_PBQuit = std::make_unique<PushButton>(20, 5, "QUIT", 26, 19);

		m_PBResume->connect([&]() { m_Select = 0; });
		m_PBOptions->connect([&]() { m_Select = 1; });
		m_PBQuit->connect([&]() { m_Select = 2; });
	}


} // Tetris