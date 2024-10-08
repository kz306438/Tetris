#pragma once

#include "Timer.h"
#include "ConsoleManager.h"
#include "GameData.h"
#include "consoleGUI\GUI.h"
#include "Game.h"

namespace Tetris
{
	struct ApplicationSpecification
	{
		int Width = 73;
		int Height = 30;
		int Scale = 21;
		std::string Title = "Tetris";
	};

	class Application
	{
	public:
		Application(const ApplicationSpecification& spec = ApplicationSpecification());

		void Run();
		void Loop();
		void Update();
		void Render();
		void RenderConsole();
	public:
        static Timer pastTime;
		static Timer TimeInGame;

	private:

		ApplicationSpecification m_Spec;

		std::unique_ptr<Game> m_Game;
	};

} // Tetris
