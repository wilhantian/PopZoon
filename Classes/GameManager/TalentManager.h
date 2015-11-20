/************************************************************************** 
* Copyright (c) 2015, pxbomb, All rights reserved. 

* File		: TalentManager.h
* Date		: 2015/07/22 12:43  
* Author	: WilhanTian
* Email		: wilhan.tian@gmail.com
* Depict	: 
**************************************************************************/
#ifndef _TALENTMANAGER_H_
#define _TALENTMANAGER_H_

#include "cocos2d.h"

class TalentManager
{
public:
	static TalentManager* getInstance();
	static void destoryInstance();

	// 获取计算后天赋消除分数
	// @iType  类型
	// @iCount 第几个
	int getComputeScore(int iType, int iCount);

	// 获取计算后天赋消除(消极)分数
	int getConputeNegativeScore(int iType, int iCount);

protected:
	static TalentManager* m_instance;
};


#endif // _TALENTMANAGER_H_/