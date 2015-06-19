/************************************************************************** 
* Copyright (c) 2015, pxbomb, All rights reserved. 

* File		: FloatNumber.h
* Date		: 2015/05/31 18:20  
* Author	: WilhanTian
* Email		: wilhan.tian@gmail.com
* Depict	: 
**************************************************************************/
#ifndef _FLOATNUMBER_H_
#define _FLOATNUMBER_H_

#include "cocos2d.h"

class FloatNumber : cocos2d::Node
{
public:
	// ÏÔÊ¾Æ®×Ö¶¯»­
	static FloatNumber* show(cocos2d::Vec2& pos);
	static FloatNumber* show(cocos2d::Vec2& pos, cocos2d::Vec2& toPos);
protected:
	// init this class
	virtual bool init(cocos2d::Vec2& pos);
	virtual bool init(cocos2d::Vec2& pos, cocos2d::Vec2& toPos);
	
};


#endif // _FLOATNUMBER_H_/