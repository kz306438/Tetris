#pragma once

#include <memory>
#include "../Game.h"
#include "Menu.h"
#include "../consoleGUI/GUI.h"

namespace Tetris
{

	class GameOverMenu : public Menu
	{
	public:
		GameOverMenu(Game& game);

		void render() override;
		void update(float ts) override;

	private:
		void setupButtons();

	private:
		std::unique_ptr<PushButton> m_PBHome;
		std::unique_ptr<PushButton> m_PBRestart;

		Game& m_Game;

		int m_Select = -1;
	};

} // Tetris