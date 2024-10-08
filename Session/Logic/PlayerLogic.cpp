#include "PlayerLogic.h"
#include "../../Images.h"
#include "../../Sound/Sound.h"
#include "../../GameData.h"

namespace Tetris
{
	PlayerLogic::PlayerLogic(PlayField& field)
		: Logic(field)
	{
	}

	/*virtual*/ void PlayerLogic::Control()
	{
		// Rotate logic
		if ((GetAsyncKeyState(GameData::getInstance().rotateKey) & 0x8000))
		{
			if (!rotateKeyWasPressed)
			{
				rotate();
				rotateKeyWasPressed = true;
			}
		}
		else
		{
			rotateKeyWasPressed = false;
		}

		// Move right logic
		if (motionDelay.elapsedMiliseconds() > GameData::getInstance().motionDelay &&
			(GetAsyncKeyState(GameData::getInstance().moveRightKey) & 0x8000))
		{
			moveRight();
		}

		// Move left logic
		if (motionDelay.elapsedMiliseconds() > GameData::getInstance().motionDelay &&
			(GetAsyncKeyState(GameData::getInstance().moveLeftKey) & 0x8000))
		{
			moveLeft();
		}

		// Hold logic
		if ((GetAsyncKeyState(GameData::getInstance().holdKey) & 0x8000) &&
			isCanUseHold)
		{
			hold();
		}

		//Soft drop logic
		if (GetAsyncKeyState(GameData::getInstance().softDropKey) & 0x8000) {
			figureSpeed = NORMAL_FALL_SPEED;
		}

		//Hard drop logic
		if (GetAsyncKeyState(GameData::getInstance().hardDropKey) & 0x8000)
		{
			figureSpeed = HARD_FALL_SPEED;
		}

		activeFigure->render();
	}

	/*virtual*/ void PlayerLogic::GetFigureOutOfBag()
	{
		if (activeFigure)
		{
			nextFigure->clear();
			nextFigure->setPosition(spawnPositionX, spawnPositionY);
			activeFigure = getNextFigure();
			nextFigure = defineNextFigure();
			Tile::TileMap[nextFigure->getColor()]->render(Field.getPosX() + Field.getWidth() * 2 + 11, 8);
		}
		else
		{
			activeFigure = defineNextFigure();
			nextFigure = defineNextFigure();
		}
		isCanUseHold = true;
	}

	void PlayerLogic::moveRight()
	{
		activeFigure->clear();

		int posX = activeFigure->getPosition().first - Field.getPosX();
		int posY = activeFigure->getPosition().second - Field.getPosY();

		for (int i = 0; i < 4; ++i)
		{
			int cellX = posX + activeFigure->coord[i].getPosition().first + 2;
			int cellY = posY + activeFigure->coord[i].getPosition().second;

			if (cellX == Field.getWidth() * 2 || Field.getCell(cellX / 2, cellY).state)
			{
				motionDelay.reset();
				return;
			}
		}

		activeFigure->setPosition(activeFigure->getPosition().first + 2, activeFigure->getPosition().second);
		activeFigure->render();
		motionDelay.reset();
		Sounds::BrickSound.play();
	}

	void PlayerLogic::moveLeft()
	{
		activeFigure->clear();
		int posX = activeFigure->getPosition().first - Field.getPosX();
		int posY = activeFigure->getPosition().second - Field.getPosY();

		for (int i = 0; i < 4; ++i)
		{
			int cellX = posX + activeFigure->coord[i].getPosition().first - 2;
			int cellY = posY + activeFigure->coord[i].getPosition().second;

			if (cellX < 0 || Field.getCell(cellX / 2, cellY).state)
			{
				motionDelay.reset();
				return;
			}
		}

		activeFigure->setPosition(activeFigure->getPosition().first - 2, activeFigure->getPosition().second);
		activeFigure->render();
		motionDelay.reset();
		Sounds::BrickSound.play();
	}

	void PlayerLogic::rotate()
	{
		activeFigure->clear();
		activeFigure->rotation();

		int posX = activeFigure->getPosition().first - Field.getPosX();
		int posY = activeFigure->getPosition().second - Field.getPosY();

		for (int i = 0; i < 4; ++i)
		{
			int cellX = posX + activeFigure->coord[i].getPosition().first;
			int cellY = posY + activeFigure->coord[i].getPosition().second;

			if (cellX > Field.getWidth() * 2 - 2 || cellX < 0 || cellY >= Field.getHeight() ||
				Field.getCell(cellX / 2, cellY).state)
			{
				activeFigure->rotation(); // Revert rotation
				activeFigure->rotation();
				activeFigure->rotation();
				break;
			}
		}
		activeFigure->render();
		motionDelay.reset();
		Sounds::BrickSound.play();
	}

} // Tetris