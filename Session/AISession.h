#pragma once

#include "Session.h"
#include "../consoleGUI/GUI.h"

namespace Tetris
{
	class Game;

	class AISession : public Session
	{
	public:

		AISession(Game& game);

		void update() override;
		void render() override;

	private:
		void setupButtons();
	
	private:
		std::unique_ptr<SliderButton> m_SBSpeed;

	};

} // Tetris