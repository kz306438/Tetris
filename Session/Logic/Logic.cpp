#include "Logic.h"
#include "../../Images.h"
#include "../../Sound/Sound.h"
#include "../../GameData.h"

namespace Tetris
{
	Logic::Logic(PlayField& field)
		: Field(field)
	{
		spawnPositionX = Field.getPosX() + Field.getWidth() - 2;
		spawnPositionY = Field.getPosY();
		shaffleShapes();
	}

	void Logic::goDown()
	{
		activeFigure->clear();
		activeFigure->setPosition(activeFigure->getPosition().first, activeFigure->getPosition().second + 1);
	}

	void Logic::shaffleShapes()
	{
		std::vector<std::shared_ptr<Figure>> shapes =
		{
			std::make_shared<IFigure>(spawnPositionX, spawnPositionY),
			std::make_shared<OFigure>(spawnPositionX, spawnPositionY),
			std::make_shared<TFigure>(spawnPositionX, spawnPositionY),
			std::make_shared<SFigure>(spawnPositionX, spawnPositionY),
			std::make_shared<ZFigure>(spawnPositionX, spawnPositionY),
			std::make_shared<JFigure>(spawnPositionX, spawnPositionY),
			std::make_shared<LFigure>(spawnPositionX, spawnPositionY)
		};
		bag = shapes;
		std::random_device rd;
		std::mt19937 g(rd());
		std::shuffle(bag.begin(), bag.end(), g);
	}

	std::shared_ptr<Figure> Logic::defineNextFigure()
	{
		if (bag.empty())shaffleShapes();
		std::shared_ptr<Figure> figure = bag[bag.size() - 1];
		bag.pop_back();
		GameData::getInstance().TotalFigures++;
		return figure;
	}

	std::shared_ptr<Figure> Logic::getActiveFigure() const
	{
		return activeFigure;
	}

	std::shared_ptr<Figure> Logic::getNextFigure() const
	{
		return nextFigure;
	}

	std::shared_ptr<Figure> Logic::getHoldFigure() const
	{
		return holdFigure;
	}

	void Logic::clear()
	{
		activeFigure = nullptr;
		nextFigure = nullptr;
		holdFigure = nullptr;

		isCanUseHold = true;

		bag.clear();
	}

	void Logic::hold()
	{
		activeFigure->clear();

		if (holdFigure == nullptr)
		{
			holdFigure = activeFigure;
			holdFigure->clear();

			nextFigure->setPosition(spawnPositionX, spawnPositionY);
			activeFigure = nextFigure;
			nextFigure = defineNextFigure();
			Tile::TileMap[nextFigure->getColor()]->render(Field.getPosX() + Field.getWidth() * 2 + 11, 8);
		}
		else
		{
			std::shared_ptr<Figure> tempFigure = activeFigure;
			holdFigure->setPosition(spawnPositionX, spawnPositionY);
			activeFigure = holdFigure;

			holdFigure = tempFigure;
			holdFigure->clear();
		}
		Tile::TileMap[holdFigure->getColor()]->render(7, 8);
		isCanUseHold = false;

		activeFigure->render();
		Sounds::BrickSound.play();
	}

	bool Logic::downButtonWasPressed()
	{
		return figureSpeed == NORMAL_FALL_SPEED || figureSpeed == HARD_FALL_SPEED;
	}

} // Tetris