/************************************************************************** 
* Copyright (c) 2015, pxbomb, All rights reserved. 

* File		: HomeScene.h
* Date		: 2015/08/06 13:38  
* Author	: WilhanTian
* Email		: wilhan.tian@gmail.com
* Depict	: 
**************************************************************************/
#ifndef _HOMESCENE_H_
#define _HOMESCENE_H_

#include "cocos2d.h"
#include "RES.h"

class HomeScene : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();
	CREATE_FUNC(HomeScene);

protected:
	virtual bool init();

protected:
	void onCloudClick(cocos2d::Ref* pSender);
	void onLogoClick(cocos2d::Ref* pSender);
	void onMainButtonClick(cocos2d::Ref* pSender);
    
protected:
    int m_iColorEggCount;   // 菜单计数器
};

#endif // _HOMESCENE_H_/