#include "AudioManager.h"

AudioManager* AudioManager::sInstance = nullptr;

AudioManager* AudioManager::Instance()
{
	if (sInstance == nullptr)
		sInstance = new AudioManager();

	return sInstance;
}

void AudioManager::Release()
{
	delete sInstance;
	sInstance = nullptr;
}

AudioManager::AudioManager()
{
	mAssetManager = AssetManager::Instance();

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
		std::cout << "Mixer Initialization Error: " << Mix_GetError() << std::endl;

	Mix_Volume(0, MIX_MAX_VOLUME * 0.75f); //Sound of ship losing/gaining shield
	Mix_Volume(1, MIX_MAX_VOLUME * 0.25f); //Sound of ship getting hit by meteor
	Mix_Volume(2, MIX_MAX_VOLUME); //Sound of shooting and ship blowing up to max volume
}

AudioManager::~AudioManager()
{
	mAssetManager = nullptr;
	Mix_Quit();
}

void AudioManager::PlayMusic(std::string filename, int loops)
{
	Mix_PlayMusic(mAssetManager->GetMusic("Audio/" + filename), loops);
}

void AudioManager::PauseMusic()
{
	if (Mix_PlayingMusic() != 0)
		Mix_PauseMusic();
}

void AudioManager::ResumeMusic()
{
	if (Mix_PausedMusic() != 0)
		Mix_ResumeMusic();
}

void AudioManager::PlaySFX(std::string filename, int loops, int channel)
{
	Mix_PlayChannel(channel, mAssetManager->GetSFX("Audio/" + filename), loops);
}