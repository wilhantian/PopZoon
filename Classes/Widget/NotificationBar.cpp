#include "NotificationBar.h"

#include "ui/UIScale9Sprite.h"

USING_NS_CC;
using namespace ui;

//=========================================================================
NotificationBar* NotificationBar::create(std::string strBackground, std::string strIconPath, std::string strTitle, std::string strContent)
{
	NotificationBar* pBar = new NotificationBar();
	if (pBar && pBar->init(strBackground, strIconPath, strTitle, strContent))
	{
		pBar->autorelease();
		return pBar;
	}

	CC_SAFE_DELETE(pBar);
	return NULL;
}
//=========================================================================
bool NotificationBar::init(std::string strBackground, std::string strIconPath, std::string strTitle, std::string strContent)
{
	if (!Node::init())
	{
		return false;
	}

	Scale9Sprite* pBackground = Scale9Sprite::create(strBackground);
	pBackground->setScale9Enabled(true);
	pBackground->setCapInsets(Rect(10, 10, 80, 80));
	pBackground->setContentSize(Size(450, 72));
	this->addChild(pBackground);

	Sprite* pIcon		= Sprite::create(strIconPath);
	pIcon->setPosition(pIcon->getContentSize().width / 2 + 20, pBackground->getContentSize().height / 2);
	pBackground->addChild(pIcon);

	Label*  pTitle		= Label::createWithSystemFont(strTitle, "", 24);
	pTitle->setAnchorPoint(Vec2(0, 1));
	pTitle->setPosition(pIcon->getPositionX() + pIcon->getContentSize().width / 2 + 20, pBackground->getContentSize().height - 6);
	pBackground->addChild(pTitle);

	Label*  pContent	= Label::createWithSystemFont(strContent, "", 22);
	pContent->setAnchorPoint(Vec2(0, 1));
	pContent->setPosition(pTitle->getPositionX(), pTitle->getPositionY() - pTitle->getContentSize().height);
	pBackground->addChild(pContent);

	this->setContentSize(pBackground->getContentSize());

	return true;
}
//=========================================================================
//=========================================================================
NotificationManager* NotificationManager::pInstance = NULL;
//=========================================================================
NotificationManager* NotificationManager::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new NotificationManager();
	}
	return pInstance;
}
//=========================================================================
void NotificationManager::notify(NotificationBar* pNotificationBar)
{
	Size visibleSize			= Director::getInstance()->getVisibleSize();
	Size notificationBarSize	= pNotificationBar->getContentSize();

	pNotificationBar->setPosition(visibleSize.width / 2, visibleSize.height + notificationBarSize.height / 2);

	Director::getInstance()->getRunningScene()->addChild(pNotificationBar);

	float pDelay = 0;

	NotificationBar* pLastBar = NULL;

	log("%d", m_vBars.size());

	if (m_vBars.size() > 0)
		pLastBar = m_vBars.at(m_vBars.size()-1);

	if (pLastBar)
	{
		Sequence* pSequence = (Sequence*)pLastBar->getActionByTag(255);
		if (pSequence)
			pDelay = pSequence->getDuration() - pSequence->getElapsed();
	}

	Sequence* pSequence = Sequence::create(
			DelayTime::create(pDelay),
			MoveBy::create(0.2, Vec2(0, -notificationBarSize.height)),
			DelayTime::create(3),
			MoveBy::create(0.2, Vec2(0, notificationBarSize.height)),
			RemoveSelf::create(),
			CallFunc::create([=]()
			{
				m_vBars.erase(0);
			}),
			NULL
		);
	pSequence->setTag(255);

	pNotificationBar->runAction(pSequence);

	m_vBars.pushBack(pNotificationBar);
}
//=========================================================================
