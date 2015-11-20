#include "DialogView.h"
#include "ui/UIButton.h"
#include "ui/UIText.h"
#include "ui/UIListView.h"
#include "RES.h"
//-------------------------------------------
USING_NS_CC;
using namespace ui;
//-------------------------------------------
DialogView* DialogView::create(const std::string& strTitle, const std::string& strContent)
{
	DialogView* dv = new DialogView();
	if (dv && dv->init(strTitle, strContent))
	{
		dv->autorelease();
		return dv;
	}
	CC_SAFE_DELETE(dv);
	return NULL;
}
//-------------------------------------------
bool DialogView::init(const std::string& strTitle, const std::string& strContent)
{
	if (!Node::init())
		return false;

	Size winSize = Director::getInstance()->getWinSize();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 截断事件传递
	EventListenerTouchOneByOne* eve = EventListenerTouchOneByOne::create();
	eve->setSwallowTouches(true);
	eve->onTouchBegan = [](Touch* t, Event* e)
	{
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eve, this);

	// 背景
	Sprite* pPlane = Sprite::create(RES::DIALOG_PLANE);
	pPlane->setPosition(origin + visibleSize / 2);
	this->addChild(pPlane);

	// 确认按钮
	Button* pBtnOK = Button::create(RES::DIALOG_OK);
	pBtnOK->setPosition(Vec2(pPlane->getContentSize().width / 2, 0));
	pBtnOK->addClickEventListener([=](Ref* pS)
	{
		if (onOkButtonClick)
			onOkButtonClick(this);
	});
	pPlane->addChild(pBtnOK);

	// 标题
	Text* pTextTitle = Text::create(strTitle, "", 32);
	pTextTitle->setPosition(Vec2(pPlane->getContentSize().width / 2, pPlane->getContentSize().height - 28));
	pPlane->addChild(pTextTitle);

	// 内容List
	ListView* pListView = ListView::create(); 
	pListView->setAnchorPoint(Vec2(0.5, 0.5));
	pListView->setPosition(Vec2(pPlane->getContentSize().width/2, 146));
	pListView->setContentSize(Size(pPlane->getContentSize().width - 60, 210));
	pListView->setBounceEnabled(true);
	pPlane->addChild(pListView);

	// 内容Text
	Text* pTextContent = Text::create(strContent, "", 26);
	pTextContent->setTextHorizontalAlignment(TextHAlignment::CENTER);
	pTextContent->setTextAreaSize(Size(pListView->getContentSize().width, 0));
	pTextContent->ignoreContentAdaptWithSize(false);
	pListView->pushBackCustomItem(pTextContent);
	
	// 播放动画
	pPlane->setScaleX(0);
	pPlane->setScaleY(0.5);

	ScaleTo* pActionScale = ScaleTo::create(0.35, 1);
	pPlane->runAction(EaseBackOut::create(pActionScale));

	return true;
}
//-------------------------------------------
DialogView::DialogView():
onOkButtonClick(nullptr)
{
}
//-------------------------------------------
void DialogView::addOkButtonClick(const std::function<void(cocos2d::Ref*)>& callback)
{
	onOkButtonClick = callback;
}
//-------------------------------------------