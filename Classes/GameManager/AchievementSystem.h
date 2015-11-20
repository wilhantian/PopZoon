/************************************************************************** 
* Copyright (c) 2015, pxbomb, All rights reserved. 

* File		: AchievementSystem.h
* Date		: 2015/07/28 15:20  
* Author	: WilhanTian
* Email		: wilhan.tian@gmail.com
* Depict	: 
**************************************************************************/
#ifndef _ACHIEVEMENTSYSTEM_H_
#define _ACHIEVEMENTSYSTEM_H_

#include "cocos2d.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

#include "AchievementDefine.h"
//-------------------------------------------------------
struct AchievementInfo
{
	int iID;						// 成就ID

	std::string strIconSmallPath;	// 小图
	std::string strIconOKPath;		// 图标路径(开启)
	std::string strIconNOPath;		// 图标路径(关闭)
	std::string strTitle;			// 标题
	std::string strDescription;		// 描述

	std::string strCardPath;		// 卡牌路径
	std::string strContent;			// 卡牌描述

	bool isOK;						// 是否获取该成就
};
//-------------------------------------------------------



//-------------------------------------------------------

class AchievementSystem
{
public:
	static AchievementSystem* getInstance();
	static void destoryInstance();

	void init();
	void initAchievementRelyOn();		// 初始化依赖
	void initAchievementInfo();
	void save();

	std::vector<AchievementInfo> loadAchievementInfosFile(std::string filePath);

	// 获取所有成就信息
	std::vector<AchievementInfo> getAchievementInfos();

	// 根据ID获取成就
	AchievementInfo getAchievementInfo(int iID);

	// 设置是否已经取得该成就
	void setAchievementIsOK(int iID, bool isOK);

	bool isAchievementOK(int iID);

// 动作触发
public:
	// 无效的点击元素一次
	void triggerClickFailZoonOnce();

	// 消除元素
	void triggerPopedZoon(int iType, int iCount);
	void checkPopedZoon();

	// 得分一次
	void triggerGetScore(int iScore);
	void checkGetScore();

	// 扣分一次
	void triggerCutScore(int iScore);
	void checkCutScore();

	// 使用一次道具/技能
	void triggerUseProp();

	// 观看一次广告
	void triggerWatchAD();

	// 成功进入游戏一次
	void triggerEnterGame();

	// 游戏胜利一次
	void triggerGameWin();

	// 游戏失败一次
	void triggerGameFail();

	// 游戏打开1分钟
	void triggerInAppOneMis();

	// 消耗金币
	void triggerCutCoin(int iCoin);

	// 累加金币
	void triggerGetCoin(int iCoin);

	// 进入一次关卡
	void triggerIntoLevel(int iLevelId);

	// 点击LOGO一次
	void triggerClickLogo();

protected:
	unsigned int m_uiClickFailCount;		// 无效的点击计数
	unsigned int m_uiGetScore;				// 得分总计
	unsigned int m_uiCutScore;				// 扣分总计
	unsigned int m_uiUsePropCount;			// 使用道具总计
	unsigned int m_uiWatchADCount;			// 观看广告次数
	unsigned int m_uiEnterGameCount;		// 成功进入游戏一次
	unsigned int m_uiGameWinCount;			// 游戏胜利总计
	unsigned int m_uiGameFailCount;			// 游戏失败总计
	unsigned int m_uiInAppMis;				// 在游戏中共进行多少分钟
	unsigned int m_uiCutCoin;				// 消耗金币总计
	unsigned int m_uiGetCoin;				// 共获得金币
	unsigned int m_uiClickLogoCount;		// 点击LOGO总计

	std::map<int, unsigned int> m_mPopTypeCount;		// 消除统计
	std::map<int, unsigned int> m_uiIntoLevelCount;		// 进入一次关卡

protected:
	std::vector<AchievementInfo> m_tagAchievementInfos;	// 所有成就
	
	rapidjson::Document m_relyDoc;
protected:
	static AchievementSystem* s_instance;
};

#endif // _ACHIEVEMENTSYSTEM_H_/