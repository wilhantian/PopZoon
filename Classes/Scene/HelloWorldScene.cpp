#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	
	Size winSize = Director::getInstance()->getWinSize();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	log("winSize----w:%f, h:%f", winSize.width, winSize.height);
	log("visibleSize----w:%f, h:%f", visibleSize.width, visibleSize.height);
	log("origin----x:%f, y:%f", origin.x, origin.y);

	float factor;
	float factorWidth = winSize.width / visibleSize.width;
	float factorHeight = visibleSize.height / visibleSize.height;

	if (factorHeight > factorWidth)
	{
		factor = factorHeight;
	}
	else
	{
		factor = factorWidth;
	}
	

	//=========================================
	// 背景
	//=========================================
	Sprite* pBk = Sprite::create("bk.png");
	pBk->setPosition(visibleSize / 2);
	addChild(pBk);

	//=========================================
	// 动物园
	//=========================================
	/*
	Zoo* pZoo = Zoo::create(10, 10, NULL);
	pZoo->setAnchorPoint(Vec2(0.5, 0.5));
	pZoo->setPosition(Vec2(320, 960/2 - 64/2));
	pZoo->setSpace(5);
	pZoo->setGameType(Zoo::TIME_LIMIT);
	addChild(pZoo);

	pZoo->setScale(1 / factor);

	log("factor=%f", factor);
	*/

	//=========================================
	// 果冻效果测试
	//=========================================
	/*
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
	*/

	//=========================================
	// 总分
	//=========================================
	ScoreLabelAtlas* sla = ScoreLabelAtlas::create(0, "font.png", 14, 21, '0');
	sla->setPosition(winSize.width / 2, winSize.height - sla->getContentSize().height);
	this->addChild(sla);

	//=========================================
	// 音乐测试
	//=========================================
	//AudioManager::getInstance()->playWelcomeMusic();
	//this->schedule(CC_CALLBACK_1(HelloWorld::update, this), 0.5, "===");

	//=========================================
	// 特效
	//=========================================
	EffectManager::getInstance();

	//=========================================
	// 对白层
	//=========================================
	/*
	LevelInfo levelInfo = LevelManager::getLevelInfo("Level/1.json");
	PrologueLayer* pl = PrologueLayer::create();
	pl->setGameScript(levelInfo.tagPrologueInfos);
	this->addChild(pl);

	pl->startShowTime();
	*/
	
	LevelInfo_1001 levelInfo = LevelManager::getLevelInfoForType1001("Level/1001.json"); 
	PrologueLayer* pl = PrologueLayer::create();
	pl->setGameScript(levelInfo.tagPrologueInfos); 
	this->addChild(pl);
	   
	pl->startShowTime();
	

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

void HelloWorld::update(float delta)
{
	//=========================================
	// 飘字测试
	//=========================================
// 	FlyScore* pFlyScore = FlyScore::create();
// 	pFlyScore->setStartPos(Vec2(0, 0));
// 	pFlyScore->setEndPos(Vec2(500, 500));
// 	pFlyScore->setSpeed(250);
// 	this->addChild(pFlyScore);
// 
// 	pFlyScore->startMove();
}