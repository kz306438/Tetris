#pragma once

#include "Menu.h"
#include "MainMenu.h"
#include "../consoleGUI/GUI.h"
#include "../GameData.h"
#include "../Application.h"
#include "../ConsoleManager.h"


namespace Tetris
{
	class Game;

	std::string GetKeyName(int keyCode);
	void popUpForChangeButton(const std::string& head, const std::string& text, int& keyForChange);
	bool isCanChangeName(int key);

	class OptionsMenu : public Menu
	{
	public:
		OptionsMenu(Game& game);

		void update(float ts) override;
		void render() override;

	private:
		void createButtons();
		void setupButtons();

		void gameMusicTypes();
		void menuMusicTypes();
		void resetHighScores();
		void resetOptions();

		void handleActionButtons(PushButton* button, const std::string& actionDescription, int& keyToChange);

	private:

		std::unique_ptr<PushButton> m_PBMoveRight;
		std::unique_ptr<PushButton> m_PBMoveLeft;
		std::unique_ptr<PushButton> m_PBRotate;
		std::unique_ptr<PushButton> m_PBSoftDrop;
		std::unique_ptr<PushButton> m_PBHardDrop;
		std::unique_ptr<PushButton> m_PBHold;
		std::unique_ptr<PushButton> m_PBResetHighScores;
		std::unique_ptr<PushButton> m_PBResetOptions;
		std::unique_ptr<PushButton> m_PBDone;
		std::unique_ptr<SliderButton> m_SBMusicVolume;
		std::unique_ptr<SliderButton> m_SBSoundVolume;
		std::unique_ptr<ScrollButton> m_SBGameMusicTypes;
		std::unique_ptr<ScrollButton> m_SBMenuMusicTypes;

		int m_Select = -1;

		Game& m_Game;
	};


} // Tetris