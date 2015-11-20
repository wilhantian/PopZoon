#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "AppInclude.h"

/**
 * 游戏场景
 */
class GameScene : public cocos2d::Scene
{
public:
    static GameScene* create(std::string strFilePath);
    
    // 胜利
    void win();
    
    // 失败
    void fail();
    
    // 暂停
    void pause();
    
    // 开始
    void play();
    
    // 重玩
    void replay();
    
    // 回调
    void onPopBeginListener(Zoo* pZoo);
    void onZooOnePopedListener(Zoo* pZoo, ZoonPopObj zoonObj);
    void onOrderEndedListener(Zoo* pZoo);
    void onPopEndedListener(Zoo* pZoo);
    
    void onScoreChangedLisener(int iScore);
    void onStepChangedLisener(int iStep);
    
    virtual void onEnterTransitionDidFinish();
protected:
    virtual bool init(std::string strFilePath);
    
    void initZoo(std::string strFilePath);
    
    void initGameManager();
    
    virtual void onExit();
    
    ~GameScene();
    
protected:
    cocos2d::Node* m_hud;
    
    int m_iLevelType;
    int m_iTime;
    
    bool m_isGameOver;
    bool m_isPasue;
    bool m_isFirstEnter;
    
    LevelInfo_1001 m_levelInfo_1001;
    LevelInfo_1002 m_levelInfo_1002;
    LevelInfo_2001 m_levelInfo_2001;
    LevelInfo_2002 m_levelInfo_2002;
    LevelInfo_2003 m_levelInfo_2003;
    LevelInfo_3001 m_levelInfo_3001;
    LevelInfo_3002 m_levelInfo_3002;
    LevelInfo_3003 m_levelInfo_3003;
    
    Zoo* m_pZoo;
};

#endif