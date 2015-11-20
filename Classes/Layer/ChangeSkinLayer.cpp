#include "ChangeSkinLayer.h"
#include "ui/UIButton.h"
#include "ui/UIImageView.h"
#include "ui/UILayout.h"
#include "cocos-ext.h"
//---------------------------------------
USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;
//---------------------------------------
#define BUTTON_LEFT  1
#define BUTTON_RIGHT 2
//---------------------------------------
bool ChangeSkinLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size winSize	 = Director::getInstance()->getWinSize();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin		 = Director::getInstance()->getVisibleOrigin();

	// 截断事件传递
	EventListenerTouchOneByOne* eve = EventListenerTouchOneByOne::create();
	eve->setSwallowTouches(true);
	eve->onTouchBegan = [](Touch* t, Event* e)
	{
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eve, this);

	// 面板
	Sprite* pPlane = Sprite::create(RES::SKIN_PLANE);
	pPlane->setPosition(origin + visibleSize / 2);
	this->addChild(pPlane);

	// 滚动层
	m_pPageView = PageView::create();
	m_pPageView->setAnchorPoint(Vec2(0.5, 0.5));
	m_pPageView->setPosition(Vec2(226, 240));
	m_pPageView->setContentSize(Size(350, 350));
	m_pPageView->setCustomScrollThreshold(60);		// 60px 翻页
	m_pPageView->addEventListener(CC_CALLBACK_2(ChangeSkinLayer::onPageChange, this));
	pPlane->addChild(m_pPageView);

	// 关闭按钮
	Button* pBtnClose = Button::create(RES::SKIN_CLOSE, RES::SKIN_CLOSE1);
	pBtnClose->setAnchorPoint(Vec2(0.6, 1));
	pBtnClose->setPosition(pPlane->getContentSize());
	pBtnClose->addClickEventListener(CC_CALLBACK_1(ChangeSkinLayer::onCloseButtonClick, this));
	pPlane->addChild(pBtnClose);

	// 左侧按钮
	m_pBtnLeft = Button::create(RES::SKIN_LEFT_BUTTON, RES::SKIN_LEFT_BUTTON1);
	m_pBtnLeft->setPosition(Vec2(0, pPlane->getContentSize().height/2));
	m_pBtnLeft->addClickEventListener(CC_CALLBACK_1(ChangeSkinLayer::onSelectButtonClick, this));
	m_pBtnLeft->setTag(BUTTON_LEFT);
	pPlane->addChild(m_pBtnLeft);

	// 右侧按钮
	m_pBtnRight = Button::create(RES::SKIN_RIGHT_BUTTON, RES::SKIN_RIGHT_BUTTON1);
	m_pBtnRight->setPosition(Vec2(pPlane->getContentSize().width, pPlane->getContentSize().height / 2));
	m_pBtnRight->addClickEventListener(CC_CALLBACK_1(ChangeSkinLayer::onSelectButtonClick, this));
	m_pBtnRight->setTag(BUTTON_RIGHT);
	pPlane->addChild(m_pBtnRight);

	// 下载按钮
	m_pBtnDown = Button::create(RES::SKIN_DOWN_BUTTON, RES::SKIN_DOWN_BUTTON1);
	m_pBtnDown->setPosition(Vec2(pPlane->getContentSize().width/2, 0));
	pPlane->addChild(m_pBtnDown);


	//==========================
	// test
	addSkin("HomeScene/TEST_1.png");
	addSkin("HomeScene/TEST_2.png"); 
	addSkin("HomeScene/TEST_3.png");

	checkPageIndex();

	// 播放动画
	pPlane->setScaleX(0);
	pPlane->setScaleY(0.5);

	ScaleTo* pActionScale = ScaleTo::create(0.32, 1);
	pPlane->runAction(EaseBackOut::create(pActionScale));

	/*
	AssetsManagerEx* ex = AssetsManagerEx::create("Manifest/project.manifest", "E:/aaaaaa");
	ex->retain();

	EventListenerAssetsManagerEx* exListener = EventListenerAssetsManagerEx::create(ex, [=](EventAssetsManagerEx* event)
	{
		switch (event->getEventCode())
		{
		case EventAssetsManagerEx::EventCode::ERROR_NO_LOCAL_MANIFEST:
			log("ERROR_NO_LOCAL_MANIFEST");
			break;
		case EventAssetsManagerEx::EventCode::ERROR_DOWNLOAD_MANIFEST:
			log("ERROR_DOWNLOAD_MANIFEST");
			break;
		case EventAssetsManagerEx::EventCode::ERROR_PARSE_MANIFEST:
			log("ERROR_PARSE_MANIFEST");
			break;
		case EventAssetsManagerEx::EventCode::NEW_VERSION_FOUND:
			log("NEW_VERSION_FOUND");
			break;
		case EventAssetsManagerEx::EventCode::ALREADY_UP_TO_DATE:
			log("ALREADY_UP_TO_DATE");
			break;
		case EventAssetsManagerEx::EventCode::UPDATE_PROGRESSION:
			log("download %f", event->getPercent());
			break;
		case EventAssetsManagerEx::EventCode::ASSET_UPDATED:
			log("ASSET_UPDATED");
			break;
		case EventAssetsManagerEx::EventCode::ERROR_UPDATING:
			log("ERROR_UPDATING");
			break;
		case EventAssetsManagerEx::EventCode::UPDATE_FINISHED:
			log("UPDATE_FINISHED");
			break;
		case EventAssetsManagerEx::EventCode::UPDATE_FAILED:
			log("UPDATE_FAILED");
			break;
		case EventAssetsManagerEx::EventCode::ERROR_DECOMPRESS:
			log("ERROR_DECOMPRESS");
			break;
		}
	});

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(exListener, this);

	ex->update();
	*/

	return true;
}
//---------------------------------------
void ChangeSkinLayer::addSkin(std::string strImagePath)
{
	Layout* pLayout = Layout::create();
	pLayout->setContentSize(Size(350, 350));
	m_pPageView->addPage(pLayout);

	ImageView* pImageView = ImageView::create(strImagePath);
	pImageView->setPosition(pLayout->getContentSize()/2);
	pLayout->addChild(pImageView);
}
//---------------------------------------
void ChangeSkinLayer::onSelectButtonClick(cocos2d::Ref* pSender)
{
	Button* pButton = (Button*)pSender;

	// 左按钮
	if (pButton->getTag() == BUTTON_LEFT)
	{
		m_pPageView->scrollToPage(m_pPageView->getCurPageIndex() - 1);
	}

	// 右按钮
	else if (pButton->getTag() == BUTTON_RIGHT)
	{
		m_pPageView->scrollToPage(m_pPageView->getCurPageIndex() + 1);
	}
}
//---------------------------------------
void ChangeSkinLayer::checkPageIndex()
{
	ssize_t curIndex = m_pPageView->getCurPageIndex();

	if (curIndex == 0)
	{
		m_pBtnLeft->setVisible(false);
	}
	else
	{
		m_pBtnLeft->setVisible(true);
	}

	if (curIndex + 1 >= m_pPageView->getPages().size())
	{
		m_pBtnRight->setVisible(false);
	}
	else
	{
		m_pBtnRight->setVisible(true);
	}
}
//---------------------------------------
void ChangeSkinLayer::onPageChange(cocos2d::Ref* pSender, cocos2d::ui::PageView::EventType eventType)
{
	// 翻页完成
	if (eventType == PageView::EventType::TURNING)
	{
		checkPageIndex();
	}
}
//---------------------------------------
void ChangeSkinLayer::onCloseButtonClick(cocos2d::Ref* pSender)
{
	this->removeFromParent();
}
//---------------------------------------