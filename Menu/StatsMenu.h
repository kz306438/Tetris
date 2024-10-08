#pragma once

#include "Menu.h"
#include "../consoleGUI/GUI.h"
#include <memory>

namespace Tetris
{

	class Game;

	class StatsMenu : public Menu
	{
	public:
		StatsMenu(Game& game);

		void update(float ts) override;
		void render() override;
	private:
		void setupButtons();
		
		void renderAllTimeData();
		void renderAverageData();
		void renderMaxLines();
		void renderTopScores();

	private:
		Game& m_Game;

		std::unique_ptr<PushButton> m_PBBack;

		int m_Select = -1;
	};

} // Tetris