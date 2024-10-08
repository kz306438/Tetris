#pragma once

#include <memory>
#include "Menu/Menu.h"
#include "Menu/MainMenu.h"
#include "Menu/OptionsMenu.h"
#include "Menu/SplashScreen.h"
#include "Session/Session.h"
#include "Session/SingleSession.h"
#include "Session/AISession.h"

namespace Tetris
{
	class SplashScreen;

	class Game
	{
	public:
		Game();

		void run();
		void finishGame();

		void update(float ts);
		void render();

		template<typename T>
		void SetMenu()
		{
			m_Menu = std::make_shared<T>(*this);
			isChange = true;
		}

		template<>
		void SetMenu<std::nullptr_t>()
		{
			m_Menu = nullptr;
			isChange = true;
		}

		template <typename T>
		void SetSession()
		{
			m_Session = std::make_shared<T>(*this);
		}

	public:
		bool isChange = false;

	private:
		std::shared_ptr<Menu> m_Menu;
		std::shared_ptr<Session> m_Session;

	};

} // Tetris
