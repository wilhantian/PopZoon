#include "FlyScore.h"
//----------------------------------------
USING_NS_CC;
//----------------------------------------
const int ActionTag = 1000;
//----------------------------------------
FlyScore* FlyScore::create()
{
	// 从池中获取
	if (!m_flyScorePool.empty())
	{
		FlyScore* buf = m_flyScorePool.at(m_flyScorePool.size() - 1);
		buf->setScale(1);
		buf->retain();
		m_flyScorePool.erase(m_flyScorePool.size() - 1);
		buf->autorelease();
		
		return buf;
	}

	FlyScore* fc = new FlyScore();
	if (fc && fc->init())
	{
		fc->autorelease();
		return fc;
	}
	CC_SAFE_DELETE(fc);
	return NULL;
}
//----------------------------------------
void FlyScore::setScore(std::string score)
{
	m_label->setString(score);
}
//----------------------------------------
std::string FlyScore::getScore()
{
	return m_label->getString();
}
//----------------------------------------
void FlyScore::setColor(Color3B& color)
{
	m_label->setColor(color);
}
//----------------------------------------
void FlyScore::setFontSize(float size)
{
	m_label->setSystemFontSize(size);
}
//----------------------------------------
void FlyScore::setStartPos(Vec2& pos)
{
	m_startPos = pos;
}
//----------------------------------------
void FlyScore::setEndPos(Vec2& pos)
{
	m_endPos = pos;
}
//----------------------------------------
void FlyScore::setSpeed(float speed)
{
	m_speed = speed;
}
//----------------------------------------
void FlyScore::startMove()
{
	this->setPosition(m_startPos);

	// 计算时间
	float distance = m_startPos.getDistance(m_endPos);
	float time	   = distance / m_speed;

	MoveTo*    mt	   = MoveTo::create(time, m_endPos);
	ScaleTo*   st		= ScaleTo::create(time, 0.5);
	CallFuncN* func	   = CallFuncN::create([=](Node* pSender)
	{
		if (m_flyScorePool.size() < 20)
		{
			m_flyScorePool.pushBack((FlyScore*)pSender);
		}

		pSender->removeFromParent();
	});

	Sequence* sequence = Sequence::createWithTwoActions(Spawn::createWithTwoActions(mt, st), func);
	sequence->setTag(ActionTag);

	this->runAction(sequence);
}
//----------------------------------------
void FlyScore::endMove()
{
	this->stopActionByTag(ActionTag);
}
//----------------------------------------
bool FlyScore::init()
{
	if (!Node::init())
	{
		return false;
	}

	m_label = Label::createWithBMFont("123.fnt", "+1234567890");
	m_particle = ParticleSystemQuad::create("Effect/particle_texture.plist");

	this->addChild(m_label);
	this->addChild(m_particle);

	return true;
}
//----------------------------------------
cocos2d::Vector<FlyScore*> FlyScore::m_flyScorePool;
//----------------------------------------