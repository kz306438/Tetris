#pragma once
#include <iostream>
#include <algorithm>
#include <random>
#include "consoleGUI/GUI.h"
#include "Variables.h"

class Square
{
public:
	Square() = default;
	Square(int squarePositionX, int squarePositionY) :
		squarePositionX(squarePositionX), squarePositionY(squarePositionY)
	{

	}
	Square(int squarePositionX, int squarePositionY, ConsoleColor squareColor) :
		squarePositionX(squarePositionX), squarePositionY(squarePositionY), squareColor(squareColor)
	{

	}


	void setPosition(int newPositionX, int newPositionY)
	{
		this->squarePositionX = newPositionX;
		this->squarePositionY = newPositionY;
	}

	void clear(int posX, int posY)
	{
		setcur(squarePositionX * 2 + posX, squarePositionY + posY);
		std::cout << ' ' << ' ';
	}

	std::pair<int, int> getPosition()
	{
		return { squarePositionX * 2, squarePositionY };
	}

	void setColor(ConsoleColor newSquareColor)
	{
		this->squareColor = newSquareColor;
	}

	ConsoleColor getColor()
	{
		return squareColor;
	}

	friend std::ostream& operator<<(std::ostream& os, const Square& obj);

private:
	int squarePositionX = 0;
	int squarePositionY = 0;
	std::pair<char, char> square = { global::leftSideTexture, global::rightSideTexture };
	ConsoleColor squareColor = White;
};

static std::ostream& operator<<(std::ostream& os, const Square& obj) {
	saveConsoleAttributes();
	setColorForeground(obj.squareColor);
	os << obj.square.first << obj.square.second;
	restoreConsoleAttributes();
	return os;
}

class Figure
{
public:
	virtual void rotation()
	{

	}

	void clear()
	{
		for (int i = 0; i < 4; i++)
		{
			figure[i].clear(figurePositionX, figurePositionY);
		}
	}

	void show()
	{
		for (int i = 0; i < 4; i++)
		{
			setcur(figurePositionX + figure[i].getPosition().first, figurePositionY + figure[i].getPosition().second);
			std::cout << figure[i];
		}
	}
	void setPosition(const int newPosX, const int newPosY)
	{
		this->figurePositionX = newPosX;
		this->figurePositionY = newPosY;
	}

	std::pair<int, int> getPosition()
	{
		return { figurePositionX, figurePositionY };
	}

	std::pair<int, int> getAxisOfRotation()
	{
		return axisOfRotation;
	}
	virtual ~Figure() {}
	std::vector<Square> figure;
	int figurePositionX = 0;
	int figurePositionY = 0;
	std::pair<int, int> axisOfRotation;
};

class OFigure : public Figure
{
public:

	OFigure(int figurePositionX, int figurePositionY)
	{
		this->figurePositionX = figurePositionX;
		this->figurePositionY = figurePositionY;
		oFigureFill();
	}

	void oFigureFill()
	{
		figure.resize(4);
		Square sq(0, 0);

		sq.setColor(BrightYellow);
		figure[0] = sq;
		sq.setPosition(1, 0);
		figure[1] = sq;
		sq.setPosition(0, 1);
		figure[2] = sq;
		sq.setPosition(1, 1);
		figure[3] = sq;

		axisOfRotation = { 1, 0 };
	}

	void rotation() override
	{

	}
};

class LFigure : public Figure
{
public:
	LFigure(int figurePositionX, int figurePositionY)
	{
		this->figurePositionX = figurePositionX;
		this->figurePositionY = figurePositionY;
		lFigureFill();
	}
	void lFigureFill()
	{
		figure.resize(4);
		Square sq(0, 1);

		sq.setColor(Yellow);
		figure[0] = sq;
		sq.setPosition(1, 1);
		figure[1] = sq;
		sq.setPosition(2, 1);
		figure[2] = sq;
		sq.setPosition(2, 0);
		figure[3] = sq;

		axisOfRotation = { 1, 1 };
	}

	void rotation() override
	{
		for (int i = 0; i < 4; i++)
		{
			std::pair<int, int> prevPoint = figure[i].getPosition();
			figure[i].setPosition(axisOfRotation.first + axisOfRotation.second - prevPoint.second,
				axisOfRotation.second - axisOfRotation.first + prevPoint.first / 2);
		}
	}
};

