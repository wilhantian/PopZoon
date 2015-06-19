#ifndef _ZOON_H_
#define _ZOON_H_

#include "cocos2d.h"

enum class ZoonState
{
	Normal,
	Select
};

//¶¯Îï
class Zoon : public cocos2d::Sprite
{
public:

	static Zoon* create(int iType);

	virtual void setState(ZoonState state);
	
	virtual ZoonState getState();

	virtual void hint();

	virtual void destory();

	virtual bool isDestory();

	virtual int getType();

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