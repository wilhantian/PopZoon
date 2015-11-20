#ifndef _POINT_MANAGER_H_
#define _POINT_MANAGER_H_

#include "AppInclude.h"

// 游戏分数管理器
// 注意，分数变更时将发送MsgPointChange消息
class PointManager
{
public:
	static PointManager* getInstance();
	static void destoryInstance();

	void init();

	// 增加分数
	void addPoint(int iPoint);
	// 减少分数
	void cutPoint(int iPoint);

	// 设置分数
	// 不推荐使用
	void setPoint(int iPoint);

	// 获取分数
	int  getPoint();
protected:
	static PointManager* s_instance;

protected:
	int m_iPoint;
};

#endif