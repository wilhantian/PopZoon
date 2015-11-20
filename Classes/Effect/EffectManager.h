#ifndef _EFFECT_MANAGER_H_
#define _EFFECT_MANAGER_H_

#include "cocos2d.h"

class EffectManager
{
public:
	static EffectManager* getInstance();
	static void			  destoryInstance();
	
	// 播放爆炸特效
	void playBombEffect(cocos2d::Node* pSender);
	
	// 播放分数特效
	void playFlyScore(cocos2d::Node* pSender, int iScore);

protected:
	void init();

private:
	static EffectManager* s_instance;
};

#endif