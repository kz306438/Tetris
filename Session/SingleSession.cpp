#include "SingleSession.h"

#include "Logic/PlayerLogic.h"
#include "../Sound/Sound.h"
#include "../GameData.h"
#include "../Menu/PauseMenu.h"
#include "../Images.h"

namespace Tetris
{

	SingleSession::SingleSession(Game& game)
		: Session(game)
	{
		m_Logic = std::make_unique<PlayerLogic>(Field);
	}

	void SingleSession::update()
	{
		if (isDead())
			Play = false;

		m_Logic->Control();

		if (isFallen())
		{
			if (time.elapsedMiliseconds() >= 300)
			{
				Sounds::FallSound.play();
				Field.addFigure(m_Logic->getActiveFigure().get());
				m_Logic->GetFigureOutOfBag();
				data.calculatePoints(Field.checkLine());
				time.reset();
			}
		}
		else if (time.elapsedMiliseconds() >= m_Logic->figureSpeed)
		{
			if (m_Logic->downButtonWasPressed())
			{
				data.incScore();
				data.render();
			}
			m_Logic->goDown();
			time.reset();
		}
		mouseButtonInteraction(m_CBPause.get());

		if (GetAsyncKeyState(27) & 0x8000)
			m_Select = 0;

		if (m_Select == 0)
		{
			Sounds::GameThemes[GameData::getInstance().gameMusicType]->pause();
			m_Game.SetMenu<PauseMenu>();
			m_Select = -1;
		}

		m_Logic->figureSpeed = 1010 - data.getLevel() * 40;

		if (!Play)
			clear();
	}

	void SingleSession::render()
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

		m_CBPause->allowChanges();
		m_CBPause->show();
	}


} // Tetris
