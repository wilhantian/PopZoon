#ifndef _NOTIFICATION_MANAGER_H_
#define _NOTIFICATION_MANAGER_H_

#include "NotifyBar.h"

class NotificationManager : public cocos2d::Node
{
public:
	static NotificationManager* getInstance();

	void notification(NotifyBar* pNotifyBar);

	virtual bool init();

	virtual void update(float delta);
protected:
	static NotificationManager* s_pInstance;

	cocos2d::Vector<NotifyBar*> m_vNotifyBars;
};

#endif