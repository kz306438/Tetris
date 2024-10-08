#include "MainMenu.h"
#include "../Sound/Sound.h"
#include "../Session/SingleSession.h"
#include "../Session/AISession.h"
#include "StatsMenu.h"


namespace Tetris
{

	MainMenu::MainMenu(Game& game)
		: m_Game(game)
	{
		createButtons();
		connectButtons();
	}

	void MainMenu::update(float ts)
	{
		if (Application::pastTime.elapsedSeconds() > ts)
		{
			mouseButtonInteraction(m_PBSoloMode.get(), m_PBAIMode.get(), m_PBStats.get(),
				m_PBOptions.get(), m_PBQuit.get());
			Application::pastTime.reset();
		}

		if (m_Select == 0)
		{
			m_Game.SetSession<SingleSession>();
			m_Game.run(); 
		}

		if (m_Select == 1)
		{
			m_Game.SetSession<AISession>();
			m_Game.run();
		}

		if (m_Select == 2)
		{
			Sounds::MusicCurrentlyPlaying->stop();
			Sounds::StatsTheme.setLoop(true);
			Sounds::StatsTheme.play();
			m_Game.SetMenu<StatsMenu>();
		}

		if (m_Select == 3)
		{
			ConsoleManager::getInstance().ClearScreen();
			m_Game.SetMenu<OptionsMenu>();
		} 

		if (m_Select == 4)
		{
			if (dialogWindow("QUIT GAME?"))
			{
				GameData::getInstance().TotalTime += Application::TimeInGame.elapsedHour();
				GameData::getInstance().saveUserData();
				exit(0);
			}
			else
			{
				m_Game.isChange = true;
			}
		}

		m_Select = -1;
	}

	void MainMenu::render()
	{
		ConsoleManager::getInstance().ClearScreen();

		TetrisTitleRender::get().render(22, 0);


		m_PBSoloMode->allowChanges();    m_PBSoloMode->show();
		m_PBAIMode->allowChanges();      m_PBAIMode->show();
		m_PBStats->allowChanges();       m_PBStats->show();
		m_PBOptions->allowChanges();     m_PBOptions->show();
		m_PBQuit->allowChanges();        m_PBQuit->show();
	}

	void MainMenu::connectButtons()
	{
		m_PBSoloMode->connect([&]()
			{
				m_Select = 0;
			});
		m_PBAIMode->connect([&]()
			{
				m_Select = 1;
			});
		m_PBStats->connect([&]()
			{
				m_Select = 2;
			});
		m_PBOptions->connect([&]()
			{
				m_Select = 3;
			});
		m_PBQuit->connect([&]()
			{
				m_Select = 4;
			});
	}

	void MainMenu::createButtons()
	{
		m_PBSoloMode = std::make_unique<PushButton>(20, 5, "SOLO MODE", 26, 6);
		m_PBAIMode   = std::make_unique<PushButton>(20, 5, "AI MODE", 26, 11);
		m_PBStats    = std::make_unique<PushButton>(20, 5, "STATS", 26, 16);
		m_PBOptions  = std::make_unique<PushButton>(10, 5, "OPTIONS", 26, 21);
		m_PBQuit     = std::make_unique<PushButton>(10, 5, "QUIT", 37, 21);
	}


	bool dialogWindow(const std::string& head)
	{
		bool returnValue = true;
		bool stopDialogWindow = false;
		Window dialogWindow(40, 8, 16, 10);
		dialogWindow.show();

		PushButton OK(16, 3, "OK", 19, 14);
		PushButton cancel(16, 3, "CANCEL", 37, 14);
		OK.connect([&]()
			{
				stopDialogWindow = true;
				returnValue = true;
			});
		cancel.connect([&]()
			{
				stopDialogWindow = true;
				returnValue = false;
			});
		setcur(36 - head.size() / 2, 11);
		std::cout << head;

		while (!stopDialogWindow)
		{
			mouseButtonInteraction(&OK, &cancel);
		}
		return returnValue;
	}

}
