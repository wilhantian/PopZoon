#ifndef _NOTIFICATION_H_
#define _NOTIFICATION_H_

#include "cocos2d.h"

class NotificationBar : public cocos2d::Node
{
public:
	static NotificationBar* create(std::string strBackground, std::string strIconPath, std::string strTitle, std::string strContent);
protected:
	virtual bool init(std::string strBackground, std::string strIconPath, std::string strTitle, std::string strContent);
};

class NotificationManager
{
public:
	static NotificationManager* getInstance();

	void notify(NotificationBar* pNotificationBar);

protected:
	static NotificationManager* pInstance;

	cocos2d::Vector<NotificationBar*> m_vBars;
};

#endif