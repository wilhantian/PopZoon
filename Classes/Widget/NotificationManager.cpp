#include "NotificationManager.h"

USING_NS_CC;

NotificationManager* NotificationManager::s_pInstance = NULL;

NotificationManager* NotificationManager::getInstance()
{
	if (s_pInstance == NULL)
	{
		s_pInstance = new NotificationManager();
		s_pInstance->init();
		s_pInstance->autorelease();

		Director::getInstance()->getRunningScene()->addChild(s_pInstance);
	}

	return s_pInstance;
}

void NotificationManager::notification(NotifyBar* pNotifyBar)
{
	if (m_vNotifyBars.empty())
		schedule(CC_SCHEDULE_SELECTOR(NotificationManager::update), 3.5, -1, -3.5);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size notifyBarSize = pNotifyBar->getContentSize();
	
	//ÉèÖÃ×ø±ê
	pNotifyBar->setPosition(visibleSize.width/2, visibleSize.height + notifyBarSize.height/2);

	Director::getInstance()->getRunningScene()->addChild(pNotifyBar);

	m_vNotifyBars.pushBack(pNotifyBar);

	log("%d", m_vNotifyBars.size());

}

bool NotificationManager::init()
{
	if (!Node::init())
	{
		return false;
	}
	
	return true;
}

void NotificationManager::update(float delta)
{
	if (m_vNotifyBars.empty())
		return;

	NotifyBar* pNotifyBar = m_vNotifyBars.at(0);
		
	Size notifyBarSize = pNotifyBar->getContentSize();

	Sequence* pSequence = Sequence::create(
		MoveBy::create(0.2, Vec2(0, -notifyBarSize.height)),
		DelayTime::create(3),
		MoveBy::create(0.2, Vec2(0, notifyBarSize.height)),
		RemoveSelf::create(),
		CallFunc::create([=]()
		{
			m_vNotifyBars.erase(0);
		}),
		NULL
		);
	pNotifyBar->runAction(pSequence);

	
	if (m_vNotifyBars.empty())
		unschedule(CC_SCHEDULE_SELECTOR(NotificationManager::update));
}