/************************************************************************** 
* Copyright (c) 2015, pxbomb, All rights reserved. 

* File		: PropNormal.h
* Date		: 2015/06/17 22:16  
* Author	: WilhanTian
* Email		: wilhan.tian@gmail.com
* Depict	: 普通的游戏消除逻辑
**************************************************************************/
#ifndef _PROPNORMAL_H_
#define _PROPNORMAL_H_

#include "cocos2d.h"
#include "PropBase.h"
#include "View/Zoo.h"

class PropNormal : public PropBase
{
public:
	static PropNormal* getInstance();

	virtual bool onHandle(Zoo* pZoo, int iRow, int iCol);

protected:
	//返回相连动物
	std::vector<ZoonPos> check(Zoo* pZoo, int iRow, int iCol);

	//检查四周
	//@return 是否检查完成，open表中不在有值
	bool _checkOpenList(Zoo* pZoo);

	//检查闭表中是否有这个元素
	bool _isCloseListHave(ZoonPos pos);

	//检查Open表中是否有这个元素
	bool _isOpenListHave(ZoonPos pos);

	//放入Open表中
	//如果闭表中有该元素，那么不会放入这个元素
	void _pushInOpenList(ZoonPos pos);

protected:
	std::vector<ZoonPos>	m_vOpen;		//未检查的节点
	std::vector<ZoonPos>	m_vClose;		//以检查的节点

	static PropNormal* s_instance;
};

#endif // _PROPNORMAL_H_/