/**************************************************************************
* Copyright (c) 2015, pxbomb, All rights reserved.

* File		: FlyScore.h
* Date		: 2015/06/27 19:42
* Author	: WilhanTian
* Email		: wilhan.tian@gmail.com
* Depict	: 飘字
**************************************************************************/
#ifndef _FLYSCORE_H_
#define _FLYSCORE_H_

#include "cocos2d.h"

/**
 * 飘字
 * 内部使用对象池管理
 */
class FlyScore : public cocos2d::Node
{
public:
	static FlyScore* create();

public:
	// 设置分数文字
	void setScore(std::string score);

	// 获取分数文字
	std::string getScore();

	// 设置颜色
	void setColor(cocos2d::Color3B& color);

	// 设置字体大小
	void setFontSize(float size);

	// 设置起始位置
	void setStartPos(cocos2d::Vec2& pos);

	// 设置移动到的位置
	void setEndPos(cocos2d::Vec2& pos);

	// 设置移动速度
	// px/s
	void setSpeed(float speed);

	// 开始执行
	void startMove();

	// 结束执行
	void endMove();
protected:
	virtual bool init();

protected:
	cocos2d::Label* m_label;

	cocos2d::Vec2  m_startPos;		// 起始坐标
	cocos2d::Vec2  m_endPos;		// 结束坐标

	float m_speed;			// 速度

	static cocos2d::Vector<FlyScore*> m_flyScorePool;
	cocos2d::ParticleSystemQuad* m_particle;
};

#endif