#include "TalentManager.h"
//-----------------------------------------------
USING_NS_CC;
//-----------------------------------------------
TalentManager* TalentManager::getInstance()
{
	if (m_instance == NULL)
	{
		m_instance = new TalentManager();
	}
	return m_instance;
}
//-----------------------------------------------
void TalentManager::destoryInstance()
{
	CC_SAFE_DELETE(m_instance);
}
//-----------------------------------------------
int TalentManager::getComputeScore(int iType, int iCount)
{
	return 20 + (iCount * 5);
}
//-----------------------------------------------
int TalentManager::getConputeNegativeScore(int iType, int iCount)
{
	return -(20 + (iCount * 5));
}
//-----------------------------------------------
TalentManager* TalentManager::m_instance = NULL;
//-----------------------------------------------