#include "GameScene.h"
//-----------------------------------------------------
USING_NS_CC;
//-----------------------------------------------------
GameScene* GameScene::create(std::string strFilePath)
{
    GameScene* gs = new GameScene();
    if (gs && gs->init(strFilePath))
    {
        gs->autorelease();
        return gs;
    }
    CC_SAFE_DELETE(gs);
    return NULL;
}
//-----------------------------------------------------
GameScene::~GameScene()
{
    MsgEvent::removeEvent(MsgOnPropChanged);
}
//-----------------------------------------------------
bool GameScene::init(std::string strFilePath)
{
    if (!Scene::init())
        return false;
    
    Size winSize = Director::getInstance()->getWinSize();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // 背景
    Sprite* pBk = Sprite::create("bk.png");
    pBk->setPosition(visibleSize / 2);
    addChild(pBk);
    
    //==============
    // TEST
    //==============
    auto as = AchievementSystem::getInstance()->getAchievementInfos();
    for (int i = 0; i < as.size(); i++)
    {
        log("---------------------");
        log("id:%d", as.at(i).iID);
        log("isOK:%d", as.at(i).isOK);
        log("strCardPath:%s", as.at(i).strCardPath.c_str());
        log("strContent:%s", as.at(i).strContent.c_str());
        log("strDescription:%s", as.at(i).strDescription.c_str());
        log("strIconNOPath:%s", as.at(i).strIconNOPath.c_str());
        log("strIconOKPath:%s", as.at(i).strIconOKPath.c_str());
        log("strIconSmallPath:%s", as.at(i).strIconSmallPath.c_str());
        log("strTitle:%s", as.at(i).strTitle.c_str());
    }
    
    m_iTime = 0;
    m_isGameOver = false;
    m_isPasue = false;
    m_isFirstEnter = true;
    
    initZoo(strFilePath);
    initGameManager();
    
    EffectManager::getInstance();
    
    play();
    
    //==============
    // HUD
    //==============
    HUDLayer* hudLayer = HUDLayer::create();
    this->addChild(hudLayer);
    
    // 监听技能变更事件
    MsgEvent::addEvent(MsgOnPropChanged, [=](EventCustom* eventCustom)
    {
        int data = *(int*)eventCustom->getUserData();
        CCLOG("%d", data);
        
        if(data == PropType_Bomb){
//            m_pZoo->setProp(PropBomb::create());
        }
        else if(data == PropType_Row){
            m_pZoo->setProp(new PropRow());
        }

    });
    
    return true;
}
//-----------------------------------------------------
void GameScene::onEnterTransitionDidFinish()
{
    if (m_isFirstEnter)
    {
        m_isFirstEnter = false;
        
        // 进入游戏成就
        AchievementSystem::getInstance()->triggerEnterGame();
        
        // 关卡进入成就
        AchievementSystem::getInstance()->triggerIntoLevel(m_iLevelType);
    }
}
//-----------------------------------------------------
void GameScene::initZoo(std::string strFilePath)
{
    Size winSize = Director::getInstance()->getWinSize();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    BaseLevelInfo tagBaseLevelInfo = LevelManager::getBaseLevelInfo(strFilePath);
    
    // 元素概率
    ProbabilityCalculator pc;
    std::vector<TypeProbability> tagTP = tagBaseLevelInfo.tagTypeProbabilitys;
    for (int i = 0; i < tagTP.size(); i++)
    {
        TypeProbability tp = tagTP.at(i);
        pc.addEventFactor(tp.iType, tp.iProbability);
    }
    
    // 关卡类型
    m_iLevelType = atoi(tagBaseLevelInfo.strType.c_str());
    
    float factor;
    float factorWidth = winSize.width / visibleSize.width;
    float factorHeight = visibleSize.height / visibleSize.height;
    
    if (factorHeight > factorWidth)
        factor = factorHeight;
    else
        factor = factorWidth;
    
    m_pZoo = Zoo::create(10, 10, pc);
    m_pZoo->setAnchorPoint(Vec2(0.5, 0.5));
    m_pZoo->setPosition(Vec2(320, 960 / 2 - 64 / 2));
    m_pZoo->setSpace(5);
    m_pZoo->setScale(1 / factor);
    this->addChild(m_pZoo);
    
    // 监听事件
    m_pZoo->setOnOnePopedListener(CC_CALLBACK_2(GameScene::onZooOnePopedListener, this));
    m_pZoo->setOnOrderEndedListener(CC_CALLBACK_1(GameScene::onOrderEndedListener, this));
    m_pZoo->setOnPopBeginListener(CC_CALLBACK_1(GameScene::onPopBeginListener, this));
    m_pZoo->setOnPopEndedListener(CC_CALLBACK_1(GameScene::onPopEndedListener, this));
    
    // 剧情
    PrologueLayer* pPrologueLayer = PrologueLayer::create();
    pPrologueLayer->setCanSkip(true);
    this->addChild(pPrologueLayer);
    
    if (m_iLevelType == LEVEL_TYPE_SCORE)
    {
        m_pZoo->setGameType(Zoo::GameType::NO_LIMIT);
        m_levelInfo_1001 = LevelManager::getLevelInfoForType1001(strFilePath);
        pPrologueLayer->setGameScript(m_levelInfo_1001.tagPrologueInfos);
    }
    else if (m_iLevelType == LEVEL_TYPE_SCORE_NEGATIVE)
    {
        m_pZoo->setGameType(Zoo::GameType::NO_LIMIT);
        m_levelInfo_1002 = LevelManager::getLevelInfoForType1002(strFilePath);
        pPrologueLayer->setGameScript(m_levelInfo_1002.tagPrologueInfos);
    }
    else if (m_iLevelType == LEVEL_TYPE_STEP_SCORE)
    {
        m_pZoo->setGameType(Zoo::GameType::STEP_LIMIT);
        m_levelInfo_2001 = LevelManager::getLevelInfoForType2001(strFilePath);
        pPrologueLayer->setGameScript(m_levelInfo_2001.tagPrologueInfos);
        
        GameManager::getInstance()->setStep(m_levelInfo_2001.iStep);
    }
    else if (m_iLevelType == LEVEL_TYPE_STEP_POPTYPE)
    {
        m_pZoo->setGameType(Zoo::GameType::STEP_LIMIT);
        m_levelInfo_2002 = LevelManager::getLevelInfoForType2002(strFilePath);
        pPrologueLayer->setGameScript(m_levelInfo_2002.tagPrologueInfos);
        
        GameManager::getInstance()->setStep(m_levelInfo_2002.iStep);
        GameManager::getInstance()->setTaskInfo(m_levelInfo_2002.tagTask);
    }
    else if (m_iLevelType == LEVEL_TYPE_STEP_SCORE_POPTYPE)
    {
        m_pZoo->setGameType(Zoo::GameType::STEP_LIMIT);
        m_levelInfo_2003 = LevelManager::getLevelInfoForType2003(strFilePath);
        pPrologueLayer->setGameScript(m_levelInfo_2003.tagPrologueInfos);
        
        GameManager::getInstance()->setStep(m_levelInfo_2003.iStep);
        GameManager::getInstance()->setTaskInfo(m_levelInfo_2003.tagTask);
    }
    else if (m_iLevelType == LEVEL_TYPE_TIME_SCORE)
    {
        m_pZoo->setGameType(Zoo::GameType::TIME_LIMIT);
        m_levelInfo_3001 = LevelManager::getLevelInfoForType3001(strFilePath);
        pPrologueLayer->setGameScript(m_levelInfo_3001.tagPrologueInfos);
        
        GameManager::getInstance()->setTime(m_levelInfo_3001.iTime);
    }
    else if (m_iLevelType == LEVEL_TYPE_TIME_POPTYPE)
    {
        m_pZoo->setGameType(Zoo::GameType::TIME_LIMIT);
        m_levelInfo_3002 = LevelManager::getLevelInfoForType3002(strFilePath);
        pPrologueLayer->setGameScript(m_levelInfo_3002.tagPrologueInfos);
        
        GameManager::getInstance()->setTime(m_levelInfo_3002.iTime);
        GameManager::getInstance()->setTaskInfo(m_levelInfo_3002.tagTask);
    }
    else if (m_iLevelType == LEVEL_TYPE_TIME_SCORE_POPTYPE)
    {
        m_pZoo->setGameType(Zoo::GameType::TIME_LIMIT);
        m_levelInfo_3003 = LevelManager::getLevelInfoForType3003(strFilePath);
        pPrologueLayer->setGameScript(m_levelInfo_3003.tagPrologueInfos);
        
        GameManager::getInstance()->setTime(m_levelInfo_3003.iTime);
        GameManager::getInstance()->setTaskInfo(m_levelInfo_3003.tagTask);
        
        // TODO
        // 监听计时管理器
        // 监听分数管理器
        // 监听消除统计管理器
    }
    
    // 播放剧情
    pPrologueLayer->startShowTime();
}
//-----------------------------------------------------
void GameScene::initGameManager()
{
    GameManager::getInstance()->setLevelType(m_iLevelType);
    GameManager::getInstance()->setOnScoreChangedListener(CC_CALLBACK_1(GameScene::onScoreChangedLisener, this));
    GameManager::getInstance()->setOnStepChangedListener(CC_CALLBACK_1(GameScene::onStepChangedLisener, this));
}
//-----------------------------------------------------
void GameScene::onExit()
{
    Scene::onExit();
    
    GameManager::destoryInstance();
    EffectManager::destoryInstance();
    
    MsgEvent::removeEvent(MsgPointChange);
}
//-----------------------------------------------------
void GameScene::win()
{
    // TODO
    // 弹出胜利窗口
    
    if (m_isGameOver)
        return;
    
    m_isGameOver = true;
    
    // 胜利成就
    AchievementSystem::getInstance()->triggerGameWin();
    
    log("=======WIN=======");
}
//-----------------------------------------------------
void GameScene::fail()
{
    // TODO
    // 弹出失败窗口
    
    if (m_isGameOver)
        return;
    
    m_isGameOver = true;
    
    // 失败成就
    AchievementSystem::getInstance()->triggerGameFail();
    
    log("=======FAIL=======");
}
//-----------------------------------------------------
void GameScene::pause()
{
    // TODO
    // 弹出暂停窗口
    
    if (m_isPasue)
        return;
    
    m_isPasue = true;
    
    m_pZoo->onExit();
}
//-----------------------------------------------------
void GameScene::play()
{
    // TODO
    // 开始玩
    
    // 开始计时
    this->schedule([=](float fTime)
                   {
                       // 计时++
                       m_iTime++;
                       
                       if (m_iLevelType == LEVEL_TYPE_TIME_SCORE &&
                           m_iTime >= m_levelInfo_3001.iTime)
                       {
                           fail();
                       }
                       
                       if (m_iLevelType == LEVEL_TYPE_TIME_POPTYPE &&
                           m_iTime >= m_levelInfo_3002.iTime)
                       {
                           fail();
                       }
                       
                       if (m_iLevelType == LEVEL_TYPE_TIME_SCORE_POPTYPE &&
                           m_iTime >= m_levelInfo_3003.iTime)
                       {
                           fail();
                       }
                       
                   }, 1.0f, "play");
}
//-----------------------------------------------------
void GameScene::replay()
{
    // TODO
    // 重新开始
    
    if (!m_isPasue)
        return;
    
    m_isPasue = false;
    
    m_pZoo->onEnter();
}
//-----------------------------------------------------
void GameScene::onZooOnePopedListener(Zoo* pZoo, ZoonPopObj zoonObj)
{
    int iType = zoonObj.zoon->getType();
    int iScore;
    
    if (m_iLevelType == LEVEL_TYPE_SCORE_NEGATIVE)
    {
        if (m_levelInfo_1002.iNegativeType == iType)
        {
            iScore = TalentManager::getInstance()->getConputeNegativeScore(iType, zoonObj.index);
            GameManager::getInstance()->cupStep(-iScore);		// 添加分数到分数管理器
            
            AchievementSystem::getInstance()->triggerCutScore(iScore);	// 扣分成就
        }
        else
        {
            iScore = TalentManager::getInstance()->getComputeScore(iType, zoonObj.index);
            GameManager::getInstance()->addScore(iScore);		// 添加分数到分数管理器
            
            AchievementSystem::getInstance()->triggerGetScore(iScore);	// 分数成就
        }
    }
    else
    {
        iScore = TalentManager::getInstance()->getComputeScore(iType, zoonObj.index);
        GameManager::getInstance()->addScore(iScore);			// 添加分数到分数管理器
        
        AchievementSystem::getInstance()->triggerGetScore(iScore);	// 分数成就
    }
    
    // 统计收集类型
    GameManager::getInstance()->addCollectType(iType);
    
    // 播放各种特技
    EffectManager::getInstance()->playBombEffect(zoonObj.zoon);
    EffectManager::getInstance()->playFlyScore(zoonObj.zoon, iScore);
    
    // 成就计数
    AchievementSystem::getInstance()->triggerPopedZoon(iType, 1);
}
//-----------------------------------------------------
void GameScene::onOrderEndedListener(Zoo* pZoo)
{
    // TODO
    // 判断是否完成游戏
    //	  查询是否可消除
    //    查询分数
    //	  查询步数
    
    if (m_iLevelType == LEVEL_TYPE_SCORE)
    {	// 是否可继续消除||是否达到分数
        if (!pZoo->isCanPop())
        {
            int iNowScore = GameManager::getInstance()->getScore();
            if (iNowScore >= m_levelInfo_1001.iPassScore)
            {
                win();
            }
            else
            {
                fail();
            }
        }
    }
    
    else if (m_iLevelType == LEVEL_TYPE_SCORE_NEGATIVE)
    {	// 是否可继续消除||是否达成分数
        if (!pZoo->isCanPop())
        {
            int iNowScore = GameManager::getInstance()->getScore();
            if (iNowScore >= m_levelInfo_1002.iPassScore)
            {
                win();
            }
            else
            {
                fail();
            }
        }
    }
    
    else if (m_iLevelType == LEVEL_TYPE_STEP_SCORE)
    {	// 是否可以继续消除||是否步数为0||是否达到分数
        if (GameManager::getInstance()->getStep() <= 0)
        {
            fail();
            return;
        }
        
        if (!pZoo->isCanPop())
        {
            int iNowScore = GameManager::getInstance()->getScore();
            if (iNowScore >= m_levelInfo_2001.iPassScore)
            {
                win();
            }
            else
            {
                fail();
            }
        }
    }
    
    else if (m_iLevelType == LEVEL_TYPE_STEP_POPTYPE)
    {	//是否可以继续消除||是否步数为0||是否收集完
        if (GameManager::getInstance()->getStep() <= 0)
        {
            fail();
            return;
        }
        
        if (!pZoo->isCanPop())
        {
            bool isTaskOk = true;
            std::vector<TaskInfo> tasks = GameManager::getInstance()->getTaskInfo();
            
            for (int i = 0; i < tasks.size(); i++)
            {
                TaskInfo buf = tasks.at(i);
                if (buf.iCount > GameManager::getInstance()->getCollectType(buf.iType))
                {
                    isTaskOk = false;
                    break;
                }
            }
            
            if (isTaskOk)
                win();
            else
                fail();
        }
    }
    
    else if (m_iLevelType == LEVEL_TYPE_STEP_SCORE_POPTYPE)
    {	//是否可以继续消除||是否步数为0||是否收集完||是否达到分数
        if (GameManager::getInstance()->getStep() <= 0)
        {
            fail();
            return;
        }
        
        if (!pZoo->isCanPop())
        {
            bool isTaskOk = true;
            std::vector<TaskInfo> tasks = GameManager::getInstance()->getTaskInfo();
            
            for (int i = 0; i < tasks.size(); i++)
            {
                TaskInfo buf = tasks.at(i);
                if (buf.iCount > GameManager::getInstance()->getCollectType(buf.iType))
                {
                    isTaskOk = false;
                    break;
                }
            }
            
            int iNowScore = GameManager::getInstance()->getScore();
            
            if (isTaskOk && iNowScore >= m_levelInfo_2003.iPassScore)
                win();
            else
                fail();
        }
    }
    
    else if (m_iLevelType == LEVEL_TYPE_TIME_SCORE)
    {	//是否可以继续消除||是否到达时间||是否到达分数
        
        if (!pZoo->isCanPop())
        {
            fail();
            return;
        }
        
        int iNowScore = GameManager::getInstance()->getScore();
        if (iNowScore >= m_levelInfo_3001.iPassScore)
            win();
    }
    
    else if (m_iLevelType == LEVEL_TYPE_TIME_POPTYPE)
    {	// 是否可以继续消除||是否到达时间||是否达到收集OK
        if (!pZoo->isCanPop())
        {
            fail();
            return;
        }
        
        bool isTaskOk = true;
        std::vector<TaskInfo> tasks = GameManager::getInstance()->getTaskInfo();
        
        for (int i = 0; i < tasks.size(); i++)
        {
            TaskInfo buf = tasks.at(i);
            if (buf.iCount > GameManager::getInstance()->getCollectType(buf.iType))
            {
                isTaskOk = false;
                break;
            }
        }
        
        if (isTaskOk)
            win();
    }
    
    else if (m_iLevelType == LEVEL_TYPE_TIME_SCORE_POPTYPE)
    {	//是否可以继续消除||是否到达时间||是否达到分数||是否收集OK
        if (!pZoo->isCanPop())
        {
            fail();
            return;
        }
        
        bool isTaskOk = true;
        std::vector<TaskInfo> tasks = GameManager::getInstance()->getTaskInfo();
        
        for (int i = 0; i < tasks.size(); i++)
        {
            TaskInfo buf = tasks.at(i);
            if (buf.iCount > GameManager::getInstance()->getCollectType(buf.iType))
            {
                isTaskOk = false;
                break;
            }
        }
        
        if (isTaskOk)
        {
            if (m_levelInfo_3003.iPassScore <= GameManager::getInstance()->getScore())
                win();
        }
    }
}
//-----------------------------------------------------
void GameScene::onScoreChangedLisener(int iScore)
{
    // TODO
    // 重新设置分数HUD
}
//-----------------------------------------------------
void GameScene::onStepChangedLisener(int iStep)
{
    // TODO
    // 重新设置步数HUD
}
//-----------------------------------------------------
void GameScene::onPopBeginListener(Zoo* pZoo)
{
    // 计步器减少
    GameManager::getInstance()->cupStep(1);
}
//-----------------------------------------------------
void GameScene::onPopEndedListener(Zoo* pZoo)
{
    // 检查消除成就
    AchievementSystem::getInstance()->checkPopedZoon();
    
    // 检查得分成就
    AchievementSystem::getInstance()->checkGetScore();
    
    // 检查扣分成就
    AchievementSystem::getInstance()->checkCutScore();
}
//-----------------------------------------------------