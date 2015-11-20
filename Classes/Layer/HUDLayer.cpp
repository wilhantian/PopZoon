//
//  HUDLayer.cpp
//  PopZoo3.8.1
//
//  Created by WilhanTian on 15/10/27.
//
//
//----------------------------------------------
#include "HUDLayer.h"
#include "AppInclude.h"
#include "ui/CocosGUI.h"
//----------------------------------------------
USING_NS_CC;
using namespace ui;
//----------------------------------------------
bool HUDLayer::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    Size winSize     = Director::getInstance()->getWinSize();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin      = Director::getInstance()->getVisibleOrigin();
    
    // Bar
    Sprite* bar = Sprite::create("bar.png");
    bar->setScale(visibleSize.width / winSize.width);
    bar->setAnchorPoint(Vec2(0, 0));
    bar->setPosition(origin + Vec2(16, -16));
    this->addChild(bar);
    
    // 炸弹
    Button* itemBtnBomb = Button::create("yellow_boxCross.png");
    itemBtnBomb->setAnchorPoint(Vec2(0.5, 0.5));
    itemBtnBomb->setPosition(Vec2(bar->getContentSize().width/6 * 1, bar->getContentSize().height/2 + 8));
    itemBtnBomb->setTag(PropType::PropType_Bomb);
    itemBtnBomb->addClickEventListener(CC_CALLBACK_1(HUDLayer::onPropButtonClick, this));
    bar->addChild(itemBtnBomb);
    
    // 横向消除
    Button* itemBtnRow = Button::create("yellow_boxCross.png");
    itemBtnRow->setAnchorPoint(Vec2(0.5, 0.5));
    itemBtnRow->setPosition(Vec2(bar->getContentSize().width/6 * 2, bar->getContentSize().height/2 + 8));
    itemBtnRow->setTag(PropType::PropType_Row);
    itemBtnRow->addClickEventListener(CC_CALLBACK_1(HUDLayer::onPropButtonClick, this));
    bar->addChild(itemBtnRow);
    
    // 纵向消除
    Button* itemBtnCol = Button::create("yellow_boxCross.png");
    itemBtnCol->setAnchorPoint(Vec2(0.5, 0.5));
    itemBtnCol->setPosition(Vec2(bar->getContentSize().width/6 * 3, bar->getContentSize().height/2 + 8));
    itemBtnCol->setTag(PropType::PropType_Col);
    itemBtnCol->addClickEventListener(CC_CALLBACK_1(HUDLayer::onPropButtonClick, this));
    bar->addChild(itemBtnCol);
    
    // 乾坤大挪移
    Button* itemBtnMove = Button::create("yellow_boxCross.png");
    itemBtnMove->setAnchorPoint(Vec2(0.5, 0.5));
    itemBtnMove->setPosition(Vec2(bar->getContentSize().width/6 * 4, bar->getContentSize().height/2 + 8));
    itemBtnMove->setTag(PropType::PropType_Move);
    itemBtnMove->addClickEventListener(CC_CALLBACK_1(HUDLayer::onPropButtonClick, this));
    bar->addChild(itemBtnMove);
    
    // 锤子
    Button* itemBtnSinker = Button::create("yellow_boxCross.png");
    itemBtnSinker->setAnchorPoint(Vec2(0.5, 0.5));
    itemBtnSinker->setPosition(Vec2(bar->getContentSize().width/6 * 5, bar->getContentSize().height/2 + 8));
    itemBtnSinker->setTag(PropType::PropType_Sinker);
    itemBtnSinker->addClickEventListener(CC_CALLBACK_1(HUDLayer::onPropButtonClick, this));
    bar->addChild(itemBtnSinker);
    
    return true;
}
//----------------------------------------------
void HUDLayer::onPropButtonClick(Ref* pSender)
{
    Button* btn = (Button*)pSender;
    int tag     = btn->getTag();
    
    btn->setScale(1.5);
    
    CCLOG("派发MsgOnPropChanged事件 : %d", tag);
    
    MsgEvent::dispatchEvent(MsgOnPropChanged, &tag);
}
//----------------------------------------------