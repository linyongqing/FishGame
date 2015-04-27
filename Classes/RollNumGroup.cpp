#include "RollNum.h"
#include "cocos2d.h"
#include "GameLayer.h"

using namespace cocos2d;

RollNumGroup *RollNumGroup::createWithGameLayer(GameLayer *pGameLayer, int nDigit)
{
	RollNumGroup *pRollNumGroup = new RollNumGroup();
	if (pRollNumGroup && pRollNumGroup->intiWithGaneLayer(pGameLayer, nDigit))
	{
		pRollNumGroup->retain();
		return pRollNumGroup;
	}
	else
	{
		CC_SAFE_DELETE(pRollNumGroup);
		return NULL;
	}
}

RollNumGroup::RollNumGroup() :m_pRollNumArray(NULL), m_nValue(0){}

RollNumGroup::~RollNumGroup()
{
	CC_SAFE_RELEASE(m_pRollNumArray);
}

bool RollNumGroup::intiWithGaneLayer(GameLayer *pGameLayer, int nDigit)
{
	m_pGameLayer = pGameLayer;
	Texture2D *pTexture = Director::getInstance()->getTextureCache()->addImage("number.png");
	m_pBatchNode = SpriteBatchNode::createWithTexture(pTexture);
	m_pGameLayer->addChild(m_pBatchNode, 100);

	this->setRollNumArray(Array::createWithCapacity(nDigit));

	for (int i = 0; i < nDigit; i++)
	{
		RollNum *pRollNum = RollNum::create();
		m_pRollNumArray->addObject(pRollNum);
		m_pBatchNode->addChild(pRollNum);
	}
	return true;
}

void RollNumGroup::setPosition(cocos2d::Vec2 pt)
{
	m_ptPosition = pt;
	for (int i = 0; i < m_pRollNumArray->count(); ++i)
	{
		RollNum *pRollNum = (RollNum*)m_pRollNumArray->getObjectAtIndex(i);
		pRollNum->setPosition(pt);
		pt.x -= 20.7f;
	}
}

void RollNumGroup::setValue(int value)
{
	if (m_nValue == value)
		return;
	bool bUp = m_nValue < value;
	m_nValue = value;

	for (int i = 0; i < m_pRollNumArray->count(); ++i)
	{
		RollNum *pRollNum = (RollNum*)m_pRollNumArray->getObjectAtIndex(i);

		int num = value % 10;

		if (pRollNum->getNumber() != num)
			pRollNum->setNumber(num, bUp);
		value = value / 10;
	}
}