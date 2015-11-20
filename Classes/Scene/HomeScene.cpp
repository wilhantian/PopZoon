#include "HomeScene.h"
#include "ui/UIButton.h"
#include "GameScene.h"
#include "Layer/ChangeSkinLayer.h"
#include "View/DialogView.h"
//---------------------------------------------
USING_NS_CC;
using namespace ui;
//---------------------------------------------
const int START_BUTTON_TAG     = 1;
const int ABOUT_BUTTON_TAG     = 2;
const int SKIN_BUTTON_TAG      = 3;
const int COLOR_EGG_BUTTON_TAG = 4;
const int LOGO_TAG             = 5;
//---------------------------------------------
cocos2d::Scene* HomeScene::createScene()
{
    HomeScene* hs = HomeScene::create();
    Scene* scene = Scene::create();
    scene->addChild(hs);
    return scene;
}
//---------------------------------------------
bool HomeScene::init()
{
    if (!LayerColor::initWithColor(Color4B(0, 196, 255, 255)))
        return false;
    
    m_iColorEggCount = 0;
    
    Size winSize = Director::getInstance()->getWinSize();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // 光
    for (int i = 0; i < 24; i++)
    {
        Sprite* pLight = Sprite::create(RES::LIGHT);
        pLight->setAnchorPoint(Vec2(0.5, 0));
        pLight->setPosition(origin + Vec2(visibleSize.width/2, 0));
        pLight->setRotation(i * 15);
        this->addChild(pLight);
        
        RotateBy* pActionRotate = RotateBy::create(120, 360);
        pLight->runAction(RepeatForever::create(pActionRotate));
    }
    
    // 云2
    {
        Button* pCloud = Button::create(RES::CLOUD2);
        pCloud->setPosition(origin + Vec2(168, visibleSize.height - 100));
        pCloud->addClickEventListener(CC_CALLBACK_1(HomeScene::onCloudClick, this));
        pCloud->setTag(COLOR_EGG_BUTTON_TAG);
        this->addChild(pCloud);
        
        MoveBy* pActionMove1 = MoveBy::create(4, Vec2(-35, 0));
        MoveBy* pActionMove2 = pActionMove1->reverse();
        Sequence* pActionSeq = Sequence::createWithTwoActions(
                                                              EaseSineInOut::create(pActionMove1),
                                                              EaseSineInOut::create(pActionMove2)
                                                              );
        pCloud->runAction(RepeatForever::create(pActionSeq));
    }
    // 云3
    {
        Button* pCloud = Button::create(RES::CLOUD3);
        pCloud->setPosition(origin + Vec2(160, visibleSize.height - 390));
        pCloud->addClickEventListener(CC_CALLBACK_1(HomeScene::onCloudClick, this));
        this->addChild(pCloud);
        
        MoveBy* pActionMove1 = MoveBy::create(6, Vec2(30, 0));
        MoveBy* pActionMove2 = pActionMove1->reverse();
        Sequence* pActionSeq = Sequence::createWithTwoActions(
                                                              EaseSineInOut::create(pActionMove1),
                                                              EaseSineInOut::create(pActionMove2)
                                                              );
        pCloud->runAction(RepeatForever::create(pActionSeq));
    }
    
    // 手贱按钮
    {
        Text* pText = Text::create("手贱按钮", "", 48);
        pText->setPosition(origin + Vec2(visibleSize.width / 2, visibleSize.height - 200));
        this->addChild(pText);
        pText->setTouchEnabled(true);
        pText->addClickEventListener([=](Ref* pSender)
        {
            Button* btn = (Button*)this->getChildByTag(START_BUTTON_TAG);
            btn->runAction(EaseBounceIn::create(ScaleTo::create(0.5, 0.2)));
        });
        
        this->schedule([=](float time)
        {
            if(pText->getTextColor() == Color4B::RED)
            {
                pText->setTextColor(Color4B::BLACK);
            }
            else
            {
                pText->setTextColor(Color4B::RED);
            }
        }, 0.23, "pText");

    }
    
    // LOGO
    Button* pLogo = Button::create(RES::LOGO, RES::LOGO);
    pLogo->setPosition(origin + Vec2(visibleSize.width / 2, visibleSize.height - 200));
    pLogo->setTag(LOGO_TAG);
    pLogo->addClickEventListener(CC_CALLBACK_1(HomeScene::onLogoClick, this));
    this->addChild(pLogo);
    
    // 云1
    {
        Button* pCloud = Button::create(RES::CLOUD1);
        pCloud->setPosition(origin + Vec2(500, visibleSize.height - 300));
        pCloud->addClickEventListener(CC_CALLBACK_1(HomeScene::onCloudClick, this));
        this->addChild(pCloud);
        
        MoveBy* pActionMove1 = MoveBy::create(5, Vec2(40, 0));
        MoveBy* pActionMove2 = pActionMove1->reverse();
        Sequence* pActionSeq = Sequence::createWithTwoActions(
                                                              EaseSineInOut::create(pActionMove1),
                                                              EaseSineInOut::create(pActionMove2)
                                                              );
        pCloud->runAction(RepeatForever::create(pActionSeq));
    }
    
    
    // 熊猫
    {
        Sprite* pPanda = Sprite::create(RES::HOMESCENE_PANDA);
        pPanda->setAnchorPoint(Vec2(0.5, 0.2));
        pPanda->setPosition(origin + Vec2(220, 265));
        pPanda->setRotation(10);
        this->addChild(pPanda);
        
        MoveBy* pActionMoveDown1 = MoveBy::create(5, Vec2(0, -40));
        MoveBy* pActionMoveUp1 = pActionMoveDown1->reverse();
        Sequence* pActionSeq1 = Sequence::createWithTwoActions(
                                                               EaseSineInOut::create(pActionMoveDown1),
                                                               EaseSineInOut::create(pActionMoveUp1)
                                                               );
        pPanda->runAction(RepeatForever::create(pActionSeq1));
        
        RotateBy* pActionRotateLeft = RotateBy::create(3, -20);
        RotateBy* pActionRotateRight = RotateBy::create(3, 20);
        Sequence* pActionSeq2 = Sequence::createWithTwoActions(
                                                               EaseSineInOut::create(pActionRotateLeft),
                                                               EaseSineInOut::create(pActionRotateRight)
                                                               );
        pPanda->runAction(RepeatForever::create(pActionSeq2));
    }
    // 河马
    {
        Sprite* pPanda = Sprite::create(RES::HOMESCENE_HIPPO);
        pPanda->setAnchorPoint(Vec2(0.5, 0.1));
        pPanda->setPosition(origin + Vec2(455, 280));
        pPanda->setRotation(10);
        this->addChild(pPanda);
        
        MoveBy* pActionMoveDown1 = MoveBy::create(5, Vec2(0, -40));
        MoveBy* pActionMoveUp1 = pActionMoveDown1->reverse();
        Sequence* pActionSeq1 = Sequence::createWithTwoActions(
                                                               EaseSineInOut::create(pActionMoveDown1),
                                                               EaseSineInOut::create(pActionMoveUp1)
                                                               );
        pPanda->runAction(RepeatForever::create(pActionSeq1));
        
        RotateBy* pActionRotateLeft = RotateBy::create(3, -20);
        RotateBy* pActionRotateRight = RotateBy::create(3, 20);
        Sequence* pActionSeq2 = Sequence::createWithTwoActions(
                                                               EaseSineInOut::create(pActionRotateLeft),
                                                               EaseSineInOut::create(pActionRotateRight)
                                                               );
        pPanda->runAction(RepeatForever::create(pActionSeq2));
    }
    
    {
        // 云
        Sprite* pBigCloud = Sprite::create(RES::BIG_CLOUD3);
        pBigCloud->setAnchorPoint(Vec2(0.5, 0));
        pBigCloud->setPosition(origin + Vec2(visibleSize.width / 2, 0));
        this->addChild(pBigCloud);
        
        MoveBy* pActionMoveDown = MoveBy::create(5, Vec2(0, -30));
        MoveBy* pActionMoveUp   = pActionMoveDown->reverse();
        Sequence* pActionSeq    = Sequence::createWithTwoActions(
                                                                 EaseSineInOut::create(pActionMoveDown),
                                                                 EaseSineInOut::create(pActionMoveUp)
                                                                 );
        pBigCloud->runAction(RepeatForever::create(pActionSeq));
    }
    
    // 兔子
    {
        Sprite* pRabbit = Sprite::create(RES::HOMESCENE_RABBIT);
        pRabbit->setAnchorPoint(Vec2(0.5, 0.2));
        pRabbit->setPosition(origin + Vec2(420, 205));
        pRabbit->setRotation(-10);
        this->addChild(pRabbit);
        
        MoveBy* pActionMoveDown1 = MoveBy::create(5, Vec2(0, -30));
        MoveBy* pActionMoveUp1 = pActionMoveDown1->reverse();
        Sequence* pActionSeq1 = Sequence::createWithTwoActions(
                                                               EaseSineInOut::create(pActionMoveDown1),
                                                               EaseSineInOut::create(pActionMoveUp1)
                                                               );
        pRabbit->runAction(RepeatForever::create(pActionSeq1));
        
        RotateBy* pActionRotateLeft = RotateBy::create(2.8, 20);
        RotateBy* pActionRotateRight = RotateBy::create(2.8, -20);
        Sequence* pActionSeq2 = Sequence::createWithTwoActions(
                                                               EaseSineInOut::create(pActionRotateLeft),
                                                               EaseSineInOut::create(pActionRotateRight)
                                                               );
        pRabbit->runAction(RepeatForever::create(pActionSeq2));
    }
    // 长颈鹿
    {
        Sprite* pRabbit = Sprite::create(RES::HOMESCENE_GIRAFFE);
        pRabbit->setAnchorPoint(Vec2(0.5, 0.1));
        pRabbit->setPosition(origin + Vec2(130, 240));
        pRabbit->setRotation(-12.5);
        this->addChild(pRabbit);
        
        MoveBy* pActionMoveDown1 = MoveBy::create(5, Vec2(0, -30));
        MoveBy* pActionMoveUp1 = pActionMoveDown1->reverse();
        Sequence* pActionSeq1 = Sequence::createWithTwoActions(
                                                               EaseSineInOut::create(pActionMoveDown1),
                                                               EaseSineInOut::create(pActionMoveUp1)
                                                               );
        pRabbit->runAction(RepeatForever::create(pActionSeq1));
        
        RotateBy* pActionRotateLeft = RotateBy::create(3.0, 25);
        RotateBy* pActionRotateRight = RotateBy::create(3.0, -25);
        Sequence* pActionSeq2 = Sequence::createWithTwoActions(
                                                               EaseSineInOut::create(pActionRotateLeft),
                                                               EaseSineInOut::create(pActionRotateRight)
                                                               );
        pRabbit->runAction(RepeatForever::create(pActionSeq2));
    }
    
    {
        Sprite* pBigCloud = Sprite::create(RES::BIG_CLOUD2);
        pBigCloud->setAnchorPoint(Vec2(0.5, 0));
        pBigCloud->setPosition(origin + Vec2(visibleSize.width / 2, 0));
        this->addChild(pBigCloud);
        
        MoveBy* pActionMoveDown = MoveBy::create(6, Vec2(0, -25));
        MoveBy* pActionMoveUp = pActionMoveDown->reverse();
        Sequence* pActionSeq = Sequence::createWithTwoActions(
                                                              EaseSineInOut::create(pActionMoveDown),
                                                              EaseSineInOut::create(pActionMoveUp)
                                                              );
        pBigCloud->runAction(RepeatForever::create(pActionSeq));
    }
    {
        Sprite* pBigCloud = Sprite::create(RES::BIG_CLOUD1);
        pBigCloud->setAnchorPoint(Vec2(0.5, 0));
        pBigCloud->setPosition(origin + Vec2(visibleSize.width / 2, 0));
        this->addChild(pBigCloud);
        
        MoveBy* pActionMoveDown = MoveBy::create(7, Vec2(0, -30));
        MoveBy* pActionMoveUp = pActionMoveDown->reverse();
        Sequence* pActionSeq = Sequence::createWithTwoActions(
                                                              EaseSineInOut::create(pActionMoveDown),
                                                              EaseSineInOut::create(pActionMoveUp)
                                                              );
        pBigCloud->runAction(RepeatForever::create(pActionSeq));
    }
    
    // 开始按钮
    Button* pBtnStart = Button::create(RES::START_BUTTON, RES::START_BUTTON1);
    pBtnStart->setPosition(origin + Vec2(visibleSize.width / 2, pBtnStart->getContentSize().height / 2 + 50));
    pBtnStart->setTag(START_BUTTON_TAG);
    pBtnStart->addClickEventListener(CC_CALLBACK_1(HomeScene::onMainButtonClick, this));
    this->addChild(pBtnStart);
    
    // 皮肤按钮
    Button* pBtnSkin = Button::create(RES::SKIN_BUTTON, RES::SKIN_BUTTON1);
    pBtnSkin->setPosition(Vec2(pBtnStart->getPositionX() - 150, pBtnStart->getPositionY()));
    pBtnSkin->setTag(SKIN_BUTTON_TAG);
    pBtnSkin->addClickEventListener(CC_CALLBACK_1(HomeScene::onMainButtonClick, this));
    this->addChild(pBtnSkin);
    
    // 关于按钮
    Button* pBtnAbout = Button::create(RES::ABOUT_BUTTON, RES::ABOUT_BUTTON1);
    pBtnAbout->setPosition(Vec2(pBtnStart->getPositionX() + 150, pBtnStart->getPositionY()));
    pBtnAbout->setTag(ABOUT_BUTTON_TAG);
    pBtnAbout->addClickEventListener(CC_CALLBACK_1(HomeScene::onMainButtonClick, this));
    this->addChild(pBtnAbout);
    
    return true;
}
//---------------------------------------------
void HomeScene::onCloudClick(cocos2d::Ref* pSender)
{
    Button* pCloud = (Button*)pSender;
    
    MoveBy* pActionMoveUp = MoveBy::create(2, Vec2(0, 35));
    MoveBy* pActionMoveDown = MoveBy::create(3, Vec2(0, -35));
    Sequence* pActionSeq = Sequence::createWithTwoActions(EaseElasticIn::create(pActionMoveUp), EaseElasticOut::create(pActionMoveDown));
    pCloud->runAction(pActionSeq);
    
    // 如果点击的是菜单云彩
    if (pCloud->getTag() == COLOR_EGG_BUTTON_TAG)
    {
        if(++m_iColorEggCount == 10)
        {
            m_iColorEggCount = 0;
            
            // 向下移动200px
            Button* pLogo = (Button*)this->getChildByTag(LOGO_TAG);
            pLogo->runAction(EaseSineInOut::create(MoveBy::create(1, Vec2(0, -200))));
        }
    }
}
//---------------------------------------------
void HomeScene::onLogoClick(cocos2d::Ref* pSender)
{
    // TODO 成就
}
//---------------------------------------------
void HomeScene::onMainButtonClick(cocos2d::Ref* pSender)
{
    Button* pButton = (Button*)pSender;
    
    int btnTag = pButton->getTag();
    
    // 开始
    if (btnTag == START_BUTTON_TAG)
    {
        GameScene* gs = GameScene::create("Level/3001.json");
        Director::getInstance()->replaceScene(gs);
    }
    
    // 皮肤
    if (btnTag == SKIN_BUTTON_TAG)
    {
        ChangeSkinLayer* layer = ChangeSkinLayer::create();
        this->addChild(layer);
    }
    
    // 关于
    if (btnTag == ABOUT_BUTTON_TAG)
    {
        DialogView* view = DialogView::create(
                                              RES::Text::getInstance()->getText("about_title"),
                                              RES::Text::getInstance()->getText("about_content"));
        view->addOkButtonClick([=](Ref* pSender)
                               {
                                   view->removeFromParent();
                               });
        this->addChild(view);
    }
}
//---------------------------------------------