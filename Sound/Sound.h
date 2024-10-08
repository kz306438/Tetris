#pragma once

#include <SFML/Audio.hpp>
#include <string>
#include <unordered_map>

namespace Tetris
{

    class Sound {
    public:
        Sound(const std::string& filename, bool stream = false);
        void play();
        void stop();
        void pause();
        void setLoop(bool loop);
        void setVolume(float volume);
        static void setMusicVolume(float volume);
        static void setSoundVolume(float volume);

    private:
        bool loadFromFile(const std::string& filename, bool stream);

    private:
        std::string m_Filename;
        bool isStreaming;
        sf::Music m_Music;
        sf::SoundBuffer m_Buffer;
        sf::Sound m_Sound;
    };

    namespace Sounds
    {
        inline Sound ATypeGameTheme("res/sounds/A-TypeGameTheme.mp3", true);
        inline Sound BTypeGameTheme("res/sounds/B-TypeGameTheme.mp3", true);
        inline Sound CTypeGameTheme("res/sounds/C-TypeGameTheme.mp3", true);

        inline Sound ATypeMenuTheme("res/sounds/A-TypeMenuTheme.mp3", true);
        inline Sound BTypeMenuTheme("res/sounds/B-TypeMenuTheme.mp3", true);
        inline Sound CTypeMenuTheme("res/sounds/C-TypeMenuTheme.mp3", true);

        inline Sound SplashcreenTheme("res/sounds/splashscreen_theme.mp3", true);
        inline Sound StatsTheme("res/sounds/StatsTheme.mp3", true);

        inline Sound FallSound("res/sounds/FallSound.mp3");
        inline Sound BrickSound("res/sounds/BrickSound.mp3");
        inline Sound DeadLineSound("res/sounds/DeadLineSound.mp3");
        inline Sound GameOverSound("res/sounds/GameOverSound.mp3");
        inline Sound WinSound("res/sounds/WinSound.mp3");

        inline Sound* MusicCurrentlyPlaying = nullptr;

        inline std::unordered_map<char, Sound*> GameThemes =
        {
            {'A', &ATypeGameTheme},
            {'B', &BTypeGameTheme},
            {'C', &CTypeGameTheme}
        };

        inline std::unordered_map<char, Sound*> MenuThemes =
        {
            {'A', &ATypeMenuTheme},
            {'B', &BTypeMenuTheme},
            {'C', &CTypeMenuTheme}
        };
    }

} // Tetris
