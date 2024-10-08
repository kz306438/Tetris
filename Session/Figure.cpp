#include "figure.h"

namespace Tetris
{

	Square::Square(int squarePositionX, int squarePositionY) :
		m_SquarePositionX(squarePositionX), m_SquarePositionY(squarePositionY) {}

	Square::Square(int squarePositionX, int squarePositionY, ConsoleColor squareColor) :
		m_SquarePositionX(squarePositionX), m_SquarePositionY(squarePositionY), m_SquareColor(squareColor) {}

	void Square::setPosition(int newPositionX, int newPositionY)
	{
		this->m_SquarePositionX = newPositionX;
		this->m_SquarePositionY = newPositionY;
	}

	void Square::clear(int posX, int posY)
	{
		setcur(m_SquarePositionX * 2 + posX, m_SquarePositionY + posY);
		std::cout << ' ' << ' ';
	}

	std::pair<int, int> Square::getPosition()
	{
		return { m_SquarePositionX * 2, m_SquarePositionY };
	}

	void Square::setColor(ConsoleColor newSquareColor)
	{
		this->m_SquareColor = newSquareColor;
	}

	ConsoleColor Square::getColor()
	{
		return m_SquareColor;
	}

	void Figure::clear()
	{
		for (int i = 0; i < 4; i++)
		{
			coord[i].clear(m_posX, m_posY);
		}
	}

	void Figure::render()
	{
		for (int i = 0; i < 4; i++)
		{
			setcur(m_posX + coord[i].getPosition().first, m_posY + coord[i].getPosition().second);
			std::cout << coord[i];
		}
	}
	void Figure::Figure::setPosition(int newPosX, int newPosY)
	{
		m_posX = newPosX;
		m_posY = newPosY;
	}

	std::pair<int, int> Figure::getPosition() const
	{
		return { m_posX, m_posY };
	}

	std::pair<int, int> Figure::getAxisOfRotation() const
	{
		return m_AxisOfRotation;
	}

	ConsoleColor Figure::getColor() const
	{
		return m_Color;
	}

	OFigure::OFigure(int posX, int posY)
	{
		m_posX = posX;
		m_posY = posY;
		m_Color = BrightYellow;
		fill();
	}

	void OFigure::rotation(){}

	void OFigure::fill()
	{
		coord.resize(4);
		Square sq(0, 0);
		sq.setColor(m_Color);

		coord[0] = sq;
		sq.setPosition(1, 0); coord[1] = sq;
		sq.setPosition(0, 1); coord[2] = sq;
		sq.setPosition(1, 1); coord[3] = sq;

		m_AxisOfRotation = { 1, 0 };
	}

	LFigure::LFigure(int posX, int posY)
	{
		m_posX = posX;
		m_posY = posY;
		m_Color = Yellow;
		fill();
	}
	void LFigure::fill()
	{
		coord.resize(4);

		Square sq(0, 1);
		sq.setColor(m_Color);

		coord[0] = sq;
		sq.setPosition(1, 1); coord[1] = sq;
		sq.setPosition(2, 1); coord[2] = sq;
		sq.setPosition(2, 0); coord[3] = sq;

		m_AxisOfRotation = { 1, 1 };
	}

	void LFigure::rotation()
	{
		for (int i = 0; i < 4; i++)
		{
			std::pair<int, int> prevPoint = coord[i].getPosition();
			coord[i].setPosition
			(
				m_AxisOfRotation.first + m_AxisOfRotation.second - prevPoint.second,
				m_AxisOfRotation.second - m_AxisOfRotation.first + prevPoint.first / 2
			);
		}
	}

	SFigure::SFigure(int posX, int posY)
	{
		m_posX = posX;
		m_posY = posY;
		m_Color = BrightGreen;
		fill();
	}
	void SFigure::fill()
	{
		coord.resize(4);

		Square sq(0, 2);
		sq.setColor(m_Color);
		coord[0] = sq;
		sq.setPosition(1, 2); coord[1] = sq;
		sq.setPosition(1, 1); coord[2] = sq;
		sq.setPosition(2, 1); coord[3] = sq;

		m_AxisOfRotation = { 1, 1 };
	}

