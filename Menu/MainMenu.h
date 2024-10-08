#pragma once

#include "../consoleGUI/GUI.h"
#include "Menu.h"
#include "../Application.h"
#include "../Image.h"
#include "../GameData.h"
#include "OptionsMenu.h"

namespace Tetris
{
	class Game;

	class MainMenu : public Menu
	{
	public:

		MainMenu(Game& game);

		void update(float ts) override;
		void render() override;

	private:
		void connectButtons();
		void createButtons();

	private:
		std::unique_ptr<PushButton> m_PBSoloMode;
		std::unique_ptr<PushButton> m_PBAIMode;
		std::unique_ptr<PushButton> m_PBStats;
		std::unique_ptr<PushButton> m_PBOptions;
		std::unique_ptr<PushButton> m_PBQuit;

		int m_Select = -1;

		Game& m_Game;
	};

	bool dialogWindow(const std::string& head);

} // Tetris
