#include "ScoreLabelAtlas.h"

USING_NS_CC;

std::string intToStr(int num)
{
	char cNum[32];
	sprintf(cNum, "%d", num);
	return cNum;
}

ScoreLabelAtlas::ScoreLabelAtlas() :
m_iTargerScore(0)
{

}

ScoreLabelAtlas* ScoreLabelAtlas::create(int iScore, const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap)
{
	ScoreLabelAtlas* label = new ScoreLabelAtlas();
	if (label && label->init(iScore, charMapFile, itemWidth, itemHeight, startCharMap))
	{
		label->autorelease();
		return label;
	}
	CC_SAFE_DELETE(label);
	return NULL;
}

bool ScoreLabelAtlas::init(int iScore, const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap)
{
	if (!ScoreLabelAtlas::initWithString(intToStr(iScore), charMapFile, itemWidth, itemHeight, startCharMap))
	{
		return false;
	}

	return true;
}

void ScoreLabelAtlas::setScore(int iScore)
{
	//设置目标分数
	m_iTargerScore = iScore;

	//开启更新器
	schedule(CC_SCHEDULE_SELECTOR(ScoreLabelAtlas::onUpdate), 0.05);
}

int ScoreLabelAtlas::getScore()
{
	return atoi(getString().c_str());
}

void ScoreLabelAtlas::onUpdate(float time)
{
	int nowScoew = getScore();

	if (abs(nowScoew - m_iTargerScore) <= STEP_SCORE)
	{
		setString(intToStr(m_iTargerScore));
		unschedule(CC_SCHEDULE_SELECTOR(ScoreLabelAtlas::onUpdate));
		return;
	}

	else if (nowScoew < m_iTargerScore)
	{
		setString(intToStr(nowScoew + STEP_SCORE));
	}

	else // if (nowScoew > m_targerScore)
	{
		setString(intToStr(nowScoew - STEP_SCORE));
	}
}