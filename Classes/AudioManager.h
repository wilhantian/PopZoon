#ifndef _AUDIO_MANAGER_H_
#define _AUDIO_MANAGER_H_

#include "cocos2d.h"
#include "AudioEngine.h"

class AudioManager
{
public:
	static AudioManager* getInstance();
	static void destoryInstance();

public:
	void playWelcomeMusic();

private:
	static AudioManager* m_pInstance;
};

#endif