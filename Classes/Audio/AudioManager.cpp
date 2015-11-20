#include "AudioManager.h"

USING_NS_CC;
using namespace experimental;

AudioManager* AudioManager::m_pInstance = NULL;

AudioManager* AudioManager::getInstance()
{
	if (m_pInstance == NULL)
	{
		m_pInstance = new AudioManager();
	}
	return m_pInstance;
}

void AudioManager::destoryInstance()
{
	CC_SAFE_DELETE(m_pInstance);
}

void AudioManager::playWelcomeMusic()
{
	AudioEngine::play2d("010614songidea(copycat)_0.mp3", true);
}

void AudioManager::playPop()
{
	AudioEngine::play2d("pop.ogg", false);
}

void AudioManager::playClick()
{
	AudioEngine::play2d("click.mp3", false);
}

