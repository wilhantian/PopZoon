/************************************************************************** 
* Copyright (c) 2015, pxbomb, All rights reserved. 

* File		: LevelManager.h
* Date		: 2015/07/09 18:12  
* Author	: WilhanTian
* Email		: wilhan.tian@gmail.com
* Depict	: 
**************************************************************************/
#ifndef _LEVELMANAGER_H_
#define _LEVELMANAGER_H_

#include "cocos2d.h"
#include "LevelDefine.h"

class LevelManager
{
public:
	static LevelInfo getLevelInfo(std::string strFileFile);

	static int			 getLevelType(std::string strFileFile);

	static BaseLevelInfo getBaseLevelInfo(std::string strFilePath);

	static LevelInfo_1001 getLevelInfoForType1001(std::string strFileFile);
	static LevelInfo_1002 getLevelInfoForType1002(const std::string& strFilePath);

	static LevelInfo_2001 getLevelInfoForType2001(const std::string& strFilePath);
	static LevelInfo_2002 getLevelInfoForType2002(const std::string& strFilePath);
	static LevelInfo_2003 getLevelInfoForType2003(const std::string& strFilePath);

	static LevelInfo_3001 getLevelInfoForType3001(const std::string& strFilePath);
	static LevelInfo_3002 getLevelInfoForType3002(const std::string& strFilePath);
	static LevelInfo_3003 getLevelInfoForType3003(const std::string& strFilePath);
};

#endif // _LEVELMANAGER_H_/