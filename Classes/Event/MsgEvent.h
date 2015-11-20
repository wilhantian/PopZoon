#ifndef _EVENT_H_
#define _EVENT_H_

#include "cocos2d.h"
//--------------------------------------------------------------------
// 队列消除开始
static const std::string MsgOnPopBegin   = "MsgOnPopBegin";
// 队列消除结束
static const std::string MsgOnPopEnded   = "MsgOnPopEnded";
// 一个动物被消除
static const std::string MsgOnOnePoped   = "MsgOnOnePoped";
// 开始整理
static const std::string MsgOnOrderBegin = "MsgOnOrderBegin";
// 整理结束
static const std::string MsgOnOrderEnded = "MsgOnOrderEnded";
//--------------------------------------------------------------------
// 分数变更
// @dispatch int
static const std::string MsgPointChange = "MsgPointChange";
//--------------------------------------------------------------------
// 队列消除开始
static const std::string MsgOnPopBeginForPoint = "MsgOnPopBeginForPoint";
// 队列消除结束
static const std::string MsgOnPopEndedForPoint = "MsgOnPopEndedForPoint";
// 一个动物被消除
static const std::string MsgOnOnePopedForPoint = "MsgOnOnePopedForPoint";
// 开始整理
static const std::string MsgOnOrderBeginForPoint = "MsgOnOrderBeginForPoint";
// 整理结束
static const std::string MsgOnOrderEndedForPoint = "MsgOnOrderEndedForPoint";
//--------------------------------------------------------------------
// 技能变更
static const std::string MsgOnPropChanged = "MsgOnPropChanged";

class MsgEvent
{
public:
	// 添加事件
	static void addEvent(const std::string &eventName, const std::function<void(cocos2d::EventCustom*)>& callback);
	
	// 移除事件
	static void removeEvent(const std::string &eventName);
	
	// 派发事件
	static void dispatchEvent(const std::string &eventName, void* userData);
};

#endif