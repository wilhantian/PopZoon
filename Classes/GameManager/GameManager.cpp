#include "GameManager.h"
//----------------------------------------
USING_NS_CC;
//----------------------------------------
GameManager* GameManager::getInstance()
{
	if (m_instance == NULL)
	{
		m_instance = new GameManager();
	}
	return m_instance;
}
//----------------------------------------
void GameManager::destoryInstance()
{
	CC_SAFE_DELETE(m_instance);
}
//----------------------------------------
void GameManager::setScore(int iScore)
{
	m_iScore = iScore;
	
	if (m_ScoreChangedCallback)
	{
		m_ScoreChangedCallback(m_iScore);
	}

	log("===SCORE:::%d===", m_iScore);
}
//-----------------------------------------------
int GameManager::getScore()
{
	return m_iScore;
}
//-----------------------------------------------
void GameManager::addScore(int iScore)
{
	setScore(getScore() + iScore);
}
//-----------------------------------------------
void GameManager::cutScore(int iScore)
{
	int iPos = m_iScore - iScore;
	setScore(iPos > 0 ? iPos : 0);

}
//----------------------------------------
void GameManager::setOnScoreChangedListener(const std::function<void(int)>& callback)
{
	m_ScoreChangedCallback = callback;
}
//----------------------------------------
GameManager::GameManager()
: m_iScore(0)
, m_ScoreChangedCallback(nullptr)
, m_StepChangedCallback(nullptr)
, m_iStep(0)
, m_iLevelType(0)
, m_CollectTypeChangedCallback(nullptr)
{
	for (int i = 0; i < COLLECT_TYPE_SIZE; i++)
	{
		m_aCollectTypeCount[i] = 0;
	}
}
//----------------------------------------
void GameManager::addStep(int iStep)
{
	setStep(getStep() + iStep);
}
//----------------------------------------
void GameManager::cupStep(int iStep)
{
	int iPos = m_iStep - iStep;
	setStep(iPos > 0 ? iPos : 0);
}
//----------------------------------------
void GameManager::setStep(int iStep)
{
	m_iStep = iStep;

	if (m_StepChangedCallback)
	{
		m_StepChangedCallback(m_iStep);
	}

	log("===STEP:::%d===", m_iStep);
}
//----------------------------------------
int GameManager::getStep()
{
	return m_iStep;
}
//----------------------------------------
void GameManager::setOnStepChangedListener(const std::function<void(int)>& callback)
{
	m_StepChangedCallback = callback;
}
//----------------------------------------
void GameManager::setLevelType(int iLevelType)
{
	m_iLevelType = iLevelType;
}
//----------------------------------------
int GameManager::getLevelType()
{
	return m_iLevelType;
}
//----------------------------------------
void GameManager::addCollectType(int iType)
{
	setCollectType(iType, getCollectType(iType) + 1);
}
//----------------------------------------
int GameManager::getCollectType(int iType)
{
	return m_aCollectTypeCount[iType];
}
//----------------------------------------
void GameManager::setCollectType(int iType, int count)
{
	m_aCollectTypeCount[iType] = count;

	if (m_CollectTypeChangedCallback)
	{
		m_CollectTypeChangedCallback(iType, count);
	}
}
//----------------------------------------
void GameManager::setOnCollectTypeChengedListener(const std::function<void(int, int)>& callback)
{
	m_CollectTypeChangedCallback = callback;
}
//----------------------------------------
void GameManager::setTaskInfo(std::vector<TaskInfo> taskInfo)
{
	m_taskInfo = taskInfo;
}
//----------------------------------------
std::vector<TaskInfo> GameManager::getTaskInfo()
{
	return m_taskInfo;
}
//----------------------------------------
void GameManager::setTime(int time)
{
	m_iTime = time;
}
//----------------------------------------
int GameManager::getTime()
{
	return m_iTime;
}
//----------------------------------------
GameManager* GameManager::m_instance = NULL;
//----------------------------------------