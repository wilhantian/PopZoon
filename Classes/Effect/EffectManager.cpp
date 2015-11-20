#include "EffectManager.h"
#include "Effect/BombParticle.h"
#include "Widget/FlyScore.h"
#include "Event/MsgEvent.h"
#include "View/Zoo.h"
#include "View/Zoon.h"
#include "Audio/AudioManager.h"
//----------------------------------------------
USING_NS_CC;
//----------------------------------------------
EffectManager* EffectManager::s_instance = NULL;
//----------------------------------------------
EffectManager* EffectManager::getInstance()
{
	if (s_instance == NULL)
	{
		s_instance = new EffectManager();
		s_instance->init();
	}
	return s_instance;
}
//----------------------------------------------
void EffectManager::destoryInstance()
{
	MsgEvent::removeEvent(MsgOnOnePoped);

	CC_SAFE_DELETE(s_instance);
}
//----------------------------------------------
void EffectManager::init()
{
	for (int i = 0; i < 10; i++)
	{
		BombParticle::create(0);
		BombParticle::create(1);
		BombParticle::create(2);
		BombParticle::create(3);
		BombParticle::create(4);
	}
}
//----------------------------------------------
void EffectManager::playBombEffect(Node* pSender)
{
	//-------------------------
	// 音效
	AudioManager::getInstance()->playPop();

	Size size = Director::getInstance()->getVisibleSize();
	Zoon* zoon = (Zoon*)pSender;
	int type = zoon->getType();
	Vec2 pos =  zoon->convertToWorldSpace(zoon->getAnchorPointInPoints());
    
    //-------------------------
    // 爆炸动画
    Sprite* pBmob = Sprite::create("bmob.png");
    pBmob->setPosition(pos);
    pBmob->setScale(0.3);
    Director::getInstance()->getRunningScene()->addChild(pBmob);
    
    EaseOut* pBombScale = EaseOut::create(ScaleTo::create(0.3, 1.2), 1);
    EaseOut* pBombFade  = EaseOut::create(FadeTo::create(0.3, 0), 1);
    Spawn* pSpawn       = Spawn::create(pBombScale, pBombFade, NULL);
    Sequence* pSequence = Sequence::create(pSpawn, CallFuncN::create([=](Node* node)
    {
        node->removeFromParent();
    }), NULL);
    
    pBmob->runAction(pSequence);
    
	//-------------------------
	// 爆炸粒子
	BombParticle* bomb = BombParticle::create(type);
	bomb->setPosition(pos);
	Director::getInstance()->getRunningScene()->addChild(bomb);
}
//----------------------------------------------
void EffectManager::playFlyScore(cocos2d::Node* pSender, int iScore)
{
	Size size = Director::getInstance()->getVisibleSize();
	Zoon* zoon = (Zoon*)pSender;
	Vec2 pos = zoon->convertToWorldSpace(zoon->getAnchorPointInPoints());
    Vec2 endPos = Vec2(size.width / 2, size.height);
    
	char cScore[28];
	sprintf(cScore, "%d", iScore);

	//-------------------------
	// 飘字特效
	FlyScore* pFlyScore = FlyScore::create();
	pFlyScore->setScore(cScore);
	pFlyScore->setFontSize(32);
	pFlyScore->setStartPos(pos);
    pFlyScore->setEndPos(endPos);
	pFlyScore->setSpeed(750);
	Director::getInstance()->getRunningScene()->addChild(pFlyScore);

	pFlyScore->startMove();
}
//----------------------------------------------