#include "RES.h"

USING_NS_CC;

std::string RES::Text::getText(std::string key)
{ 
	rapidjson::Value& value = _doc[key.c_str()];
	if (value.IsNull() || !value.IsString())
	{
		return "";
	}
	else
	{
		return value.GetString();
	}
}

bool RES::Text::initText()
{
	_doc.Parse<0>(String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename("String/zh.json"))->getCString());
	return true;
}

RES::Text* RES::Text::getInstance()
{
	if (m_text == NULL)
	{
		m_text = new Text();
		m_text->initText();
	}

	return m_text;
}

void RES::Text::destoryInstance()
{
	CC_SAFE_DELETE(m_text);
}

RES::Text* RES::Text::m_text = NULL;