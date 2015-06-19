#include "HelloWorldScene.h"
#include "Zoo.h"
#include "Zoon.h"

#include "ScoreLabelAtlas.h"

#include "Widget/JellyButton.h"
#include "Widget/NotificationBar.h"

#include "AudioManager.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	//=========================================
	// 背景
	//=========================================
	Sprite* pBk = Sprite::create("bk.png");
	pBk->setPosition(visibleSize / 2);
	addChild(pBk);

	//=========================================
	// 动物园
	//=========================================
	Zoo* pZoo = Zoo::create(10, 10);
	pZoo->setAnchorPoint(Vec2(0.5, 0.5));
	pZoo->setPosition(Vec2(320, 960/2 - 64/2));
	addChild(pZoo);

	pZoo->setSpace(5);
	
	//=========================================
	// 果冻效果测试
	//=========================================
	Menu* pMenu = Menu::create();
	pMenu->setPosition(0, 0);
	addChild(pMenu);

	JellyButton* pButton = JellyButton::create("yellow_button01.png", nullptr);
	pButton->setPosition(visibleSize / 2);
	pMenu->addChild(pButton);

	pButton->setCallback([=](Ref* pSender)
	{
		NotificationBar* bar = NotificationBar::create("green_panel.png", "yellow_boxCross.png", "Test", "1111111111111111111");
		NotificationManager::getInstance()->notify(bar);
	});

	//=========================================
	// 音乐测试
	//=========================================
	AudioManager::getInstance()->playWelcomeMusic();

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::onEnterTransitionDidFinish()
{
	//=========================================
	// 通知效果测试
	//=========================================
	
}
