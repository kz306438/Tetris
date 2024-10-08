#pragma once

#include <memory>

#include "Figure.h"
#include "PlayField.h"
#include "LevelData.h"

#include "../Timer.h"
#include "../consoleGUI/colors.h"
#include "../FileManager.h"
#include "Logic/Logic.h"
#include "Logic/AILogic.h"

namespace Tetris
{

	class Game;

	class Session
	{
	public:
		Session(Game& game);
		virtual ~Session() = default;

		virtual void update() = 0;
		virtual void render() = 0;

		void setupGame();

		bool isFallen();
		bool isDead();

		void clear();
	protected:
		void renderGameWindow();
		void renderNextFiguteWindow();
		void renderHoldFigureWindow();
		void renderDataWindow();

		void setupButton();

	public:
		bool Play = false;

	protected:
		std::unique_ptr<CustomButton> m_CBPause;

		int m_Height = 20;
		int m_Width = 10;
		int m_FieldPosX = 26;
		int m_FieldPosY = 6;
	protected:

		int m_Select = -1;

		Game& m_Game;

		std::unique_ptr<Logic> m_Logic;

		PlayField Field;
		LevelData data;
		Timer time;
	};

} // Tetris