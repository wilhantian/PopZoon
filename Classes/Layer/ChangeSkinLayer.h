/************************************************************************** 
* Copyright (c) 2015, pxbomb, All rights reserved. 

* File		: ChangeSkinLayer.h
* Date		: 2015/08/06 16:24  
* Author	: WilhanTian
* Email		: wilhan.tian@gmail.com
* Depict	: 
**************************************************************************/
#ifndef _CHANGESKINLAYER_H_
#define _CHANGESKINLAYER_H_

#include "cocos2d.h"
#include "RES.h"
#include "ui/UIPageView.h"
#include "ui/UIButton.h"

class ChangeSkinLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(ChangeSkinLayer);

	void addSkin(std::string strImagePath);

protected:
	virtual bool init();

	void checkPageIndex();

	void onCloseButtonClick(cocos2d::Ref* pSender);
	void onSelectButtonClick(cocos2d::Ref* pSender);
	void onPageChange(cocos2d::Ref* pSender, cocos2d::ui::PageView::EventType eventType);

protected:
	cocos2d::ui::PageView* m_pPageView;
	cocos2d::ui::Button* m_pBtnLeft;
	cocos2d::ui::Button* m_pBtnRight;
	cocos2d::ui::Button* m_pBtnDown;
};

#endif // _CHANGESKINLAYER_H_/