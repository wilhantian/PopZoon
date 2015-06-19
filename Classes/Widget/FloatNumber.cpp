#include "FloatNumber.h"
//-----------------------------------------------
USING_NS_CC;
//-----------------------------------------------
FloatNumber* FloatNumber::show(cocos2d::Vec2& pos)
{
	FloatNumber* fn = new FloatNumber();
	if (fn && fn->init(pos))
	{
		fn->autorelease();
		return fn;
	}
	CC_SAFE_DELETE(fn);
	return NULL;
}
//-----------------------------------------------
FloatNumber* FloatNumber::show(cocos2d::Vec2& pos, cocos2d::Vec2& toPos)
{
	FloatNumber* fn = new FloatNumber();
	if (fn && fn->init(pos, toPos))
	{
		fn->autorelease();
		return fn;
	}
	CC_SAFE_DELETE(fn);
	return NULL;
}
//-----------------------------------------------
bool FloatNumber::init(cocos2d::Vec2& pos)
{
	if (!Node::init())
	{
		return false;
	}

	return true;
}
//-----------------------------------------------
bool FloatNumber::init(cocos2d::Vec2& pos, cocos2d::Vec2& toPos)
{
	if (!Node::init())
	{
		return false;
	}

	return true;
}
//-----------------------------------------------