class SFigure : public Figure
{
public:
	SFigure(int figurePositionX, int figurePositionY)
	{
		this->figurePositionX = figurePositionX;
		this->figurePositionY = figurePositionY;
		sFigureFill();
	}
	void sFigureFill()
	{
		figure.resize(4);
		Square sq(0, 2);

		sq.setColor(BrightGreen);
		figure[0] = sq;
		sq.setPosition(1, 2);
		figure[1] = sq;
		sq.setPosition(1, 1);
		figure[2] = sq;
		sq.setPosition(2, 1);
		figure[3] = sq;

		axisOfRotation = { 1, 1 };
	}



	void rotation() override
	{
		for (int i = 0; i < 4; i++)
		{
			std::pair<int, int> prevPoint = figure[i].getPosition();
			figure[i].setPosition(axisOfRotation.first + axisOfRotation.second - prevPoint.second,
				axisOfRotation.second - axisOfRotation.first + prevPoint.first / 2);
		}
	}
};

class ZFigure : public Figure
{
public:
	ZFigure(int figurePositionX, int figurePositionY)
	{
		this->figurePositionX = figurePositionX;
		this->figurePositionY = figurePositionY;
		zFigureFill();
	}
	void zFigureFill()
	{
		figure.resize(4);
		Square sq(0, 1);

		sq.setColor(BrightRed);
		figure[0] = sq;
		sq.setPosition(1, 1);
		figure[1] = sq;
		sq.setPosition(1, 2);
		figure[2] = sq;
		sq.setPosition(2, 2);
		figure[3] = sq;

		axisOfRotation = { 1, 1 };
	}

	void rotation() override
	{
		for (int i = 0; i < 4; i++)
		{
			std::pair<int, int> prevPoint = figure[i].getPosition();
			figure[i].setPosition(axisOfRotation.first + axisOfRotation.second - prevPoint.second,
				axisOfRotation.second - axisOfRotation.first + prevPoint.first / 2);
		}
	}
};

class IFigure : public Figure
{
public:
	IFigure(int figurePositionX, int figurePositionY)
	{
		this->figurePositionX = figurePositionX;
		this->figurePositionY = figurePositionY;
		iFigureFill();
	}
	void iFigureFill()
	{
		figure.resize(4);
		Square sq(0, 2);

		sq.setColor(BrightCyan);
		figure[0] = sq;
		sq.setPosition(1, 2);
		figure[1] = sq;
		sq.setPosition(2, 2);
		figure[2] = sq;
		sq.setPosition(3, 2);
		figure[3] = sq;

		axisOfRotation = { 2, 2 };
	}

	void rotation() override
	{
		for (int i = 0; i < 4; i++)
		{
			std::pair<int, int> prevPoint = figure[i].getPosition();
			figure[i].setPosition(axisOfRotation.first + axisOfRotation.second - prevPoint.second,
				axisOfRotation.second - axisOfRotation.first + prevPoint.first / 2);
		}
	}
};

class JFigure : public Figure
{
public:
	JFigure(int figurePositionX, int figurePositionY)
	{
		this->figurePositionX = figurePositionX;
		this->figurePositionY = figurePositionY;
		jFigureFill();
	}
	void jFigureFill()
	{
		figure.resize(4);
		Square sq(0, 0);

		sq.setColor(BrightBlue);
		figure[0] = sq;
		sq.setPosition(0, 1);
		figure[1] = sq;
		sq.setPosition(1, 1);
		figure[2] = sq;
		sq.setPosition(2, 1);
		figure[3] = sq;

		axisOfRotation = { 1, 1 };
	}

	void rotation() override
	{
		for (int i = 0; i < 4; i++)
		{
			std::pair<int, int> prevPoint = figure[i].getPosition();
			figure[i].setPosition(axisOfRotation.first + axisOfRotation.second - prevPoint.second,
				axisOfRotation.second - axisOfRotation.first + prevPoint.first / 2);
		}
	}
};

class TFigure : public Figure
{
public:
	TFigure(int figurePositionX, int figurePositionY)
	{
		this->figurePositionX = figurePositionX;
		this->figurePositionY = figurePositionY;
		tFigureFill();
	}
	void tFigureFill()
	{
		figure.resize(4);
		Square sq(0, 1);

		sq.setColor(BrightMagenta);
		figure[0] = sq;
		sq.setPosition(1, 1);
		figure[1] = sq;
		sq.setPosition(2, 1);
		figure[2] = sq;
		sq.setPosition(1, 2);
		figure[3] = sq;

		axisOfRotation = { 1, 1 };
	}

	void rotation() override
	{
		for (int i = 0; i < 4; i++)
		{
			std::pair<int, int> prevPoint = figure[i].getPosition();
			figure[i].setPosition(axisOfRotation.first + axisOfRotation.second - prevPoint.second,
				axisOfRotation.second - axisOfRotation.first + prevPoint.first / 2);
		}
	}
};