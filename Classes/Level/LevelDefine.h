/************************************************************************** 
* Copyright (c) 2015, pxbomb, All rights reserved. 

* File		: LevelDefine.h
* Date		: 2015/07/10 13:27  
* Author	: WilhanTian
* Email		: wilhan.tian@gmail.com
* Depict	: 
**************************************************************************/
#ifndef _LEVELDEFINE_H_
#define _LEVELDEFINE_H_

#include "cocos2d.h"

/**
 * 类型概率
 */
struct TypeProbability
{
	int iType;			// 类型
	int iProbability;	// 概率(权重)
}; 

/**
 * 对白
 */
struct PrologueInfo
{
	bool		bHeadPlace;				// 头像摆放位置 true-左 false-右
	std::string strHeadName;			// 头像名
	std::string strHeadFile;			// 头像资源路径

	std::vector<std::string> strWords;	// 几句话
};

// 游戏剧本
typedef std::vector<PrologueInfo> GameScript;	

//---------------------------------------------------------------
// 关卡信息
struct LevelInfo
{
	std::string strLevelId;					// 关卡ID
	std::string strDepict;					// 描述
	int			iPassScore;					// 通过分数
	int			iJumpCoin;					// 跳过该关卡所需金币
	int			iGiveExp;					// 通过给予的经验
	int			iGiveCoin;					// 通过给予的金币

	GameScript	 tagPrologueInfos;			// 开场白
	std::vector<TypeProbability> tagTypeProbabilitys;	// 类型概率
};
//---------------------------------------------------------------
// 基本关卡信息
struct BaseLevelInfo
{
	std::string strType;					// 游戏类型

	std::string strLevelId;					// 关卡ID
	std::string strDepict;					// 描述
	int			iJumpCoin;					// 跳过该关卡所需金币
	int			iGiveExp;					// 通过给予的经验
	int			iGiveCoin;					// 通过给予的金币

	GameScript	 tagPrologueInfos;			// 开场白
	std::vector<TypeProbability> tagTypeProbabilitys;	// 类型概率
};


//---------------------------------------------------------------
// 无限 通分模式
struct LevelInfo_1001 : BaseLevelInfo
{
	int			iPassScore;					// 通过分数
};
//---------------------------------------------------------------
// 无限 通分+扣分模式
struct LevelInfo_1002 : BaseLevelInfo
{
	int			iPassScore;					// 通过分数
	int			iNegativeType;				// 扣分类型
};
//---------------------------------------------------------------
// 步数+通分
struct LevelInfo_2001 : BaseLevelInfo
{
	int			iPassScore;					// 通过分数
	int			iStep;						// 步数
};
//---------------------------------------------------------------
// 收集信息
struct TaskInfo
{
	int iType;	// 类型
	int iCount;	// 个数
};
//---------------------------------------------------------------
// 步数+收集
struct LevelInfo_2002 : BaseLevelInfo
{
	int			iStep;						// 步数
	std::vector<TaskInfo> tagTask;			// 任务收集
};
//---------------------------------------------------------------
// 步数+收集+通分
struct LevelInfo_2003 : BaseLevelInfo
{
	int			iStep;						// 步数
	int			iPassScore;					// 通过分数
	std::vector<TaskInfo> tagTask;			// 任务收集
};
//---------------------------------------------------------------
// 计时+通分
struct LevelInfo_3001 : BaseLevelInfo
{
	int			iTime;						// 时间
	int			iPassScore;					// 通过分数
};
//---------------------------------------------------------------
// 计时+收集
struct LevelInfo_3002 : BaseLevelInfo
{
	int			iTime;						// 时间
	std::vector<TaskInfo> tagTask;			// 任务收集
};
//---------------------------------------------------------------
// 计时+收集+通分
struct LevelInfo_3003 : BaseLevelInfo
{
	int			iTime;						// 时间
	std::vector<TaskInfo> tagTask;			// 任务收集
	int			iPassScore;					// 通过分数
};
//---------------------------------------------------------------

#endif // _LEVELDEFINE_H_/