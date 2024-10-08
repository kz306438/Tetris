#include "AISession.h"

#include "../Sound/Sound.h"
#include "../GameData.h"
#include "../Menu/PauseMenu.h"
#include "../Images.h"

namespace Tetris
{
	AISession::AISession(Game& game)
		: Session(game)
	{
		m_Logic = std::make_unique<AILogic>(Field);
		setupButtons();
	}

	/*virtual*/ void AISession::update()
	{
		if (isDead())
			Play = false;

		m_Logic->Control();

		if (isFallen())
		{
			if (time.elapsedMiliseconds() >= m_Logic->figureSpeed * 7.5)
			{
				Sounds::FallSound.play();
				Field.addFigure(m_Logic->getActiveFigure().get());
				data.calculatePoints(Field.checkLine());
				m_Logic->GetFigureOutOfBag();
				time.reset();
			}
		}
		else if (time.elapsedMiliseconds() >= m_Logic->figureSpeed)
		{
			data.incScore();
			data.render();
			m_Logic->goDown();
			time.reset();
		}
		mouseButtonInteraction(m_CBPause.get(), m_SBSpeed.get());

		if (GetAsyncKeyState(27) & 0x8000)
			m_Select = 0;

		if (m_Select == 0)
		{
			Sounds::GameThemes[GameData::getInstance().gameMusicType]->pause();
			m_Game.SetMenu<PauseMenu>();
			m_Select = -1;
		}

		if (!Play)
			clear();
	}

	/*virtual*/ void AISession::render()
	{
		ConsoleManager::getInstance().ClearScreen();

		TetrisTitleRender::get().render(m_FieldPosX + m_Width - 14, 0);

		renderGameWindow();
		renderNextFiguteWindow();
		renderHoldFigureWindow();
		renderDataWindow();

		data.render();

		if (m_Logic->getHoldFigure())
			Tile::TileMap[m_Logic->getHoldFigure()->getColor()]->render(7, 8);

		Tile::TileMap[m_Logic->getNextFigure()->getColor()]->render(m_FieldPosX + m_Width * 2 + 11, 8);

		Field.render();

		m_CBPause->allowChanges();	m_CBPause->show();
		m_SBSpeed->allowChanges();  m_SBSpeed->show();
	}

	void AISession::setupButtons()
	{
		m_SBSpeed = std::make_unique<SliderButton>
			(
				0,
				10,
				"SPEED",
			    (m_Logic->NORMAL_FALL_SPEED - m_Logic->figureSpeed) / 4,
				m_FieldPosX + m_Width * 2 + 8,
				15,
				SliderButton::Orientation::HORIZONTAL
			);

		m_SBSpeed->connect
		(
			[&]() { m_Logic->figureSpeed += 4; },
			[&]() { m_Logic->figureSpeed -= 4; }
		);
	}

} // Tetris
