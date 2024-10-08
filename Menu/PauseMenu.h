#pragma once

#include "Menu.h"
#include "../consoleGUI/GUI.h"
#include <memory>

namespace Tetris
{
	class Game;

	class PauseMenu : public Menu
	{
	public:
		PauseMenu(Game& game);

		void render() override;
		void update(float ts) override;

	private:
		void setupButtons();

	private:
		std::unique_ptr<PushButton> m_PBResume;
		std::unique_ptr<PushButton> m_PBOptions;
		std::unique_ptr<PushButton> m_PBQuit;

		Game& m_Game;

		int m_Select = -1;

	};

} // Tetris