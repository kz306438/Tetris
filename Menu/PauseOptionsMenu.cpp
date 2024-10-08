#include "PauseOptionsMenu.h"
#include "PauseMenu.h"
#include "../Sound/Sound.h"
#include "../Images.h"

namespace Tetris
{
	PauseOptionsMenu::PauseOptionsMenu(Game& game)
		: m_Game(game)
	{
		createButtons();
		setupButtons();
	}

	void PauseOptionsMenu::render()
	{
		Window optionsWindow(42, 27, 15, 2);
        optionsWindow.addWindowName("OPTIONS", 16, 0);
        optionsWindow.show();

		m_SBMusicVolume->allowChanges();     m_SBMusicVolume->show();
		m_PBDone->allowChanges();            m_PBDone->show();
	}

	void PauseOptionsMenu::update(float ts)
	{
		if (Application::pastTime.elapsedSeconds() > ts)
		{
			mouseButtonInteraction(m_PBDone.get(), m_SBGameMusicTypes.get(), m_SBMusicVolume.get(),
				m_SBSoundVolume.get(), m_SBMotionDelay.get());
			Application::pastTime.reset();
		}

		if (m_Select == 0)
		{
			Sound::setMusicVolume(GameData::getInstance().musicVolume);
			Sound::setSoundVolume(GameData::getInstance().soundVolume);
			GameData::getInstance().saveUserData();
			m_Game.SetMenu<PauseMenu>();
		}

		if (m_Select == 1)
			chooseGameMusic();

		m_Select = -1;
	}

	void PauseOptionsMenu::setupButtons()
	{
		m_PBDone->connect([&]() { m_Select = 0; });

		m_SBMusicVolume->connect
		(
			[&]() { GameData::getInstance().musicVolume -= 5; },
			[&]() { GameData::getInstance().musicVolume += 5; }
		);

		m_SBSoundVolume->connect
		(
			[&]() { GameData::getInstance().soundVolume -= 5; },
			[&]() { GameData::getInstance().soundVolume += 5; }
		);

		m_SBMotionDelay->connect
		(    
			[&]() { GameData::getInstance().motionDelay -= 5; },
			[&]() { GameData::getInstance().motionDelay += 5; }
		);

		m_SBGameMusicTypes->connect
		(
			[&]() { m_Select = 1; },
			[&]() {m_Select = 1; }
		);
	}

	void PauseOptionsMenu::createButtons()
	{
		m_SBGameMusicTypes = std::make_unique<ScrollButton>(Tile::musicTypes, 31, 6,
			ScrollButton::Orientation::HORIZONTAL);
		m_SBGameMusicTypes->addName("GAME MUSIC", 31, 4);
		m_SBGameMusicTypes->nextSlide(static_cast<int>(GameData::getInstance().gameMusicType - 'A'));

		m_PBDone = std::make_unique<PushButton>(16, 3, "DONE", 28, 25);

		m_SBMusicVolume = std::make_unique<SliderButton>(0, 20, "MUSIC VOLUME", GameData::getInstance().musicVolume / 5,
			5, 25, 8, SliderButton::Orientation::HORIZONTAL);

		m_SBSoundVolume = std::make_unique<SliderButton>(0, 20, "SOUND VOLUME", GameData::getInstance().soundVolume / 5,
			5, 25, 14, SliderButton::Orientation::HORIZONTAL);

		m_SBMotionDelay = std::make_unique<SliderButton>(10, 30, "MOTION DELAY (ms)", GameData::getInstance().motionDelay / 5,
			5, 25, 20, SliderButton::Orientation::HORIZONTAL);
	}

	void PauseOptionsMenu::chooseGameMusic()
	{
		int num = m_SBGameMusicTypes->getSlideNumber();
		if (num == 0)
			GameData::getInstance().gameMusicType = 'A';
		if (num == 1)
			GameData::getInstance().gameMusicType = 'B';
		if (num == 2)
			GameData::getInstance().gameMusicType = 'C';
	}

} // Tetris