#include "OptionsMenu.h"
#include "../Sound/Sound.h"
#include "../Images.h"

namespace Tetris
{

	OptionsMenu::OptionsMenu(Game& game)
		: m_Game(game)
	{
		createButtons();
		setupButtons();
	}

	void OptionsMenu::update(float ts)
	{
		if (Application::pastTime.elapsedSeconds() > ts)
		{
			mouseButtonInteraction(m_PBMoveRight.get(), m_PBMoveLeft.get(), m_PBRotate.get(), m_PBSoftDrop.get(),
				m_PBHardDrop.get(), m_PBHold.get(), m_PBResetHighScores.get(), m_PBResetOptions.get(),
				m_PBDone.get(), m_SBMusicVolume.get(), m_SBSoundVolume.get(),
				m_SBGameMusicTypes.get(), m_SBMenuMusicTypes.get());
			Application::pastTime.reset();
		}

		if (m_Select == 0)
			handleActionButtons(m_PBMoveRight.get(), "MOVE RIGHT", GameData::getInstance().moveRightKey);

		if (m_Select == 1)
			handleActionButtons(m_PBMoveLeft.get(), "MOVE LEFT", GameData::getInstance().moveLeftKey);

		if (m_Select == 2)
			handleActionButtons(m_PBRotate.get(), "ROTATE", GameData::getInstance().rotateKey);

		if (m_Select == 3)
			handleActionButtons(m_PBSoftDrop.get(), "SOFT DROP", GameData::getInstance().softDropKey);

		if (m_Select == 4)
			handleActionButtons(m_PBHardDrop.get(), "HARD DROP", GameData::getInstance().hardDropKey);

		if (m_Select == 5)
			handleActionButtons(m_PBHold.get(), "HOLD", GameData::getInstance().holdKey);

		if (m_Select == 6)
		{
			GameData::getInstance().saveUserData();
			m_Game.SetMenu<MainMenu>();
		}

		if (m_Select == 7)
			resetHighScores();

		if (m_Select == 8)
			resetOptions();

		if (m_Select == 9)
			gameMusicTypes();

		if (m_Select == 10)
			menuMusicTypes();

		m_Select = -1;
	}

	void OptionsMenu::render()
	{
		m_PBMoveRight->allowChanges();       m_PBMoveRight->show();
		m_PBMoveLeft->allowChanges();        m_PBMoveLeft->show();
		m_PBRotate->allowChanges();          m_PBRotate->show();
		m_PBSoftDrop->allowChanges();        m_PBSoftDrop->show();
		m_PBHardDrop->allowChanges();        m_PBHardDrop->show();
		m_PBHold->allowChanges();            m_PBHold->show();
		m_SBMusicVolume->allowChanges();     m_SBMusicVolume->show();
		m_SBSoundVolume->allowChanges();     m_SBSoundVolume->show();
		m_PBResetHighScores->allowChanges(); m_PBResetHighScores->show();
		m_PBResetOptions->allowChanges();    m_PBResetOptions->show();
		m_PBDone->allowChanges();            m_PBDone->show();
		m_SBGameMusicTypes->allowChanges();  m_SBGameMusicTypes->show();
		m_SBMenuMusicTypes->allowChanges();  m_SBMenuMusicTypes->show();

		ConsoleManager::getInstance().SetCursorPosition(2, 3); std::cout << "MOVE RIGHT";
		ConsoleManager::getInstance().SetCursorPosition(2, 6); std::cout << "MOVE LEFT";
		ConsoleManager::getInstance().SetCursorPosition(2, 9); std::cout << "ROTATE";
		ConsoleManager::getInstance().SetCursorPosition(38, 3); std::cout << "SOFT DROP";
		ConsoleManager::getInstance().SetCursorPosition(38, 6); std::cout << "HARD DROP";
		ConsoleManager::getInstance().SetCursorPosition(38, 9); std::cout << "HOLD";
	}

