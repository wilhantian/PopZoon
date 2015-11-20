/************************************************************************** 
* Copyright (c) 2015, pxbomb, All rights reserved. 

* File		: PropBase.h
* Date		: 2015/06/17 21:18  
* Author	: WilhanTian
* Email		: wilhan.tian@gmail.com
* Depict	: 技能接口
              所有技能类必须继承该接口并实现onHandle纯虚函数
              在onHandle中实现相应的技能逻辑
**************************************************************************/
#ifndef _PROPBASE_H_
#define _PROPBASE_H_

#include "cocos2d.h"

class Zoo;

class PropBase : public cocos2d::Ref
{
public:
	virtual bool onHandle(Zoo* pZoo, int iRow, int iCol) = 0;
};

#endif // _PROPBASE_H_/