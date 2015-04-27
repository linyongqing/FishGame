#include "Fish.h"
#include "GameLayer.h"

USING_NS_CC;

Fish::~Fish()
{
	//CCLog("destuct fish %d", m_nFishType);
}

Fish *Fish::createWithFishType(int fishType, GameLayer* gameLayer, SpriteBatchNode *pBatchNodeFish)
{
	Fish *fish = new Fish();
	if (fish && fish->initWithFishType(fishType, gameLayer, pBatchNodeFish))
	{
		fish->autorelease();
		return fish;
	}else{
		CC_SAFE_DELETE(fish);
		return NULL;
	}
}

bool Fish::initWithFishType(int fishType, GameLayer *gameLayer, SpriteBatchNode *pBatchNodeFish)
{
	m_bCaught = false;
	this->setFishType(fishType);
	this->setGameLayer(gameLayer);
	this->setBatchNodeFish(pBatchNodeFish);
	m_pParticleBubble = false;

	if (m_nFishType == 11 || m_nFishType == 12)
	{
		m_bParticleBulle = true;
	}
	Vector<SpriteFrame*> frames;
	for (int i = 0; i <= 16; i++)
	{
		String *frametName = String::createWithFormat("Fish%02d_%02d.png", m_nFishType, i);
		SpriteFrame *pFrame = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(frametName->getCString());
		if (pFrame)
		{
			frames.pushBack(pFrame);
		}
	}
	Animation *animation = Animation::createWithSpriteFrames(frames, 0.2f);
	animation->setRestoreOriginalFrame(false);
	Animate *animate = Animate::create(animation);
	Action *swing = RepeatForever::create(animate);

	String *originalFrameName = __String::createWithFormat("fish%02d_01.png", fishType);
	m_pSpriteFish = Sprite::createWithSpriteFrameName(originalFrameName->getCString());
	m_pSpriteFish->runAction(swing);

	m_pSpriteFish->setAnchorPoint(Vec2(0.5f, 0.5f));

	MoveTo *moveTo = NULL;

	//随机构建鱼的运动路线
	this->getPath(moveTo);
	CallFunc *releaseFunc = CallFunc::create(this, callfunc_selector(Fish::removeSelf));
	Sequence *sequence = Sequence::create(moveTo, releaseFunc, NULL);
	m_pSpriteFish->runAction(sequence);

	//让游戏主场景拿到鱼的指针，方便做碰撞检测
	this->m_pGameLayer->getFishes()->addObject(this);
	this->getBatchNodeFish()->addChild(m_pSpriteFish);
	return true;
}

void Fish::showCaught()
{
	m_bCaught = true; //标记鱼被捕获了
	//停止所有动作
	m_pSpriteFish->stopAllActions();
	if (m_bParticleBulle && m_pParticleBubble)
	{
		m_pParticleBubble->stopAllActions();
		m_pParticleBubble->setVisible(true);

		Vector<SpriteFrame*> frames;
		for (int i = 1; i <= 4; i++)
		{
			__String *frameName = __String::createWithFormat("fish%02d_catch_%02d.png", m_nFishType, i);
			SpriteFrame *pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
			if (pFrame)
			{
				frames.pushBack(pFrame);
			}
		}
		//构建帧动画
		Animation *animation = Animation::createWithSpriteFrames(frames, 0.3f);
		Animate *animate = Animate::create(animation);
		CallFunc *callFunc = CallFunc::create(this, callfunc_selector(Fish::removeSelf));
		Sequence *sequence = Sequence::create(animate, callFunc, NULL);
		m_pSpriteFish->runAction(sequence);
	}
}

void Fish::offsetPoit(Vec2 &pt, float offsetX, float offsetY){
	pt.x = offsetX;
	pt.y = offsetY;
}

void Fish::getPath(MoveTo *&moveTo)
{
	Size fishSize = m_pSpriteFish->getContentSize();
	Size size = Director::getInstance()->getWinSize();
	Vec2 ptStart, ptEnd; //开始点，结束点
	float radius = MAX(fishSize.width, fishSize.height);

	switch (rand() % 4)
	{
	case 0: //从左开始
		ptStart.x = radius;
		ptStart.y = rand() % (int)size.height;

		//从右结束
		ptEnd.x = size.width + radius;
		ptEnd.y = rand() % (int)size.height;
		break;

	case 1: //从右开始
		ptStart.x = size.width + radius;
		ptStart.y = rand() % (int)size.height;

		//从左结束
		ptEnd.x = -radius;
		ptEnd.y = rand() % (int)size.height;
		break;
	case 2:
		//从底开始
		ptStart.x = rand() % (int)size.width;
		ptStart.y = -radius;

		//从上结束
		ptEnd.x = rand() % (int)size.width;
		ptEnd.y = size.height + radius;
		break;

	case 3: //从上开始
		ptStart.x = rand() % (int)size.width;
		ptStart.y = size.height + radius;

		//从底结束
		ptEnd.x = rand() % (int)size.width;
		ptEnd.y = -radius;
		break;
	default:
		break;
	}

	float angle = atan2f(ptEnd.y - ptStart.y, ptEnd.x - ptStart.y);
	float rotation = 180.0f - angle * 180.0f / M_PI;
	float duration = rand() % 10 + 4.0f;
	
	m_pSpriteFish->setPosition(ptStart);
	m_pSpriteFish->setRotation(rotation);
	moveTo = MoveTo::create(duration, ptEnd);

	if (m_bParticleBulle)
	{
		this->setParticleBubble(ParticleSystemQuad::create("bubble.plist"));
		m_pGameLayer->addChild(this->m_pParticleBubble);
		float w = m_pSpriteFish->getContentSize().width;

		offsetPoit(ptStart, cosf(angle)*w, sinf(angle)*w);
		m_pParticleBubble->setPosition(ptStart);

		offsetPoit(ptEnd, cosf(angle) * w, sinf(angle) * w);
		Action *act = MoveTo::create(moveTo->getDuration(), ptEnd);
		m_pParticleBubble->setAutoRemoveOnFinish(false);
		m_pParticleBubble->setPositionType(ParticleSystem::PositionType::FREE);
		m_pParticleBubble->runAction(act);
	}
}

void Fish::removeSelf()
{
	this->getGameLayer()->getFishes()->removeObject(this);
	m_pSpriteFish->removeFromParentAndCleanup(true);

	if (m_bParticleBulle && m_pParticleBubble)
	{
		m_pParticleBubble->removeFromParentAndCleanup(true);
	}
}