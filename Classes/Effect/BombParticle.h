#ifndef _BOMB_PRATICLE_H_
#define _BOMB_PRATICLE_H_

#include "cocos2d.h"

class BombParticle : public cocos2d::ParticleSystemQuad
{
public:
	static BombParticle* create(int iType);

protected:
	bool init(int iType);
	virtual void onExit() override;

protected:
	static cocos2d::Vector<BombParticle*> s_poll[5];

	int m_iType;
};

#endif