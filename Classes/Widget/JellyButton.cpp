#include "JellyButton.h"

USING_NS_CC;

JellyButton* JellyButton::create(const std::string& normalImage, const ccMenuCallback& callback)
{
	JellyButton* pButton = new JellyButton();
	if (pButton && pButton->init(normalImage, callback))
	{
		pButton->autorelease();
		return pButton;
	}
	CC_SAFE_DELETE(pButton);
	return NULL;
}

bool JellyButton::init(const std::string& normalImage, const ccMenuCallback& callback)
{
	if (!MenuItemImage::initWithNormalImage(normalImage, normalImage, normalImage, callback))
	{
		return false;
	}

	return true;
}

void JellyButton::selected()
{
	MenuItemImage::selected();
	
	ScaleTo* st = ScaleTo::create(0.6, 0.88);
	EaseElasticOut* eeo = EaseElasticOut::create(st);
	runAction(eeo);
}

void JellyButton::unselected()
{
	MenuItemImage::unselected();

	ScaleTo* st = ScaleTo::create(0.6, 1);
	EaseElasticOut* eeo = EaseElasticOut::create(st);
	runAction(eeo);
}
