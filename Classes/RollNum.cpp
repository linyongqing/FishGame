#include "cocos2d.h"
#include "RollNum.h"
#include "GameLayer.h"

USING_NS_CC;

#define NUMBERHIGHT 16
#define NUMBERWIDTH 12
#define TEXTUREHIGHT 196

RollNum::RollNum() :m_nNumber(0), m_bUp(true), m_nCurTexH(0), m_nEndTexH(0), m_bRolling(false), m_pTexture(NULL){

}

RollNum::~RollNum()
{
	this->unscheduleAllSelectors();
}

bool RollNum::init()
{
	std::string fullPath = FileUtils::getInstance()->fullPathForFilename("number.png");
	m_pTexture = Director::getInstance()->getTextureCache()->getTextureForKey(fullPath);
	SpriteFrame *pFrame = SpriteFrame::createWithTexture(m_pTexture, Rect(0, 0, NUMBERWIDTH, NUMBERHIGHT));
	this->initWithSpriteFrame(pFrame);
	this->setScale(1.0f);
	return true;
}

void RollNum::updateNumber(float dt)
{
	if (m_bRolling && m_nCurTexH == m_nEndTexH)
	{
		this->unschedule(schedule_selector(RollNum::updateNumber));
		m_bRolling = false;
		return;
	}
	if (m_bUp)
	{
		m_nCurTexH += 4;
		if (m_nCurTexH >= TEXTUREHIGHT)
			m_nCurTexH = 0;
	}
	else
	{
		m_nCurTexH -= 4;
		if (m_nCurTexH < 0)
			m_nCurTexH = TEXTUREHIGHT;
	}
	int h = m_nCurTexH;
	if (m_nCurTexH >= 180)
		h = 180;
	SpriteFrame *pFrame = SpriteFrame::createWithTexture(m_pTexture, Rect(0, h, NUMBERHIGHT, NUMBERWIDTH));
	this->setDisplayFrame(pFrame);
	m_bRolling = true;
}

void RollNum::setNumber(int var, bool bUp)
{
	m_nNumber = var;
	m_bUp = bUp;
	m_nEndTexH = m_nNumber * (NUMBERHIGHT + 4);
	this->schedule(schedule_selector(RollNum::updateNumber), 0.01f);
}

int RollNum::getNumber()
{
	return m_nNumber;
}