	void OptionsMenu::createButtons() {
		m_PBMoveRight = std::make_unique<PushButton>(16, 3, GetKeyName(GameData::getInstance().moveRightKey), 16, 2);
		m_PBMoveLeft = std::make_unique<PushButton>(16, 3, GetKeyName(GameData::getInstance().moveLeftKey), 16, 5);
		m_PBRotate = std::make_unique<PushButton>(16, 3, GetKeyName(GameData::getInstance().rotateKey), 16, 8);
		m_PBSoftDrop = std::make_unique<PushButton>(16, 3, GetKeyName(GameData::getInstance().softDropKey), 52, 2);
		m_PBHardDrop = std::make_unique<PushButton>(16, 3, GetKeyName(GameData::getInstance().hardDropKey), 52, 5);
		m_PBHold = std::make_unique<PushButton>(16, 3, GetKeyName(GameData::getInstance().holdKey), 52, 8);
		m_PBResetHighScores = std::make_unique<PushButton>(21, 3, "RESET HIGH SCORES", 8, 22);
		m_PBResetOptions = std::make_unique<PushButton>(20, 3, "RESET OPTIONS", 44, 22);
		m_PBDone = std::make_unique<PushButton>(16, 3, "DONE", 28, 26);
		m_SBMusicVolume = std::make_unique<SliderButton>(0, 20, "MUSIC VOLUME", GameData::getInstance().musicVolume / 5,
			5, 7, 17, SliderButton::Orientation::HORIZONTAL);
		m_SBSoundVolume = std::make_unique<SliderButton>(0, 20, "SOUND VOLUME", GameData::getInstance().soundVolume / 5,
			5, 7, 12, SliderButton::Orientation::HORIZONTAL);

		m_SBGameMusicTypes = std::make_unique<ScrollButton>(Tile::musicTypes, 50, 15,
			ScrollButton::Orientation::HORIZONTAL);
		m_SBGameMusicTypes->addName("GAME MUSIC", 50, 13);
		m_SBGameMusicTypes->nextSlide(static_cast<int>(GameData::getInstance().gameMusicType - 'A'));

		m_SBMenuMusicTypes = std::make_unique<ScrollButton>(Tile::musicTypes, 50, 20,
			ScrollButton::Orientation::HORIZONTAL);
		m_SBMenuMusicTypes->addName("MENU MUSIC", 50, 18);
		m_SBMenuMusicTypes->nextSlide(static_cast<int>(GameData::getInstance().menuMusicType - 'A'));
	}


	void OptionsMenu::setupButtons() {

		m_PBMoveRight->connect([&]() { m_Select = 0; });
		m_PBMoveLeft->connect([&]() { m_Select = 1; });
		m_PBRotate->connect([&]() { m_Select = 2; });
		m_PBSoftDrop->connect([&]() { m_Select = 3; });
		m_PBHardDrop->connect([&]() { m_Select = 4; });
		m_PBHold->connect([&]() { m_Select = 5; });
		m_PBDone->connect([&]() { m_Select = 6; });

		m_SBMusicVolume->connect
		(
			[&]() 
			{
			    GameData::getInstance().musicVolume -= 5;
			    Sound::setMusicVolume(GameData::getInstance().musicVolume);
			},
			[&]() 
			{ 
				GameData::getInstance().musicVolume += 5;
				Sound::setMusicVolume(GameData::getInstance().musicVolume);
			}
		);

		m_SBSoundVolume->connect
		(
			[&]() 
			{
				GameData::getInstance().soundVolume -= 5;
		        Sound::setSoundVolume(GameData::getInstance().soundVolume); 
			},
			[&]() 
			{ 
				GameData::getInstance().soundVolume += 5;
		        Sound::setSoundVolume(GameData::getInstance().soundVolume); 
			}
		);

		m_PBResetHighScores->connect([&]() { m_Select = 7; });
		m_PBResetOptions->connect([&]() { m_Select = 8; });

		m_SBGameMusicTypes->connect([&]() { m_Select = 9; }, [&]() { m_Select = 9; });
		m_SBMenuMusicTypes->connect([&]() { m_Select = 10; }, [&]() { m_Select = 10; });
	}

	void OptionsMenu::gameMusicTypes()
	{
		int num = m_SBGameMusicTypes->getSlideNumber();
		if (num == 0)
			GameData::getInstance().gameMusicType = 'A';
		if (num == 1)
			GameData::getInstance().gameMusicType = 'B';
		if (num == 2)
			GameData::getInstance().gameMusicType = 'C';
	}

	void OptionsMenu::menuMusicTypes()
	{
		int num = m_SBMenuMusicTypes->getSlideNumber();
		if (num == 0)
			GameData::getInstance().menuMusicType = 'A';
		if (num == 1)
			GameData::getInstance().menuMusicType = 'B';
		if (num == 2)
			GameData::getInstance().menuMusicType = 'C';

		Sounds::MusicCurrentlyPlaying->stop();
		Sounds::MenuThemes[GameData::getInstance().menuMusicType]->play();
		Sounds::MenuThemes[GameData::getInstance().menuMusicType]->setLoop(true);
	}

