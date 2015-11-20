/************************************************************************** 
* Copyright (c) 2015, pxbomb, All rights reserved. 

* File		: PropBomb.h
* Date		: 2015/06/24 8:08  
* Author	: WilhanTian
* Email		: wilhan.tian@gmail.com
* Depict	: 炸弹: 消除四周
**************************************************************************/
#ifndef _PROPBOMB_H_
#define _PROPBOMB_H_

#include "cocos2d.h"
#include "PropBase.h"

class PropBomb : public PropBase
{
public:
	virtual bool onHandle(Zoo* pZoo, int iRow, int iCol);
};

#endif // _PROPBOMB_H_/