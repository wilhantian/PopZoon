/************************************************************************** 
* Copyright (c) 2015, pxbomb, All rights reserved. 

* File		: GameManager.h
* Date		: 2015/07/22 12:56  
* Author	: WilhanTian
* Email		: wilhan.tian@gmail.com
* Depict	: 
**************************************************************************/
#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include "cocos2d.h"
#include "Level/LevelDefine.h"

#define COLLECT_TYPE_SIZE 10

class GameManager
{
public:
	static GameManager* getInstance();
	static void destoryInstance();

// 分数
public:
	void addScore(int iScore);
	void cutScore(int iScore);
	int  getScore();
	void setScore(int iScore);

	void setOnScoreChangedListener(const std::function<void(int)>& callback);

// 时间s
public:
	void  setTime(int time);
	int   getTime();

// 步数
public:
	void addStep(int iStep);
	void cupStep(int iStep);
	void setStep(int iStep);
	int  getStep();

	void setOnStepChangedListener(const std::function<void(int)>& callback);

// 消除收集统计
public:
	void addCollectType(int iType);
	int  getCollectType(int iType);
	void setCollectType(int iType, int count);

	void setOnCollectTypeChengedListener(const std::function<void(int, int)>& callback);

// 收集类型
public:
	void setTaskInfo(std::vector<TaskInfo> taskInfo);
	std::vector<TaskInfo> getTaskInfo();

// 关卡类型
public:
	void setLevelType(int iLevelType);
	int  getLevelType();

protected:
	GameManager();

protected:
	static GameManager* m_instance;

	int m_iLevelType;
	int m_iScore;
	int m_iStep;
	int m_aCollectTypeCount[COLLECT_TYPE_SIZE];	// 收集类型计数器 0-9
	int m_iTime;

	std::vector<TaskInfo> m_taskInfo;

	std::function<void(int)> m_ScoreChangedCallback;
	std::function<void(int)> m_StepChangedCallback;
	std::function<void(int, int)> m_CollectTypeChangedCallback;		// iType count
};

#endif // _GAMEMANAGER_H_/