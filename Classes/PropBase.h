/************************************************************************** 
* Copyright (c) 2015, pxbomb, All rights reserved. 

* File		: PropBase.h
* Date		: 2015/06/17 21:18  
* Author	: WilhanTian
* Email		: wilhan.tian@gmail.com
* Depict	: prop base class
**************************************************************************/
#ifndef _PROPBASE_H_
#define _PROPBASE_H_

class Zoo;

class PropBase
{
public:
	virtual void onHandle(Zoo* pZoo, int iRow, int iCol) = 0;
};

#endif // _PROPBASE_H_/