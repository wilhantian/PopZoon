/************************************************************************** 
* Copyright (c) 2015, pxbomb, All rights reserved. 

* File		: Weibo.h
* Date		: 2015/06/10 11:58  
* Author	: WilhanTian
* Email		: wilhan.tian@gmail.com
* Depict	: 
**************************************************************************/
#ifndef _WEIBO_H_
#define _WEIBO_H_

#include "cocos2d.h"

enum class EnumWeiboAuthorizedType
{
	OK,
	FAIL
};

class WeiboAuthorize
{
public:
	static WeiboAuthorize* getInstance();

public:
	void authorize();

	void setOnAuthorizedListener(const std::function<void(EnumWeiboAuthorizedType)>& callback);

protected:
	std::function<void(EnumWeiboAuthorizedType)> m_callback;

	static WeiboAuthorize* s_instance;
};

#endif // _WEIBO_H_/