#ifndef _ZOON_H_
#define _ZOON_H_

#include "cocos2d.h"

enum class ZoonState
{
	Normal,
	Select
};

//动物
class Zoon : public cocos2d::Sprite
{
public:

	static Zoon* create(int iType);

	// 设置状态
	virtual void setState(ZoonState state);
	
	// 获取当前是否为选中状态
	virtual ZoonState getState();

	// 提示
	virtual void hint();

	// 销毁
	virtual void destory();

	// 是否被销毁
	virtual bool isDestory();

	// 获取类型
	virtual int getType();


	// 向左涌动一下
	virtual void swarmForLeft(float fdistance);

	// 向右涌动一下
	virtual void swarmForRight(float fdistance);

	// 向上涌动一下
	virtual void swarmForUp(float fdistance);

	// 向下涌动一下
	virtual void swarmForDown(float fdistance);

protected:

	virtual bool init(int iType);

	virtual void onEnterTransitionDidFinish();

	Zoon();

	virtual ~Zoon();

protected:
	ZoonState m_state;

	std::string m_strNormalFileName;
	std::string m_strSeleteFileName;

	int			m_iType;

	bool m_isDestory;
};

#endif