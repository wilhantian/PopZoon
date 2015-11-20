#include "PointManager.h"
//-----------------------------------------------
USING_NS_CC;
//-----------------------------------------------
PointManager* PointManager::getInstance()
{
	if (s_instance == NULL)
	{
		s_instance = new PointManager();
		s_instance->init();
	}
	return s_instance;
}
//-----------------------------------------------
void PointManager::destoryInstance()
{
	MsgEvent::removeEvent(MsgOnOnePopedForPoint);
	MsgEvent::removeEvent(MsgOnPopBeginForPoint);
	MsgEvent::removeEvent(MsgOnPopEndedForPoint);

	CC_SAFE_DELETE(s_instance);
}
//-----------------------------------------------
void PointManager::init()
{
	m_iPoint = 0;

}
//-----------------------------------------------

//-----------------------------------------------
PointManager* PointManager::s_instance = NULL;
//-----------------------------------------------