//------------------------------------------------
#include "ProbabilityCalculator.h"
//------------------------------------------------
USING_NS_CC;
//------------------------------------------------
ProbabilityCalculator::ProbabilityCalculator()
{
}
//------------------------------------------------
void ProbabilityCalculator::addEventFactor(int eventType, float percentage)
{
	EventFactor ef;
	ef.eventType  = eventType;
	ef.percentage = percentage;
	m_factors.push_back(ef);
}
//------------------------------------------------
void ProbabilityCalculator::removeAllEventFactor()
{
	m_factors.clear();
}
//------------------------------------------------
std::vector<int> ProbabilityCalculator::getEventList(int count)
{
	std::vector<int> probabilityFactor;
	
	float eventSum = __getEventSum();

	// 填充数据
	for (int i = 0; i < m_factors.size(); i++)
	{
		int   eventType  = m_factors[i].eventType;
		float percentage = m_factors[i].percentage / eventSum;
		int   size		 = count * percentage;

		for (int j = 0; j < size; j++)
		{
			probabilityFactor.push_back(eventType);
		}
	}

	// 整理数据
	__arrangeEventFactors(probabilityFactor, count);

	// 打乱顺序
	__randomEventFactors(probabilityFactor);

	return probabilityFactor;
}
//------------------------------------------------
float ProbabilityCalculator::__getEventSum()
{
	float percentageCount = 0.0f;

	for (int i = 0; i < m_factors.size(); i++)
	{
		percentageCount += m_factors[i].percentage;
	}
	
	return percentageCount;
}
//------------------------------------------------
void ProbabilityCalculator::__arrangeEventFactors(std::vector<int>& factors, int count)
{
	int dValue = factors.size() - count;
	
	if (dValue < 0)
	{
		for (int i = 0; i < -dValue; i++)
		{
			int index = RandomHelper::random_int<int>(0, m_factors.size()-1);
			factors.push_back(m_factors[index].eventType);
		}
	}

	if (dValue > 0)
	{
		for (int i = 0; i < dValue; i++)
		{
			factors.pop_back();
		}
	}
}
//------------------------------------------------
void ProbabilityCalculator::__randomEventFactors(std::vector<int>& factors)
{
	for (int i = 0; i < factors.size(); i++)
	{
		int oldType = factors[i];
		int index = RandomHelper::random_int<int>(0, factors.size()-1);

 		factors[i]	   = factors[index];
 		factors[index] = oldType;
	}
}
//------------------------------------------------