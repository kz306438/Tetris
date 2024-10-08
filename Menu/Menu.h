#pragma once

namespace Tetris
{
	class Menu
	{
	public:
		virtual ~Menu() = default;

		virtual void update(float ts) {}
		virtual void render() {}
	};

} // Tetris
