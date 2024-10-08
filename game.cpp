#include "Game.h"
#include "Sound/Sound.h"

namespace Tetris
{
	Game::Game()
	{
		SetMenu<SplashScreen>();
		SetSession<SingleSession>();
	}

	void Game::run()
	{
        m_Session->Play = true;
		m_Session->setupGame();

		m_Menu = nullptr;
	}

	void Game::finishGame()
	{
     	m_Session->Play = false;
		m_Session->clear();
	}

	void Game::update(float ts)
	{
		if (m_Menu)
			m_Menu->update(ts);

		if (m_Session->Play && !m_Menu)
			m_Session->update();
	}

	void Game::render()
	{
		if (m_Menu && isChange)
		{
			m_Menu->render();
			isChange = false;
		}

		if (m_Session->Play && !m_Menu && isChange)
		{
			m_Session->render();
			isChange = false;
		}
	}

} // Tetris
