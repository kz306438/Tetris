#include "Sound.h"
#include <iostream>

namespace Tetris
{
    Sound::Sound(const std::string& filename, bool stream)
        : m_Filename(filename), isStreaming(stream) {
        if (!loadFromFile(filename, stream)) {
            std::cerr << "Error loading audio from file: " << filename << std::endl;
        }
    }

    bool Sound::loadFromFile(const std::string& filename, bool stream) {
        if (stream) {
            if (!m_Music.openFromFile(filename)) {
                std::cerr << "Error loading music from file: " << filename << std::endl;
                return false;
            }
        }
        else {
            if (!m_Buffer.loadFromFile(filename)) {
                std::cerr << "Error loading sound from file: " << filename << std::endl;
                return false;
            }
            m_Sound.setBuffer(m_Buffer);
        }

        return true;
    }

    void Sound::play() {
        if (isStreaming) {
            m_Music.play();
            Sounds::MusicCurrentlyPlaying = this;
        }
        else {
            m_Sound.play();
        }
    }

    void Sound::stop() {
        if (isStreaming) {
            m_Music.stop();
            Sounds::MusicCurrentlyPlaying = nullptr;
        }
        else {
            m_Sound.stop();
        }
    }

    void Sound::pause()
    {
        if (isStreaming) {
            m_Music.pause();
        }
        else {
            m_Sound.pause();
        }
    }

    void Sound::setLoop(bool loop)
    {
        if (isStreaming) {
            m_Music.setLoop(loop);
        }
        else {
            m_Sound.setLoop(loop);
        }
    }

    void Sound::setVolume(float volume)
    {
        if (isStreaming) {
            m_Music.setVolume(volume);
        }
        else {
            m_Sound.setVolume(volume);
        }
    }

    void Sound::setMusicVolume(float volume)
    {
        Sounds::ATypeGameTheme.setVolume(volume);
        Sounds::BTypeGameTheme.setVolume(volume);
        Sounds::CTypeGameTheme.setVolume(volume);

        Sounds::ATypeMenuTheme.setVolume(volume);
        Sounds::BTypeMenuTheme.setVolume(volume);
        Sounds::CTypeMenuTheme.setVolume(volume);

        Sounds::SplashcreenTheme.setVolume(volume);
        Sounds::StatsTheme.setVolume(volume);
    }

    void Sound::setSoundVolume(float volume)
    {
        Sounds::FallSound.setVolume(volume);
        Sounds::BrickSound.setVolume(volume);
        Sounds::DeadLineSound.setVolume(volume);
        Sounds::WinSound.setVolume(volume);
        Sounds::GameOverSound.setVolume(volume);
    }


} // Tetris