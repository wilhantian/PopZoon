/************************************************************************** 
* Copyright (c) 2015, pxbomb, All rights reserved. 

* File		: DialogView.h
* Date		: 2015/08/07 12:32  
* Author	: WilhanTian
* Email		: wilhan.tian@gmail.com
* Depict	: 
**************************************************************************/
#ifndef _DIALOGVIEW_H_
#define _DIALOGVIEW_H_

#include "cocos2d.h"

class DialogView : public cocos2d::Node
{
public:
	static DialogView* create(const std::string& strTitle, const std::string& strContent);

	void addOkButtonClick(const std::function<void(cocos2d::Ref*)>& callback);

protected:
	virtual bool init(const std::string& strTitle, const std::string& strContent);

	DialogView();
protected:
	std::function<void(cocos2d::Ref*)> onOkButtonClick;
};

#endif // _DIALOGVIEW_H_/