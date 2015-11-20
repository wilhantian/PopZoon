#include "MsgEvent.h"
//-----------------------------------------------------------------
USING_NS_CC;
//-----------------------------------------------------------------
void MsgEvent::addEvent(const std::string &eventName, const std::function<void(EventCustom*)>& callback)
{
	Director::getInstance()->getEventDispatcher()->addCustomEventListener(eventName, callback);
}
//-----------------------------------------------------------------
void MsgEvent::removeEvent(const std::string &eventName)
{
	Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(eventName);
}
//-----------------------------------------------------------------
void MsgEvent::dispatchEvent(const std::string &eventName, void* userData)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(eventName, userData);
}
//-----------------------------------------------------------------