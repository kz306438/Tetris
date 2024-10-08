#pragma once

#include "Menu.h"
#include "OptionsMenu.h"
#include "../consoleGUI/GUI.h"

namespace Tetris
{
	class Game;

	class PauseOptionsMenu : public Menu
	{
	public:
		PauseOptionsMenu(Game& game);

		void render() override;
		void update(float ts) override;

	private:
		void setupButtons();
		void createButtons();
		void chooseGameMusic();

	private:
		std::unique_ptr<ScrollButton> m_SBGameMusicTypes;
		std::unique_ptr<SliderButton> m_SBSoundVolume;
		std::unique_ptr<SliderButton> m_SBMusicVolume;
		std::unique_ptr<SliderButton> m_SBMotionDelay;
		std::unique_ptr<PushButton> m_PBDone;

		int m_Select = -1;

		Game& m_Game;

	};

} // Tetris