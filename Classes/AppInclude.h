#ifndef _APP_INCLUDE_H_
#define _APP_INCLUDE_H_

#include "cocos2d.h"

#include "Event/MsgEvent.h"

#include "View/Zoo.h"
#include "View/Zoon.h"

#include "Widget/ScoreLabelAtlas.h"
#include "Widget/JellyButton.h"
#include "Widget/NotificationBar.h"
#include "Widget/FlyScore.h"

#include "Layer/PrologueLayer.h"
#include "Layer/HUDLayer.h"

#include "Audio/AudioManager.h"
#include "Effect/EffectManager.h"
#include "Level/LevelManager.h"

#include "GameManager/GameManager.h"
#include "GameManager/TalentManager.h"
#include "GameManager/AchievementSystem.h"

#include "Base/ProbabilityCalculator.h"

#include "Prop/PropBase.h"
#include "Prop/PropNormal.h"
#include "Prop/PropBomb.h"
#include "Prop/PropRow.h"
#include "Prop/PropCol.h"

// 分数
static const int LEVEL_TYPE_SCORE				= 1001;
// 分数 消极
static const int LEVEL_TYPE_SCORE_NEGATIVE		= 1002;
// 步数 分数
static const int LEVEL_TYPE_STEP_SCORE			= 2001;
// 步数 收集
static const int LEVEL_TYPE_STEP_POPTYPE		= 2002;
// 步数 分数 收集
static const int LEVEL_TYPE_STEP_SCORE_POPTYPE  = 2003;
// 时间 分数
static const int LEVEL_TYPE_TIME_SCORE			= 3001;
// 时间 收集
static const int LEVEL_TYPE_TIME_POPTYPE		= 3002;
// 时间 分数 收集
static const int LEVEL_TYPE_TIME_SCORE_POPTYPE  = 3003;

#endif