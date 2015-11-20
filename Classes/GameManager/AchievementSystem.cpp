#include "AchievementSystem.h"
//-------------------------------------------
USING_NS_CC;
//-------------------------------------------
std::string FormatKey(int iID)
{
	char buf[28];
	sprintf(buf, "achievement_%d", iID);
	return buf;
}
//-------------------------------------------
AchievementSystem* AchievementSystem::getInstance()
{
	if (s_instance == NULL)
	{
		s_instance = new AchievementSystem();
		s_instance->init();
	}
	return s_instance;
}
//-------------------------------------------
void AchievementSystem::destoryInstance()
{
	s_instance->save();
	CC_SAFE_DELETE(s_instance);
}
//-------------------------------------------
void AchievementSystem::init()
{
	// 初始化成就依赖
	initAchievementRelyOn();

	// 初始化成就状态
	initAchievementInfo();
}
//-------------------------------------------
void AchievementSystem::initAchievementRelyOn()
{
	// TODO
	std::string strFilePath = FileUtils::getInstance()->getWritablePath() + "/achievementRelyOn.json";
	
	bool isExist = FileUtils::getInstance()->isFileExist(strFilePath);

	if (!isExist)
	{
		strFilePath = FileUtils::getInstance()->fullPathForFilename("Data/achievementRelyOn.json");
	}

	std::string strJson = FileUtils::getInstance()->getStringFromFile(strFilePath);

	m_relyDoc;
	m_relyDoc.Parse<0>(strJson.c_str());	// 解析JSON字符串

	m_uiClickFailCount  = m_relyDoc["m_uiClickFailCount"].GetInt();
	m_uiGetScore		= m_relyDoc["m_uiGetScore"].GetInt();
	m_uiCutScore		= m_relyDoc["m_uiCutScore"].GetInt();
	m_uiUsePropCount	= m_relyDoc["m_uiUsePropCount"].GetInt();
	m_uiWatchADCount	= m_relyDoc["m_uiWatchADCount"].GetInt();
	m_uiEnterGameCount	= m_relyDoc["m_uiEnterGameCount"].GetInt();
	m_uiGameWinCount	= m_relyDoc["m_uiGameWinCount"].GetInt();
	m_uiGameFailCount	= m_relyDoc["m_uiGameFailCount"].GetInt();
	m_uiInAppMis		= m_relyDoc["m_uiInAppMis"].GetInt();
	m_uiCutCoin			= m_relyDoc["m_uiCutCoin"].GetInt();
	m_uiGetCoin			= m_relyDoc["m_uiGetCoin"].GetInt();
	m_uiClickLogoCount	= m_relyDoc["m_uiClickLogoCount"].GetInt();

	rapidjson::Value& valuePopCount = m_relyDoc["m_mPopTypeCount"];
	for (int i = 0; i < valuePopCount.Size(); i+=2)
	{
		int iType = valuePopCount[i].GetInt();
		int iCount = valuePopCount[i+1].GetInt();

		m_mPopTypeCount[iType] = iCount;
	}

	rapidjson::Value& valueLevelCount = m_relyDoc["m_uiIntoLevelCount"];
	for (int i = 0; i < valueLevelCount.Size(); i+=2)
	{
		int iType = valueLevelCount[i].GetInt();
		int iCount = valueLevelCount[i + 1].GetInt();

		m_uiIntoLevelCount[iType] = iCount;
	}
}
//-------------------------------------------
void AchievementSystem::initAchievementInfo()
{
	// 载入成就配置文件
	m_tagAchievementInfos = loadAchievementInfosFile("Data/achiecement.json");

	// 初始化成就状态
	for (int i = 0; i < m_tagAchievementInfos.size(); i++)
	{
		bool isHave = UserDefault::getInstance()->getBoolForKey(FormatKey(m_tagAchievementInfos.at(i).iID).c_str(), false);
		m_tagAchievementInfos.at(i).isOK = isHave;
	}
}
//-------------------------------------------
void AchievementSystem::save()
{
	//======================================
	// 修改json缓存
	//======================================
	m_relyDoc["m_uiClickFailCount"].SetInt(m_uiClickFailCount);
	m_relyDoc["m_uiGetScore"].SetInt(m_uiGetScore);
	m_relyDoc["m_uiCutScore"].SetInt(m_uiCutScore);
	m_relyDoc["m_uiUsePropCount"].SetInt(m_uiUsePropCount);
	m_relyDoc["m_uiWatchADCount"].SetInt(m_uiWatchADCount);
	m_relyDoc["m_uiEnterGameCount"].SetInt(m_uiEnterGameCount);
	m_relyDoc["m_uiGameWinCount"].SetInt(m_uiGameWinCount);
	m_relyDoc["m_uiGameFailCount"].SetInt(m_uiGameFailCount);
	m_relyDoc["m_uiInAppMis"].SetInt(m_uiInAppMis);
	m_relyDoc["m_uiCutCoin"].SetInt(m_uiCutCoin);
	m_relyDoc["m_uiGetCoin"].SetInt(m_uiGetCoin);
	m_relyDoc["m_uiClickLogoCount"].SetInt(m_uiClickLogoCount);

	rapidjson::Document::AllocatorType& allocator = m_relyDoc.GetAllocator();
	{
		std::map<int, unsigned int>::iterator it = m_mPopTypeCount.begin();
		rapidjson::Value& array1 = m_relyDoc["m_mPopTypeCount"];
		int arrSize = array1.Size();

		for (int i = 0; i < arrSize; i++)
		{
			array1.PopBack();
		}

		for (; it != m_mPopTypeCount.end(); ++it)
		{
			array1.PushBack(it->first, allocator);
			array1.PushBack(it->second, allocator);
		}
	}
	
	{	
		std::map<int, unsigned int>::iterator it = m_uiIntoLevelCount.begin();
		rapidjson::Value& array1 = m_relyDoc["m_uiIntoLevelCount"];
		int arrSize = array1.Size();

		for (int i = 0; i < arrSize; i++)
		{
			array1.PopBack();
		}

		for (; it != m_uiIntoLevelCount.end(); ++it)
		{
			array1.PushBack(it->first, allocator);
			array1.PushBack(it->second, allocator);
		}
	}
	
	//======================================
	// 写入文件
	//======================================
	std::string strFilePath = FileUtils::getInstance()->getWritablePath() + "/achievementRelyOn.json";

	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	m_relyDoc.Accept(writer);
	
	//向本地写入文件
	FILE *fp = fopen(strFilePath.c_str(), "wb");
	if (fp)
	{
		fwrite(buffer.GetString(), 1, strlen(buffer.GetString()), fp);
		fclose(fp);
	}
	else
	{
		log("Write failed");
	}
}
//-------------------------------------------
std::vector<AchievementInfo> AchievementSystem::getAchievementInfos()
{
	return m_tagAchievementInfos;
}
//-------------------------------------------
void AchievementSystem::setAchievementIsOK(int iID, bool isOK)
{
	for (int i = 0; i < m_tagAchievementInfos.size(); i++)
	{
		if (m_tagAchievementInfos.at(i).iID == iID)
		{
			m_tagAchievementInfos.at(i).isOK = isOK;

			// 保存
			UserDefault::getInstance()->setBoolForKey(FormatKey(iID).c_str(), isOK);

			return;
		}
	}
}
//-------------------------------------------
bool AchievementSystem::isAchievementOK(int iID)
{
	for (int i = 0; i < m_tagAchievementInfos.size(); i++)
	{
		if (m_tagAchievementInfos.at(i).iID == iID)
		{
			return m_tagAchievementInfos.at(i).isOK;
		}
	}

	return false;
}
//-------------------------------------------
void AchievementSystem::triggerClickFailZoonOnce()
{
	m_uiClickFailCount++;

	log("triggerClickFailZoonOnce : %d", m_uiClickFailCount);

	if (m_uiClickFailCount == 20)
	{
		// TODO 手残党
		if (!getAchievementInfo(ShouCanDang).isOK)
		{
			setAchievementIsOK(ShouCanDang, true);
		}
	}

	else if (m_uiClickFailCount == 60)
	{
		// TODO 手残之王
		if (!getAchievementInfo(ShouCanZhiWang).isOK)
		{
			setAchievementIsOK(ShouCanZhiWang, true);
		}
	}

	else if (m_uiClickFailCount == 200)
	{
		// TODO 手残至尊
		if (!getAchievementInfo(ShouCanZhiZun).isOK)
		{
			setAchievementIsOK(ShouCanZhiZun, true);
		}
	}
}
//-------------------------------------------
void AchievementSystem::triggerPopedZoon(int iType, int iCount)
{
	m_mPopTypeCount[iType] += (unsigned int)iCount;
}
//-------------------------------------------
void AchievementSystem::checkPopedZoon()
{
	int allCount = 0;
	std::map<int, unsigned int>::iterator it;
	for (it = m_mPopTypeCount.begin(); it != m_mPopTypeCount.end(); ++it)
	{
		allCount += it->second;
	}

	log("checkPopedZoon : iCountAll=%d", allCount);

	// TODO 动物出击
	if (allCount >= 100 && !getAchievementInfo(DongWuChuJi).isOK)
	{
		setAchievementIsOK(DongWuChuJi, true);
	}

	// TODO 动物暴动
	else if (allCount >= 250 && !getAchievementInfo(DongWuBaoDong).isOK)
	{
		setAchievementIsOK(DongWuBaoDong, true);
	}

	// TODO 本拉灯
	else if (allCount >= 500 && !getAchievementInfo(BenLaDeng).isOK)
	{
		setAchievementIsOK(BenLaDeng, true);
	}

	// TODO 2012
	else if (allCount >= 1000 && !getAchievementInfo(ShiJieMoRi2012).isOK)
	{
		setAchievementIsOK(ShiJieMoRi2012, true);
	}
}
//-------------------------------------------
void AchievementSystem::triggerGetScore(int iScore)
{
	m_uiGetScore += (unsigned int)iScore;
}
//-------------------------------------------
void AchievementSystem::checkGetScore()
{
	log("checkGetScore : GetScore=%d", m_uiGetScore);

	// TODO 高考状元
	if (m_uiGetScore >= 10000 && !getAchievementInfo(GaoKaoZhuangYuan).isOK)
	{
		setAchievementIsOK(GaoKaoZhuangYuan, true);
	}

	// TODO 蓝翔归来
	if (m_uiGetScore >= 30000 && !getAchievementInfo(LanXiangGuiLai).isOK)
	{
		setAchievementIsOK(LanXiangGuiLai, true);
	}

	// TODO 挖掘机天才
	if (m_uiGetScore >= 80000 && !getAchievementInfo(WaJueJiTianCai).isOK)
	{
		setAchievementIsOK(WaJueJiTianCai, true);
	}

	// TODO 霍格沃兹
	if (m_uiGetScore >= 200000 && !getAchievementInfo(HuoGeWoZi).isOK)
	{
		setAchievementIsOK(HuoGeWoZi, true);
	}
}
//-------------------------------------------
void AchievementSystem::triggerCutScore(int iScore)
{
	m_uiCutScore += (unsigned int)iScore;
}
//-------------------------------------------
void AchievementSystem::checkCutScore()
{
	// TODO 惨目忍睹
	if (m_uiCutScore >= 1000 && !getAchievementInfo(CanMuRenDu).isOK)
	{
		setAchievementIsOK(CanMuRenDu, true);
	}

	// TODO 脑残联盟
	if (m_uiCutScore >= 5000 && !getAchievementInfo(NaoCanLianMeng).isOK)
	{
		setAchievementIsOK(NaoCanLianMeng, true);
	}

	// TODO 大傻X
	if (m_uiCutScore >= 10000 && !getAchievementInfo(DaShaBi).isOK)
	{
		setAchievementIsOK(DaShaBi, true);
	}
}
//-------------------------------------------
void AchievementSystem::triggerUseProp()
{
	m_uiUsePropCount++;
}
//-------------------------------------------
void AchievementSystem::triggerWatchAD()
{
	m_uiWatchADCount++;
}
//-------------------------------------------
void AchievementSystem::triggerEnterGame()
{
	m_uiEnterGameCount++;

	// TODO 蝶恋花
	if (m_uiEnterGameCount == 10 && !getAchievementInfo(DieLianHua).isOK)
	{
		setAchievementIsOK(DieLianHua, true);
	}

	// TODO 依依不舍
	else if (m_uiEnterGameCount == 25 && !getAchievementInfo(YiYiBuShe).isOK)
	{
		setAchievementIsOK(YiYiBuShe, true);
	}

	// TODO 全民女神
	else if (m_uiEnterGameCount == 70 && !getAchievementInfo(QuanMinNvShen).isOK)
	{
		setAchievementIsOK(QuanMinNvShen, true);
	}
}
//-------------------------------------------
void AchievementSystem::triggerGameWin()
{
	m_uiGameWinCount++;

	// TODO 胜利之歌
	if (m_uiGameWinCount == 10 && !getAchievementInfo(ShengLiZhiGe).isOK)
	{
		setAchievementIsOK(ShengLiZhiGe, true);
	}

	// TODO 吊炸天
	else if (m_uiGameWinCount == 30 && !getAchievementInfo(DiaoZhaTian).isOK)
	{
		setAchievementIsOK(DiaoZhaTian, true);
	}
	
	// TODO 钓鱼岛是中国的
	else if (m_uiGameWinCount == 100 && !getAchievementInfo(DiaoYuDaoShiChinese).isOK)
	{
		setAchievementIsOK(DiaoYuDaoShiChinese, true);
	}
}
//-------------------------------------------
void AchievementSystem::triggerGameFail()
{
	m_uiGameFailCount++;

	// TODO 再接再厉
	if (m_uiGameFailCount == 10 && !getAchievementInfo(ZaiJieZaiLi).isOK)
	{
		setAchievementIsOK(ZaiJieZaiLi, true);
	}

	// TODO 万夫莫敌
	else if (m_uiGameFailCount == 30 && !getAchievementInfo(WanFuMoDi).isOK)
	{
		setAchievementIsOK(WanFuMoDi, true);
	}

	// TODO 干了这碗热翔
	else if (m_uiGameFailCount == 100 && !getAchievementInfo(GanLeZheWanReXiang).isOK)
	{
		setAchievementIsOK(GanLeZheWanReXiang, true);
	}
}
//-------------------------------------------
void AchievementSystem::triggerInAppOneMis()
{ 
	m_uiInAppMis++;
}
//-------------------------------------------
void AchievementSystem::triggerCutCoin(int iCoin)
{
	m_uiCutCoin += (unsigned int)iCoin;
}
//-------------------------------------------
void AchievementSystem::triggerGetCoin(int iCoin)
{
	m_uiGetCoin += (unsigned int)iCoin;
}
//-------------------------------------------
void AchievementSystem::triggerIntoLevel(int iLevelId)
{
	m_uiIntoLevelCount[iLevelId] = m_uiIntoLevelCount[iLevelId] + 1;

	// 肥而不腻
	if (m_uiIntoLevelCount[iLevelId] == 20 && !getAchievementInfo(FeiErBuLi).isOK)
	{
		setAchievementIsOK(FeiErBuLi, true);
	}
}
//-------------------------------------------
void AchievementSystem::triggerClickLogo()
{
	m_uiClickLogoCount++;
}
//-------------------------------------------
std::vector<AchievementInfo> AchievementSystem::loadAchievementInfosFile(std::string filePath)
{
	std::vector<AchievementInfo> ais;

	// 获取真实路径
	std::string strFileFile = FileUtils::getInstance()->fullPathForFilename(filePath);

	// 获取JSON字符串
	std::string strJson = FileUtils::getInstance()->getStringFromFile(strFileFile);

	rapidjson::Document doc;
	doc.Parse<0>(strJson.c_str());	// 解析JSON字符串

	rapidjson::Value& value = doc["achiecement"];

	for (int i = 0; i < value.Size(); i++)
	{
		AchievementInfo ai;

		rapidjson::Value& valueBuf = value[i];

		ai.iID				= valueBuf["id"].GetInt();
		ai.strTitle			= valueBuf["title"].GetString();
		ai.strDescription	= valueBuf["description"].GetString();
		ai.strIconSmallPath = valueBuf["iconSmallPath"].GetString();
		ai.strIconOKPath	= valueBuf["iconOKPath"].GetString();
		ai.strIconNOPath	= valueBuf["iconNOPath"].GetString();
		ai.strCardPath		= valueBuf["cardPath"].GetString();
		ai.strContent		= valueBuf["content"].GetString();

		ais.push_back(ai);
	}

	return ais;
}
//-------------------------------------------
AchievementInfo AchievementSystem::getAchievementInfo(int iID)
{
	for (int i = 0; i < m_tagAchievementInfos.size(); i++)
	{
		if (m_tagAchievementInfos.at(i).iID == iID)
		{
			return m_tagAchievementInfos.at(i);
		}
	}

	return AchievementInfo();
}
//-------------------------------------------
AchievementSystem* AchievementSystem::s_instance = NULL;
//-------------------------------------------