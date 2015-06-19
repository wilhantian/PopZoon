#include "WeiboAuthorize.h"
//-------------------------------------------------------------
USING_NS_CC;
//-------------------------------------------------------------
WeiboAuthorize* WeiboAuthorize::s_instance = NULL;
//-------------------------------------------------------------
WeiboAuthorize* WeiboAuthorize::getInstance()
{
	if (s_instance == NULL)
	{
		s_instance = new WeiboAuthorize();
	}
	return s_instance;
}
//-------------------------------------------------------------
void WeiboAuthorize::authorize()
{

}
//-------------------------------------------------------------
void WeiboAuthorize::setOnAuthorizedListener(const std::function<void(EnumWeiboAuthorizedType)>& callback)
{
	m_callback = callback;
}
//-------------------------------------------------------------