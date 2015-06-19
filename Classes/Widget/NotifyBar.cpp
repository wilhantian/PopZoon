#include "NotifyBar.h"

USING_NS_CC;
using namespace ui;

NotifyBar* NotifyBar::create(std::string strBackgoundPath, std::string strTitle, std::string strContent, std::string strIconPath)
{
	NotifyBar* pBar = new NotifyBar();
	if (pBar && pBar->init(strBackgoundPath, strTitle, strContent, strIconPath))
	{
		pBar->autorelease();
		return pBar;
	}
	CC_SAFE_DELETE(pBar);
	return NULL;
}

bool NotifyBar::init(std::string strBackgoundPath, std::string strTitle, std::string strContent, std::string strIconPath)
{
	if (!Node::init())
	{
		return false;
	}

	//=================================================================
	// 背景
	//=================================================================
	Scale9Sprite* pBackgound = Scale9Sprite::create(strBackgoundPath);
	pBackgound->setScale9Enabled(true);
	pBackgound->setCapInsets(Rect(10, 10, 80, 80));
	pBackgound->setContentSize(Size(450, 72));
	addChild(pBackgound);

	//重置该节点大小
	setContentSize(pBackgound->getContentSize());

	//=================================================================
	// 图标
	//=================================================================
	Sprite* pIcon = Sprite::create(strIconPath);
	pIcon->setPosition( pIcon->getContentSize().width / 2 + 20, pBackgound->getContentSize().height / 2);
	pBackgound->addChild(pIcon);

	//=================================================================
	// 标题
	//=================================================================
	LabelTTF* pLabelTitle = LabelTTF::create(strTitle, "font", 28);
	pLabelTitle->setAnchorPoint(Vec2(0, 1));
	pLabelTitle->setPosition(pIcon->getPositionX() + pIcon->getContentSize().width / 2 + 20, pBackgound->getContentSize().height - 6);
	pBackgound->addChild(pLabelTitle);

	//=================================================================
	// 内容
	//=================================================================
	LabelTTF* pLabelContent = LabelTTF::create(strContent, "font", 22);
	pLabelContent->setAnchorPoint(Vec2(0, 1));
	pLabelContent->setPosition(pLabelTitle->getPositionX(), pLabelTitle->getPositionY() - pLabelTitle->getContentSize().height);
	pBackgound->addChild(pLabelContent);


	return true;
}