#ifndef _SCORE_LABEL_ATLAS_H_
#define _SCORE_LABEL_ATLAS_H_

#include "cocos2d.h"

//每次+5
#define STEP_SCORE 15

class ScoreLabelAtlas : public cocos2d::LabelAtlas
{
public:
	static ScoreLabelAtlas* create(int iScore, const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap);

	virtual void setScore(int iScore);

	virtual int getScore();
protected:
	virtual bool init(int iScore, const std::string& charMapFile, int itemWidth, int itemHeight, int startCharMap);

	virtual void onUpdate(float time);

	ScoreLabelAtlas();

protected:
	int m_iTargerScore;
};


#endif