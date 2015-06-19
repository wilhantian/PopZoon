#ifndef _JELLY_BUTTON_H_
#define _JELLY_BUTTON_H_

#include "cocos2d.h"

class JellyButton : public cocos2d::MenuItemImage
{
public:
	static JellyButton* create(const std::string& normalImage, const cocos2d::ccMenuCallback& callback);

protected:
	virtual bool init(const std::string& normalImage, const cocos2d::ccMenuCallback& callback);

	virtual void selected();

	virtual void unselected();

};

#endif