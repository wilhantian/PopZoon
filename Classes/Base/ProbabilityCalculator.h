/************************************************************************** 
* Copyright (c) 2015, pxbomb, All rights reserved. 

* File		: ProbabilityCalculator.h
* Date		: 2015/05/29 18:52  
* Author	: WilhanTian
* Email		: wilhan.tian@gmail.com
* Depict	: 概率计算器
**************************************************************************/
#ifndef _PROBABILITYCALCULATOR_H_
#define _PROBABILITYCALCULATOR_H_

#include "cocos2d.h"

/**
* 事件因子
*/
struct EventFactor
{
	int		eventType;		// 事件名
	float	percentage;		// 几率(权重)
};

/**
 * 概率计算器
 * 指定N个事件类型与概率，取得指定个数的随机事件序列
 */
class ProbabilityCalculator
{
public:
	ProbabilityCalculator();
	
	// 添加概率因子
	// eventType:  事件名
	// percentage: 几率(权重)
	void addEventFactor(int eventType, float percentage);

	// 清除所有概率因子
	void removeAllEventFactor();

	// 获取结果
	// count: 事件总数
	std::vector<int> getEventList(int count);

private:
	// 获取概率总和
	float __getEventSum();

	// 校验整理
	// 如果少就加数据、反之
	void  __arrangeEventFactors(std::vector<int>& factors, int count);

	// 随机
	void  __randomEventFactors(std::vector<int>& factors);
private:
	std::vector<EventFactor> m_factors;
};

#endif // _PROBABILITYCALCULATOR_H_/