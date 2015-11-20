#include "LevelManager.h"
#include "json/document.h"
//--------------------------------------------------------
USING_NS_CC;
//--------------------------------------------------------
int LevelManager::getLevelType(std::string strFileFile)
{
	// 获取真实路径
	strFileFile = FileUtils::getInstance()->fullPathForFilename(strFileFile);

	// 获取JSON字符串
	std::string strJson = FileUtils::getInstance()->getStringFromFile(strFileFile);

	rapidjson::Document doc;
	doc.Parse<0>(strJson.c_str());	// 解析JSON字符串

	return atoi( doc["type"].GetString());
}
//--------------------------------------------------------
LevelInfo LevelManager::getLevelInfo(std::string strFileFile)
{
	LevelInfo tagLevelInfo;

	// 获取真实路径
	strFileFile = FileUtils::getInstance()->fullPathForFilename(strFileFile);

	// 获取JSON字符串
	std::string strJson = FileUtils::getInstance()->getStringFromFile(strFileFile);

	rapidjson::Document doc;
	doc.Parse<0>(strJson.c_str());	// 解析JSON字符串

	// 关卡ID
	tagLevelInfo.strLevelId   = doc["levelId"].GetString();
	
	// 描述
	tagLevelInfo.strDepict = doc["depict"].GetString();

	// 通过分数
	tagLevelInfo.iPassScore = doc["passScore"].GetInt();

	// 跳过关卡分数
	tagLevelInfo.iJumpCoin  = doc["jumpCoin"].GetInt();

	// 通过关卡给予经验
	tagLevelInfo.iGiveExp   = doc["giveExp"].GetInt();

	// 通过关卡给予金币
	tagLevelInfo.iGiveCoin  = doc["giveCoin"].GetInt();

	// 类型概率
	rapidjson::Value& valueTP = doc["typeProbability"];

	for (int i = 0; i < valueTP.Size(); i++)
	{
		rapidjson::Value& valueBuf = valueTP[i];
		
		TypeProbability   tagTB;
		tagTB.iType			= valueBuf["type"].GetInt();
		tagTB.iProbability  = valueBuf["probability"].GetInt();

		tagLevelInfo.tagTypeProbabilitys.push_back(tagTB);
	}

	// 对白
	rapidjson::Value& valuePI = doc["prologueInfo"];

	for (int i = 0; i < valuePI.Size(); i++)
	{
		rapidjson::Value& valueBuf = valuePI[i];

		PrologueInfo tagPI;
		tagPI.bHeadPlace  = valueBuf["headPlace"].GetBool();
		tagPI.strHeadName = valueBuf["headName"].GetString();
		tagPI.strHeadFile = valueBuf["headFile"].GetString();

		rapidjson::Value& valueWords = valueBuf["words"];
		for (int i = 0; i < valueWords.Size(); i++)
		{
			tagPI.strWords.push_back(valueWords[i].GetString());
		}

		tagLevelInfo.tagPrologueInfos.push_back(tagPI);
	}

	return tagLevelInfo;
}
//--------------------------------------------------------
BaseLevelInfo LevelManager::getBaseLevelInfo(std::string strFilePath)
{
	BaseLevelInfo tagBaseLevelInfo;

	// 获取真实路径
	strFilePath = FileUtils::getInstance()->fullPathForFilename(strFilePath);

	// 获取JSON字符串
	std::string strJson = FileUtils::getInstance()->getStringFromFile(strFilePath);

	rapidjson::Document doc;
	doc.Parse<0>(strJson.c_str());	// 解析JSON字符串
	bool isNull = doc.IsNull();

	// 关卡类型
	tagBaseLevelInfo.strType = doc["type"].GetString(); 

	// 关卡ID
	tagBaseLevelInfo.strLevelId = doc["levelId"].GetString();

	// 描述
	tagBaseLevelInfo.strDepict = doc["depict"].GetString();

	// 跳过关卡分数
	tagBaseLevelInfo.iJumpCoin = doc["jumpCoin"].GetInt();

	// 通过关卡给予经验
	tagBaseLevelInfo.iGiveExp = doc["giveExp"].GetInt();

	// 通过关卡给予金币
	tagBaseLevelInfo.iGiveCoin = doc["giveCoin"].GetInt();

	// 类型概率
	rapidjson::Value& valueTP = doc["typeProbability"];

	for (int i = 0; i < valueTP.Size(); i++)
	{
		rapidjson::Value& valueBuf = valueTP[i];

		TypeProbability   tagTB;
		tagTB.iType = valueBuf["type"].GetInt();
		tagTB.iProbability = valueBuf["probability"].GetInt();

		tagBaseLevelInfo.tagTypeProbabilitys.push_back(tagTB);
	}

	// 对白
	rapidjson::Value& valuePI = doc["prologueInfo"];
	
	for (int i = 0; i < valuePI.Size(); i++)
	{
		rapidjson::Value& valueBuf = valuePI[i];

		PrologueInfo tagPI;
		tagPI.bHeadPlace = valueBuf["headPlace"].GetBool();
		tagPI.strHeadName = valueBuf["headName"].GetString();
		tagPI.strHeadFile = valueBuf["headFile"].GetString();

		rapidjson::Value& valueWords = valueBuf["words"];
		for (int i = 0; i < valueWords.Size(); i++)
		{
			tagPI.strWords.push_back(valueWords[i].GetString());
		}

		tagBaseLevelInfo.tagPrologueInfos.push_back(tagPI);
	}

	return tagBaseLevelInfo;
}
//--------------------------------------------------------
LevelInfo_1001 LevelManager::getLevelInfoForType1001(std::string strFileFile)
{
	LevelInfo_1001 tagLevelInfo;

	BaseLevelInfo tagBaseLevelInfo	 = getBaseLevelInfo(strFileFile);
	tagLevelInfo.iGiveCoin			 = tagBaseLevelInfo.iGiveCoin;
	tagLevelInfo.iGiveExp			 = tagBaseLevelInfo.iGiveExp;
	tagLevelInfo.iJumpCoin			 = tagBaseLevelInfo.iJumpCoin;
	tagLevelInfo.strDepict			 = tagBaseLevelInfo.strDepict;
	tagLevelInfo.strLevelId			 = tagBaseLevelInfo.strLevelId;
	tagLevelInfo.strType			 = tagBaseLevelInfo.strType;
	tagLevelInfo.tagPrologueInfos	 = tagBaseLevelInfo.tagPrologueInfos;
	tagLevelInfo.tagTypeProbabilitys = tagBaseLevelInfo.tagTypeProbabilitys;

	// 获取真实路径
	std::string strFullPath = FileUtils::getInstance()->fullPathForFilename(strFileFile);
	std::string strJson = FileUtils::getInstance()->getStringFromFile(strFullPath);

	rapidjson::Document doc;
	doc.Parse<0>(strJson.c_str());	// 解析JSON字符串

	// 关卡类型
	tagLevelInfo.iPassScore = doc["passScore"].GetInt();

	return tagLevelInfo;
}
//--------------------------------------------------------
LevelInfo_1002 LevelManager::getLevelInfoForType1002(const std::string& strFilePath)
{
	LevelInfo_1002 tagLevelInfo;

	BaseLevelInfo tagBaseLevelInfo = getBaseLevelInfo(strFilePath);
	tagLevelInfo.iGiveCoin = tagBaseLevelInfo.iGiveCoin;
	tagLevelInfo.iGiveExp = tagBaseLevelInfo.iGiveExp;
	tagLevelInfo.iJumpCoin = tagBaseLevelInfo.iJumpCoin;
	tagLevelInfo.strDepict = tagBaseLevelInfo.strDepict;
	tagLevelInfo.strLevelId = tagBaseLevelInfo.strLevelId;
	tagLevelInfo.strType = tagBaseLevelInfo.strType;
	tagLevelInfo.tagPrologueInfos = tagBaseLevelInfo.tagPrologueInfos;
	tagLevelInfo.tagTypeProbabilitys = tagBaseLevelInfo.tagTypeProbabilitys;

	// 获取真实路径
	std::string strFullPath = FileUtils::getInstance()->fullPathForFilename(strFilePath);
	std::string strJson = FileUtils::getInstance()->getStringFromFile(strFullPath);

	rapidjson::Document doc;
	doc.Parse<0>(strJson.c_str());	// 解析JSON字符串

	// 关卡类型
	tagLevelInfo.iPassScore = doc["passScore"].GetInt();
	tagLevelInfo.iNegativeType = doc["negativeType"].GetInt();

	return tagLevelInfo;
}
//--------------------------------------------------------
LevelInfo_2001 LevelManager::getLevelInfoForType2001(const std::string& strFilePath)
{
	LevelInfo_2001 tagLevelInfo;

	BaseLevelInfo tagBaseLevelInfo = getBaseLevelInfo(strFilePath);
	tagLevelInfo.iGiveCoin = tagBaseLevelInfo.iGiveCoin;
	tagLevelInfo.iGiveExp = tagBaseLevelInfo.iGiveExp;
	tagLevelInfo.iJumpCoin = tagBaseLevelInfo.iJumpCoin;
	tagLevelInfo.strDepict = tagBaseLevelInfo.strDepict;
	tagLevelInfo.strLevelId = tagBaseLevelInfo.strLevelId;
	tagLevelInfo.strType = tagBaseLevelInfo.strType;
	tagLevelInfo.tagPrologueInfos = tagBaseLevelInfo.tagPrologueInfos;
	tagLevelInfo.tagTypeProbabilitys = tagBaseLevelInfo.tagTypeProbabilitys;

	// 获取真实路径
	std::string strFullPath = FileUtils::getInstance()->fullPathForFilename(strFilePath);
	std::string strJson = FileUtils::getInstance()->getStringFromFile(strFullPath);

	rapidjson::Document doc;
	doc.Parse<0>(strJson.c_str());	// 解析JSON字符串

	// 关卡类型
	tagLevelInfo.iPassScore = doc["passScore"].GetInt();
	tagLevelInfo.iStep = doc["step"].GetInt();

	return tagLevelInfo;
}
//--------------------------------------------------------
LevelInfo_2002 LevelManager::getLevelInfoForType2002(const std::string& strFilePath)
{
	LevelInfo_2002 tagLevelInfo;

	BaseLevelInfo tagBaseLevelInfo = getBaseLevelInfo(strFilePath);
	tagLevelInfo.iGiveCoin = tagBaseLevelInfo.iGiveCoin;
	tagLevelInfo.iGiveExp = tagBaseLevelInfo.iGiveExp;
	tagLevelInfo.iJumpCoin = tagBaseLevelInfo.iJumpCoin;
	tagLevelInfo.strDepict = tagBaseLevelInfo.strDepict;
	tagLevelInfo.strLevelId = tagBaseLevelInfo.strLevelId;
	tagLevelInfo.strType = tagBaseLevelInfo.strType;
	tagLevelInfo.tagPrologueInfos = tagBaseLevelInfo.tagPrologueInfos;
	tagLevelInfo.tagTypeProbabilitys = tagBaseLevelInfo.tagTypeProbabilitys;

	// 获取真实路径
	std::string strFullPath = FileUtils::getInstance()->fullPathForFilename(strFilePath);
	std::string strJson = FileUtils::getInstance()->getStringFromFile(strFullPath);

	rapidjson::Document doc;
	doc.Parse<0>(strJson.c_str());	// 解析JSON字符串

	// 关卡类型
	tagLevelInfo.iStep = doc["step"].GetInt();

	// 任务
	rapidjson::Value& valueTK = doc["task"];

	for (int i = 0; i < valueTK.Size(); i++)
	{
		rapidjson::Value& task = valueTK[i];

		TaskInfo ti;
		ti.iCount = task["count"].GetInt();
		ti.iType = task["type"].GetInt();

		tagLevelInfo.tagTask.push_back(ti);
	}

	return tagLevelInfo;
}
//--------------------------------------------------------
LevelInfo_2003 LevelManager::getLevelInfoForType2003(const std::string& strFilePath)
{
	LevelInfo_2003 tagLevelInfo;

	BaseLevelInfo tagBaseLevelInfo = getBaseLevelInfo(strFilePath);
	tagLevelInfo.iGiveCoin = tagBaseLevelInfo.iGiveCoin;
	tagLevelInfo.iGiveExp = tagBaseLevelInfo.iGiveExp;
	tagLevelInfo.iJumpCoin = tagBaseLevelInfo.iJumpCoin;
	tagLevelInfo.strDepict = tagBaseLevelInfo.strDepict;
	tagLevelInfo.strLevelId = tagBaseLevelInfo.strLevelId;
	tagLevelInfo.strType = tagBaseLevelInfo.strType;
	tagLevelInfo.tagPrologueInfos = tagBaseLevelInfo.tagPrologueInfos;
	tagLevelInfo.tagTypeProbabilitys = tagBaseLevelInfo.tagTypeProbabilitys;

	// 获取真实路径
	std::string strFullPath = FileUtils::getInstance()->fullPathForFilename(strFilePath);
	std::string strJson = FileUtils::getInstance()->getStringFromFile(strFullPath);

	rapidjson::Document doc;
	doc.Parse<0>(strJson.c_str());	// 解析JSON字符串

	// 关卡类型
	tagLevelInfo.iStep = doc["step"].GetInt();

	// 通过分数
	tagLevelInfo.iPassScore = doc["passScore"].GetInt();

	// 任务
	rapidjson::Value& valueTK = doc["task"];

	for (int i = 0; i < valueTK.Size(); i++)
	{
		rapidjson::Value& task = valueTK[i];

		TaskInfo ti;
		ti.iCount = task["count"].GetInt();
		ti.iType = task["type"].GetInt();

		tagLevelInfo.tagTask.push_back(ti);
	}

	return tagLevelInfo;
}
//--------------------------------------------------------
LevelInfo_3001 LevelManager::getLevelInfoForType3001(const std::string& strFilePath)
{
	LevelInfo_3001 tagLevelInfo;

	BaseLevelInfo tagBaseLevelInfo = getBaseLevelInfo(strFilePath);
	tagLevelInfo.iGiveCoin = tagBaseLevelInfo.iGiveCoin;
	tagLevelInfo.iGiveExp = tagBaseLevelInfo.iGiveExp;
	tagLevelInfo.iJumpCoin = tagBaseLevelInfo.iJumpCoin;
	tagLevelInfo.strDepict = tagBaseLevelInfo.strDepict;
	tagLevelInfo.strLevelId = tagBaseLevelInfo.strLevelId;
	tagLevelInfo.strType = tagBaseLevelInfo.strType;
	tagLevelInfo.tagPrologueInfos = tagBaseLevelInfo.tagPrologueInfos;
	tagLevelInfo.tagTypeProbabilitys = tagBaseLevelInfo.tagTypeProbabilitys;

	// 获取真实路径
	std::string strFullPath = FileUtils::getInstance()->fullPathForFilename(strFilePath);
	std::string strJson = FileUtils::getInstance()->getStringFromFile(strFullPath);

	rapidjson::Document doc;
	doc.Parse<0>(strJson.c_str());	// 解析JSON字符串

	// 通过分数
	tagLevelInfo.iPassScore = doc["passScore"].GetInt();
	tagLevelInfo.iTime = doc["time"].GetInt();

	return tagLevelInfo;
}
//--------------------------------------------------------
LevelInfo_3002 LevelManager::getLevelInfoForType3002(const std::string& strFilePath)
{
	LevelInfo_3002 tagLevelInfo;

	BaseLevelInfo tagBaseLevelInfo = getBaseLevelInfo(strFilePath);
	tagLevelInfo.iGiveCoin = tagBaseLevelInfo.iGiveCoin;
	tagLevelInfo.iGiveExp = tagBaseLevelInfo.iGiveExp;
	tagLevelInfo.iJumpCoin = tagBaseLevelInfo.iJumpCoin;
	tagLevelInfo.strDepict = tagBaseLevelInfo.strDepict;
	tagLevelInfo.strLevelId = tagBaseLevelInfo.strLevelId;
	tagLevelInfo.strType = tagBaseLevelInfo.strType;
	tagLevelInfo.tagPrologueInfos = tagBaseLevelInfo.tagPrologueInfos;
	tagLevelInfo.tagTypeProbabilitys = tagBaseLevelInfo.tagTypeProbabilitys;

	// 获取真实路径
	std::string strFullPath = FileUtils::getInstance()->fullPathForFilename(strFilePath);
	std::string strJson = FileUtils::getInstance()->getStringFromFile(strFullPath);

	rapidjson::Document doc;
	doc.Parse<0>(strJson.c_str());	// 解析JSON字符串

	tagLevelInfo.iTime = doc["time"].GetInt();

	// 任务
	rapidjson::Value& valueTK = doc["task"];

	for (int i = 0; i < valueTK.Size(); i++)
	{
		rapidjson::Value& task = valueTK[i];

		TaskInfo ti;
		ti.iCount = task["count"].GetInt();
		ti.iType = task["type"].GetInt();

		tagLevelInfo.tagTask.push_back(ti);
	}

	return tagLevelInfo;
}
//--------------------------------------------------------
LevelInfo_3003 LevelManager::getLevelInfoForType3003(const std::string& strFilePath)
{
	LevelInfo_3003 tagLevelInfo;

	BaseLevelInfo tagBaseLevelInfo = getBaseLevelInfo(strFilePath);
	tagLevelInfo.iGiveCoin = tagBaseLevelInfo.iGiveCoin;
	tagLevelInfo.iGiveExp = tagBaseLevelInfo.iGiveExp;
	tagLevelInfo.iJumpCoin = tagBaseLevelInfo.iJumpCoin;
	tagLevelInfo.strDepict = tagBaseLevelInfo.strDepict;
	tagLevelInfo.strLevelId = tagBaseLevelInfo.strLevelId;
	tagLevelInfo.strType = tagBaseLevelInfo.strType;
	tagLevelInfo.tagPrologueInfos = tagBaseLevelInfo.tagPrologueInfos;
	tagLevelInfo.tagTypeProbabilitys = tagBaseLevelInfo.tagTypeProbabilitys;

	// 获取真实路径
	std::string strFullPath = FileUtils::getInstance()->fullPathForFilename(strFilePath);
	std::string strJson = FileUtils::getInstance()->getStringFromFile(strFullPath);

	rapidjson::Document doc;
	doc.Parse<0>(strJson.c_str());	// 解析JSON字符串

	tagLevelInfo.iTime = doc["time"].GetInt();
	tagLevelInfo.iPassScore = doc["passScore"].GetInt();

	// 任务
	rapidjson::Value& valueTK = doc["task"];

	for (int i = 0; i < valueTK.Size(); i++)
	{
		rapidjson::Value& task = valueTK[i];

		TaskInfo ti;
		ti.iCount = task["count"].GetInt();
		ti.iType = task["type"].GetInt();

		tagLevelInfo.tagTask.push_back(ti);
	}

	return tagLevelInfo;
}
//--------------------------------------------------------