	void OptionsMenu::resetOptions()
	{
		if (dialogWindow("RESET OPTIONS?")) {
			GameData::getInstance().moveRightKey = VK_RIGHT;
			GameData::getInstance().moveLeftKey = VK_LEFT;
			GameData::getInstance().rotateKey = VK_UP;
			GameData::getInstance().softDropKey = VK_DOWN;
			GameData::getInstance().hardDropKey = 32;
			GameData::getInstance().holdKey = 'C';

			m_PBMoveRight->setName(GetKeyName(GameData::getInstance().moveRightKey));
			m_PBMoveLeft->setName(GetKeyName(GameData::getInstance().moveLeftKey));
			m_PBRotate->setName(GetKeyName(GameData::getInstance().rotateKey));
			m_PBSoftDrop->setName(GetKeyName(GameData::getInstance().softDropKey));
			m_PBHardDrop->setName(GetKeyName(GameData::getInstance().hardDropKey));
			m_PBHold->setName(GetKeyName(GameData::getInstance().holdKey));

			GameData::getInstance().motionDelay = 100.0;
		}
		ConsoleManager::getInstance().ClearScreen();
		m_Game.isChange = true;
	}

	void OptionsMenu::resetHighScores()
	{
		if (dialogWindow("RESET HIGH SCORES?")) {
			GameData::getInstance().topScores = { 0, 0, 0, 0, 0 };
		}
		ConsoleManager::getInstance().ClearScreen();
		m_Game.isChange = true;
	}


	void OptionsMenu::handleActionButtons(PushButton* button, const std::string& actionDescription, int& keyToChange)
	{
		popUpForChangeButton("PRESS THE DESIRED KEY FOR", actionDescription, keyToChange);
		ConsoleManager::getInstance().ClearScreen();
		m_Game.isChange = true;
		button->setName(GetKeyName(keyToChange));
	}

	void popUpForChangeButton(const std::string& head, const std::string& text, int& keyForChange)
	{
		bool stopWindow = false;

		Window popUpWindow(40, 10, 16, 10);
		popUpWindow.show();

		PushButton cancel(12, 3, "CANCEL", 30, 16);
		cancel.connect([&]() { stopWindow = true; });
		ConsoleManager::getInstance().SetCursorPosition(36 - head.size() / 2, 11);
		std::cout << head;

		ConsoleManager::getInstance().SetCursorPosition(36 - text.size() / 2, 13);
		std::cout << text;

		setupInputHandling();
		while (!stopWindow)
		{
			mouseButtonInteraction(&cancel);
			if (_kbhit())
			{
				int temp = keyForChange;
				keyForChange = _getch();
				keyForChange = _getch();
				keyForChange = toupper(keyForChange);
				if (keyForChange == 0x50)keyForChange = VK_DOWN;
				if (keyForChange == 0x48)keyForChange = VK_UP;
				if (keyForChange == 0x4B)keyForChange = VK_LEFT;
				if (keyForChange == 0x4D)keyForChange = VK_RIGHT;
				if (!isCanChangeName(keyForChange))keyForChange = temp;
				stopWindow = true;
			}
		}
	}

	bool isCanChangeName(int key)
	{
		int cnt = 0;
		if (key == GameData::getInstance().moveRightKey)cnt++;
		if (key == GameData::getInstance().moveLeftKey)cnt++;
		if (key == GameData::getInstance().rotateKey)cnt++;
		if (key == GameData::getInstance().softDropKey)cnt++;
		if (key == GameData::getInstance().hardDropKey)cnt++;
		if (key == GameData::getInstance().holdKey)cnt++;
		if (cnt >= 2) return false;
		else return true;
	}

	std::string GetKeyName(int keyCode) {
		switch (keyCode) {
		case 13: return "ENTER";
		case VK_SPACE: return "SPACE";
		case VK_TAB: return "TAB";
		case VK_ESCAPE: return "ESCAPE";
		case VK_LEFT: return "LEFT ARROW";
		case VK_UP: return "UP ARROW";
		case VK_RIGHT: return "RIGHT ARROW";
		case VK_DOWN: return "DOWN ARROW";
		default: return std::string(1, char(keyCode));
		}
	}

} // Tetris