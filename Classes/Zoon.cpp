#include "Zoon.h"

USING_NS_CC;

Zoon::Zoon() :
m_state(ZoonState::Normal),
m_isDestory(false)
{

}

Zoon::~Zoon()
{

}

Zoon* Zoon::create(int iType)
{
	Zoon* zoon = new Zoon();
	if (zoon && zoon->init(iType))
	{
		zoon->autorelease();
		return zoon;
	}
	CC_SAFE_DELETE(zoon);
	return NULL;
}

bool Zoon::init(int iType)
{
	if (!Sprite::init())
	{
		return false;
	}

	m_iType = iType;

	char cBufferNormal[56];
	sprintf(cBufferNormal, "%d.png", iType);
	m_strNormalFileName = cBufferNormal;
	
	char cBufferSelete[56];
	sprintf(cBufferSelete, "%d_sel.png", iType);
	m_strSeleteFileName = cBufferSelete;

	//设置纹理
	setState(m_state);

	return true;
}

void Zoon::onEnterTransitionDidFinish()
{
	setScale(0);
	ScaleTo* pScale = ScaleTo::create(0.4, 1);
	runAction(pScale);
}

void Zoon::setState(ZoonState state)
{
	switch (state)
	{
	case ZoonState::Normal:
		setTexture(m_strNormalFileName);
		break;
	case ZoonState::Select:
		setTexture(m_strSeleteFileName);
		break;
	default:
		break;
	}
}

ZoonState Zoon::getState()
{
	return m_state;
}

void Zoon::destory()
{
	//设置销毁标识
	m_isDestory = true;

	//播放动画
	//todo

	//销毁实例
	removeFromParent();
}

bool Zoon::isDestory()
{
	return m_isDestory;
}

void Zoon::hint()
{
	ScaleTo* pMinScale = ScaleTo::create(0.7, 0.9);
	ScaleTo* pMaxScale = ScaleTo::create(0.7, 1);
	Sequence* pSequence = Sequence::createWithTwoActions(pMinScale, pMaxScale);

	runAction(RepeatForever::create(pSequence));
}

int Zoon::getType()
{
	return m_iType;
}