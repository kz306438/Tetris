#pragma once

#include <memory>
#include "../Figure.h"
#include "../PlayField.h"
#include "../../Timer.h"

namespace Tetris
{

	class Logic
	{
	public:

		Logic(PlayField& field);
		virtual ~Logic() = default;

		virtual void Control() = 0;
		virtual void GetFigureOutOfBag() = 0;

		void goDown();

		void shaffleShapes();
		std::shared_ptr<Figure> defineNextFigure();

		std::shared_ptr<Figure> getActiveFigure() const;
		std::shared_ptr<Figure> getNextFigure() const;
		std::shared_ptr<Figure> getHoldFigure() const;

		void clear();

		void hold();
		bool downButtonWasPressed();
	public:
		int figureSpeed{};

		const int NORMAL_FALL_SPEED = 40;
		const int HARD_FALL_SPEED = 0;

	protected:
		std::shared_ptr<Figure> activeFigure;
		std::shared_ptr<Figure> nextFigure;
		std::shared_ptr<Figure> holdFigure;

		bool isCanUseHold = true;

		std::vector<std::shared_ptr<Figure>> bag;

		int spawnPositionX{};
		int spawnPositionY{};

		PlayField& Field;
	};

} // Tetris