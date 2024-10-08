#include "Application.h"
#include "Sound/Sound.h"

namespace Tetris
{
	Timer Application::pastTime;
	Timer Application::TimeInGame;

	Application::Application(const ApplicationSpecification& spec)
		: m_Spec(spec)
	{
		RenderConsole();

		GameData::getInstance().loadUserData();

		setupInputHandling();
	}

	void Application::Run()
	{

		pastTime.reset();
		m_Game = std::make_unique<Game>();

		Sound::setMusicVolume(GameData::getInstance().musicVolume);
		Sound::setSoundVolume(GameData::getInstance().soundVolume);

		Sounds::SplashcreenTheme.play();
				
		while (true)
		{
			Loop();
		}
	}

	void Application::Loop()
	{
		Update();
		Render();
	}

	void Application::Update()
	{
		m_Game->update(0.0167f);
	}

	void Application::Render()
	{
		m_Game->render();
	}

	void Application::RenderConsole()
	{
		ConsoleManager::getInstance().SetSize(m_Spec.Width, m_Spec.Height);
		ConsoleManager::getInstance().SetTitle(m_Spec.Title);
		ConsoleManager::getInstance().SetCursorVisibility(false);
		ConsoleManager::getInstance().DisableScrollbars();
		ConsoleManager::getInstance().SetFontSize(m_Spec.Scale, m_Spec.Scale);
		ConsoleManager::getInstance().DisableResize();
	}

}
