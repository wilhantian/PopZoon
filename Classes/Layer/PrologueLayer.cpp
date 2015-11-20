#include "PrologueLayer.h"
#include "AppInclude.h"
//----------------------------------------------
USING_NS_CC;
using namespace ui;
//----------------------------------------------
const Color4B TEXT_COLOR(92, 74, 0, 255);
//----------------------------------------------
PrologueLayer* PrologueLayer::create()
{
	PrologueLayer* pl = new PrologueLayer();
	if (pl && pl->init())
	{
		pl->autorelease();
		return pl;
	}
	CC_SAFE_DELETE(pl);
	return NULL;
}
//----------------------------------------------
void PrologueLayer::setGameScript(GameScript gameScript)
{
	m_gameScript = gameScript;
}
//----------------------------------------------
void PrologueLayer::setCanSkip(bool canSkip)
{
	m_pBtnSkip->setVisible(canSkip);
}
//----------------------------------------------
void PrologueLayer::startShowTime()
{
	FadeTo* pFadeTo = FadeTo::create(0.3, 196);
	this->runAction(pFadeTo);

	nextPrologue();

	{
		MoveBy* pMoveByLeft = MoveBy::create(0, Vec2(-50, 0));
		MoveBy* pMoveByRight = MoveBy::create(0.5, Vec2(50, 0));

		FadeTo* pFade_0 = FadeTo::create(0, 0);
		FadeTo* pFade_255 = FadeTo::create(0.5, 255);

		Spawn*    pSpawnLeft = Spawn::createWithTwoActions(pMoveByLeft, pFade_0);
		Spawn*    pSpawnRight = Spawn::createWithTwoActions(pMoveByRight, pFade_255);

		Sequence* pSeq = Sequence::createWithTwoActions(pSpawnLeft, pSpawnRight);
		
		m_pImageViewNameBk->runAction(pSeq);

		m_pTextName->runAction(pFade_255->clone());
	}

	{
		MoveBy* pMoveByLeft = MoveBy::create(0, Vec2(50, 0));
		MoveBy* pMoveByRight = MoveBy::create(0.5, Vec2(-50, 0));

		FadeTo* pFade_0 = FadeTo::create(0, 0);
		FadeTo* pFade_255 = FadeTo::create(0.5, 255);

		Spawn*    pSpawnLeft = Spawn::createWithTwoActions(pMoveByLeft, pFade_0);
		Spawn*    pSpawnRight = Spawn::createWithTwoActions(pMoveByRight, pFade_255);

		Sequence* pSeq = Sequence::createWithTwoActions(pSpawnLeft, pSpawnRight);

		m_pBk->runAction(pSeq);

		m_pTextContent->runAction(pFade_255->clone());
	}
	
	this->setVisible(true);
}
//----------------------------------------------
bool PrologueLayer::init()
{
	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 0)))
	{
		return false;
	}

	Size winSize = Director::getInstance()->getWinSize();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	this->setTouchEnabled(true);
	this->setSwallowsTouches(true);

	this->setVisible(false);

	//------------------------------------
	// 对话背景
	//------------------------------------
	m_pBk = ImageView::create("PrologueLayer/panel_yello.png");
	m_pBk->setAnchorPoint(Vec2(0.5, 0));
	m_pBk->setPosition(origin + Vec2(visibleSize.width / 2, 16));
	m_pBk->setScale9Enabled(true);
	m_pBk->setCapInsets(Rect(5, 5, 90, 90));
	m_pBk->setContentSize(Size(visibleSize.width - 38, 200));
	m_pBk->setCascadeColorEnabled(true);
	this->addChild(m_pBk);

	//------------------------------------
	// 对话文字
	//------------------------------------
	m_pTextContent = Text::create(" ", "", 24);
	m_pTextContent->setPosition(m_pBk->getContentSize() / 2);
	m_pTextContent->ignoreContentAdaptWithSize(false);
	m_pTextContent->setTextAreaSize(m_pBk->getContentSize() - Size(54, 36));
	m_pTextContent->setTextColor(TEXT_COLOR);
	m_pBk->addChild(m_pTextContent);

	//------------------------------------
	// 人物
	//------------------------------------
	m_pHeadFile = ImageView::create();
	m_pHeadFile->setAnchorPoint(Vec2(0.5, 0));
	m_pHeadFile->setPosition(Vec2(m_pBk->getPositionX(), m_pBk->getPositionY() + m_pBk->getContentSize().height));
	this->addChild(m_pHeadFile);

	//------------------------------------
	// 人物姓名背景
	//------------------------------------
	m_pImageViewNameBk = ImageView::create("PrologueLayer/panel_yello.png");
	m_pImageViewNameBk->setAnchorPoint(Vec2(0, 0));
	m_pImageViewNameBk->setPosition(Vec2(38, 10) + Vec2(
		  m_pBk->getPositionX() - m_pBk->getContentSize().width/2
		, m_pBk->getPositionY() + m_pBk->getContentSize().height));
	m_pImageViewNameBk->setScale9Enabled(true);
	m_pImageViewNameBk->setCapInsets(Rect(5, 5, 90, 90));
	m_pImageViewNameBk->setCascadeColorEnabled(true);
	this->addChild(m_pImageViewNameBk);

	//------------------------------------
	// 人物姓名文字
	//------------------------------------
	m_pTextName = Text::create(" ", "", 24);
	m_pTextName->setTextColor(TEXT_COLOR);
	m_pImageViewNameBk->addChild(m_pTextName);

	// 重置大小
	m_pImageViewNameBk->setContentSize(m_pTextName->getContentSize() + Size(44, 18));
	m_pTextName->setPosition(m_pImageViewNameBk->getContentSize()/2);

	//------------------------------------
	// 跳过按钮
	//------------------------------------
	m_pBtnSkip = Button::create("PrologueLayer/btn_skip_unselect.png", "PrologueLayer/btn_skip_select.png");
	m_pBtnSkip->setAnchorPoint(Vec2(1, 0));
	m_pBtnSkip->setPosition(Vec2(m_pBk->getPositionX() + m_pBk->getContentSize().width/2 - 10, m_pImageViewNameBk->getPositionY()));
	m_pBtnSkip->addClickEventListener([=](Ref* pSender)
	{
		skip();
	});
	this->addChild(m_pBtnSkip);

	//------------------------------------
	// 设置透明度
	//------------------------------------
	m_pBk->setOpacity(0);
	m_pImageViewNameBk->setOpacity(0);
	m_pHeadFile->setOpacity(0);
	m_pTextContent->setOpacity(0);
	m_pTextName->setOpacity(0);

	return true;
}
//----------------------------------------------
void PrologueLayer::skip()
{
	// 层
	FadeTo* pFadeTo = FadeTo::create(0.2, 0);
	Sequence* pSequence = Sequence::createWithTwoActions(pFadeTo, RemoveSelf::create());
	this->runAction(pSequence);

	// 名
	{
		MoveBy* pMoveByLeft = MoveBy::create(0.2, Vec2(-50, 0));
		FadeTo* pFade_0 = FadeTo::create(0.2, 0);
		Spawn*    pSpawn = Spawn::createWithTwoActions(pMoveByLeft, pFade_0);
		m_pImageViewNameBk->runAction(pSpawn);
	}

	// 对白
	{
		MoveBy* pMoveByLeft = MoveBy::create(0.2, Vec2(50, 0));
		FadeTo* pFade_0 = FadeTo::create(0.2, 0);
		Spawn*    pSpawn = Spawn::createWithTwoActions(pMoveByLeft, pFade_0);
		m_pBk->runAction(pSpawn);
	}
}
//----------------------------------------------
void PrologueLayer::nextPrologue()
{
	// 完成全部对话
	if (m_gameScript.size() <= m_nowPrologueIndex)
	{
		if (m_prologueDoneCallback)
			m_prologueDoneCallback(this);

		skip();

		return;
	}
	
	// 更换人物对白
	if (m_gameScript.at(m_nowPrologueIndex).strWords.size() <= m_nowWordIndex)
	{
		// 换人
		m_nowPrologueIndex++;
		m_nowWordIndex = 0;
		nextPrologue();
		return;
	}

	// 游戏对白信息
	PrologueInfo tagInfo = m_gameScript.at(m_nowPrologueIndex);
	m_pTextName->setText(tagInfo.strHeadName);
	m_pTextContent->setText(tagInfo.strWords.at(m_nowWordIndex));
	
	if (tagInfo.strHeadFile.empty())
	{
		m_pHeadFile->setVisible(false);
	}
	else
	{
		m_pHeadFile->setVisible(true);
		m_pHeadFile->loadTexture(tagInfo.strHeadFile);
	}

	m_nowWordIndex++;

	// 重新摆放
	m_pImageViewNameBk->setContentSize(m_pTextName->getContentSize() + Size(44, 18));
	m_pTextName->setPosition(m_pImageViewNameBk->getContentSize() / 2);

	//--------------------------
	// 动画队列
	//--------------------------
	if (tagInfo.strHeadFile.compare(m_strLastHeadFile) != 0
		/*&& !m_strLastHeadFile.empty()*/)
	{
		FadeTo* pFadeTo0   = FadeTo::create(0.0, 0);
		FadeTo* pFadeTo255 = FadeTo::create(0.5, 255);
		MoveBy* pMoveByRight = MoveBy::create(0.0, Vec2(40, 0));
		MoveBy* pMoveByLeft  = MoveBy::create(0.5, Vec2(-40, 0));

		Spawn* pSpawn1 = Spawn::createWithTwoActions(pFadeTo0, pMoveByRight);
		Spawn* pSpawn2 = Spawn::createWithTwoActions(pFadeTo255, pMoveByLeft);

		Sequence* pSequence = Sequence::createWithTwoActions(pSpawn1, pSpawn2);

		m_pHeadFile->runAction(pSequence);
	}

	// 缓存任务文件名
	m_strLastHeadFile = tagInfo.strHeadFile;
}
//----------------------------------------------
PrologueLayer::PrologueLayer()
	: m_nowPrologueIndex(0)
	, m_nowWordIndex(0)
	, m_prologueDoneCallback(nullptr)
{
}
//----------------------------------------------
void PrologueLayer::addPrologueDoneListener(const ccPrologueDoneCallback& callback)
{
	m_prologueDoneCallback = callback;
}
//----------------------------------------------
bool PrologueLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	if (!this->isVisible())
		return false;

	AudioManager::getInstance()->playClick();

	nextPrologue();
	return true;
}
//----------------------------------------------
