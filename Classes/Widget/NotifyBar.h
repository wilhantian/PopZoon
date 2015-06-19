#ifndef _NOTIFY_BAR_H_
#define _NOTIFY_BAR_H_

#include "cocos2d.h"
#include "ui/UIScale9Sprite.h"

class NotifyBar : public cocos2d::Node
{
public:
	static NotifyBar* create(std::string strBackgoundPath, std::string strTitle, std::string strContent, std::string strIconPath);

protected:
	virtual bool init(std::string strBackgoundPath, std::string strTitle, std::string strContent, std::string strIconPath);
};

#endif