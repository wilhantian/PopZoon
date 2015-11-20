#ifndef _PROLOGUE_LAYER_H_
#define _PROLOGUE_LAYER_H_

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Level/LevelDefine.h"

// 对话完成回调监听
typedef std::function<void(cocos2d::Ref*)> ccPrologueDoneCallback;

/**
 * 对白层
 */
class PrologueLayer : public cocos2d::LayerColor
{
public:
	static PrologueLayer* create();

	// 设置游戏剧本
	void setGameScript(GameScript gameScript);

	// 设置是否可以跳过
	void setCanSkip(bool canSkip);

	// 跳过
	void skip();

	// 下一个对话
	void nextPrologue();

	// 开始表演
	void startShowTime();

	// 完成对话回调见提供
	void addPrologueDoneListener(const ccPrologueDoneCallback& callback);

protected:
	virtual bool init();
	PrologueLayer();

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);

protected:
	GameScript m_gameScript;		// 剧本
	int		   m_nowPrologueIndex;	// 当前对白下标
	int		   m_nowWordIndex;		// 当前语句下标

	cocos2d::ui::Text* m_pTextName;
	cocos2d::ui::Text* m_pTextContent;

	cocos2d::ui::ImageView* m_pBk;
	cocos2d::ui::ImageView* m_pHeadFile;
	cocos2d::ui::ImageView* m_pImageViewNameBk;

	cocos2d::ui::Button* m_pBtnSkip;

	ccPrologueDoneCallback m_prologueDoneCallback;

	std::string m_strLastHeadFile;
};

#endif