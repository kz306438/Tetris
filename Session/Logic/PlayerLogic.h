#pragma once

#include "Logic.h"
#include "../PlayField.h"

namespace Tetris
{

	class PlayerLogic : public Logic
	{
	public:
		PlayerLogic(PlayField& field);

		void Control() override;
		void GetFigureOutOfBag() override;

	private:
		void moveRight();
		void moveLeft();
		void rotate();

	private:
		Timer motionDelay;
		bool rotateKeyWasPressed = false;

	};

} // Tetris