#include "BombParticle.h"
//-----------------------------------------
USING_NS_CC;
//-----------------------------------------
BombParticle* BombParticle::create(int iType)
{
	if (!s_poll[iType ].empty())
	{
		BombParticle* buf = s_poll[iType].at(s_poll[iType].size() - 1);
		buf->init(iType);
		buf->retain();
		s_poll[iType].erase(s_poll[iType].size() - 1);
		buf->autorelease();
		return buf;
	}

	BombParticle* bp = new BombParticle();
	if (bp && bp->init(iType))
	{
		bp->autorelease();
		return bp;
	}
	CC_SAFE_DELETE(bp);
	return NULL;
}
//-----------------------------------------
bool BombParticle::init(int iType)
{
	char cType[56];
	sprintf(cType, "%d", iType);
	if (!ParticleSystemQuad::initWithFile("Effect/" + std::string(cType) + ("/particle_texture.plist")))
	{
		return false;
	}

	m_iType = iType;

	this->setAutoRemoveOnFinish(true);

	return true;
}
//-----------------------------------------
void BombParticle::onExit()
{
	if (s_poll[m_iType].size() < 20)
	{
		log("%d", s_poll[m_iType].size());
		s_poll[m_iType].pushBack(this);
	}

	ParticleSystemQuad::onExit();
}
//-----------------------------------------
Vector<BombParticle*> BombParticle::s_poll[5];
//-----------------------------------------