	void SFigure::rotation()
	{
		for (int i = 0; i < 4; i++)
		{
			std::pair<int, int> prevPoint = coord[i].getPosition();
			coord[i].setPosition(m_AxisOfRotation.first + m_AxisOfRotation.second - prevPoint.second,
				m_AxisOfRotation.second - m_AxisOfRotation.first + prevPoint.first / 2);
		}
	}

	ZFigure::ZFigure(int posX, int posY)
	{
		m_posX = posX;
		m_posY = posY;
		m_Color = BrightRed;
		fill();
	}
	void ZFigure::fill()
	{
		coord.resize(4);

		Square sq(0, 1);
		sq.setColor(m_Color);

		coord[0] = sq;
		sq.setPosition(1, 1); coord[1] = sq;
		sq.setPosition(1, 2); coord[2] = sq;
		sq.setPosition(2, 2); coord[3] = sq;

		m_AxisOfRotation = { 1, 1 };
	}

	void ZFigure::rotation()
	{
		for (int i = 0; i < 4; i++)
		{
			std::pair<int, int> prevPoint = coord[i].getPosition();
			coord[i].setPosition(m_AxisOfRotation.first + m_AxisOfRotation.second - prevPoint.second,
				m_AxisOfRotation.second - m_AxisOfRotation.first + prevPoint.first / 2);
		}
	}

	IFigure::IFigure(int posX, int posY)
	{
		m_posX = posX;
		m_posY = posY;
		m_Color = BrightCyan;
		fill();
	}
	void IFigure::fill()
	{
		coord.resize(4);

		Square sq(0, 2);
		sq.setColor(m_Color);

		coord[0] = sq;
		sq.setPosition(1, 2); coord[1] = sq;
		sq.setPosition(2, 2); coord[2] = sq;
		sq.setPosition(3, 2); coord[3] = sq;

		m_AxisOfRotation = { 2, 2 };
	}

	void IFigure::rotation()
	{
		for (int i = 0; i < 4; i++)
		{
			std::pair<int, int> prevPoint = coord[i].getPosition();
			coord[i].setPosition(m_AxisOfRotation.first + m_AxisOfRotation.second - prevPoint.second,
				m_AxisOfRotation.second - m_AxisOfRotation.first + prevPoint.first / 2);
		}
	}

	JFigure::JFigure(int posX, int posY)
	{
		m_posX = posX;
		m_posY = posY;
		m_Color = BrightBlue;
		fill();
	}
	void JFigure::fill()
	{
		coord.resize(4);

		Square sq(0, 0);
		sq.setColor(m_Color);

		coord[0] = sq;
		sq.setPosition(0, 1); coord[1] = sq;
		sq.setPosition(1, 1); coord[2] = sq;
		sq.setPosition(2, 1); coord[3] = sq;

		m_AxisOfRotation = { 1, 1 };
	}

	void JFigure::rotation() 
	{
		for (int i = 0; i < 4; i++)
		{
			std::pair<int, int> prevPoint = coord[i].getPosition();
			coord[i].setPosition(m_AxisOfRotation.first + m_AxisOfRotation.second - prevPoint.second,
				m_AxisOfRotation.second - m_AxisOfRotation.first + prevPoint.first / 2);
		}
	}

	TFigure::TFigure(int posX, int posY)
	{
		m_posX = posX;
		m_posY = posY;
		m_Color = BrightMagenta;
		fill();
	}
	void TFigure::fill()
	{
		coord.resize(4);

		Square sq(0, 1);
		sq.setColor(m_Color);

		coord[0] = sq;
		sq.setPosition(1, 1); coord[1] = sq;
		sq.setPosition(2, 1); coord[2] = sq;
		sq.setPosition(1, 2); coord[3] = sq;

		m_AxisOfRotation = { 1, 1 };
	}

	void TFigure::rotation() 
	{
		for (int i = 0; i < 4; i++)
		{
			std::pair<int, int> prevPoint = coord[i].getPosition();
			coord[i].setPosition(m_AxisOfRotation.first + m_AxisOfRotation.second - prevPoint.second,
				m_AxisOfRotation.second - m_AxisOfRotation.first + prevPoint.first / 2);
		}
	}
} // Tetris