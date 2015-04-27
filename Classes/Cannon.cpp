#include "Cannon.h"
#include "GameLayer.h"
#include "Bullet.h"

USING_NS_CC;

Cannon *Cannon::createWithCannonType(int cannonType, GameLayer* pGameLayer, cocos2d::SpriteBatchNode *pBatchNode){
	Cannon *pCannon = new Cannon(cannonType, pGameLayer);
	if (pCannon && pCannon->initWithCannonType(pBatchNode))
	{
		pCannon->autorelease(); //调用方需要使用retain操作，才能避免被释放掉
		return pCannon;
	}
	else
	{
		CC_SAFE_DELETE(pCannon);
		return NULL;
	}
}

Cannon::Cannon(int cannonType, GameLayer *gameLayer) :m_nCannonType(cannonType), m_pGameLayer(gameLayer){
	//初始化列表
}

Cannon::~Cannon(){
	this->m_pSprite->removeFromParentAndCleanup(true);
}

int Cannon::getCannnType(){
	return this->m_nCannonType;
}

bool Cannon::initWithCannonType(cocos2d::SpriteBatchNode *pBatchNode){
	String *cannonName = String::createWithFormat("actor_cannon1_%d1.png", m_nCannonType);
	this->m_pSprite = Sprite::createWithSpriteFrameName(cannonName->getCString());
	this->m_pSprite->setPosition(Vec2(520, 50));
	pBatchNode->addChild(this->m_pSprite);
	return true;
}

void Cannon::rotateToPoint(cocos2d::Vec2 pt){
	Vec2 ptFrom = m_pSprite->getPosition();
	float angle = atan2f(pt.y - ptFrom.y, pt.x - ptFrom.x) / M_PI * 180.0f;
	this->setRotation(90.f - angle);
	this->m_pDirection = pt;
}

void Cannon::setRotation(float rotation){
	m_fRotation = rotation;
	float absf_Rotation = fabsf(m_fRotation - this->m_pSprite->getRotation());
	float duration = absf_Rotation / 180.0f * 0.2f;
	FiniteTimeAction *pAction = RotateTo::create(duration, m_fRotation);
	this->m_pSprite->runAction(pAction);
}

void Cannon::fire(){
	String *pFireStartFrameName = String::createWithFormat("actor_cannon1_%d1.png", this->m_nCannonType);
	String *pFireEndFrameName = String::createWithFormat("actor_cannon1_%d2.png", this->m_nCannonType);

	//创建发射子弹的大炮动画帧
	SpriteFrame *pFireStartFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(pFireStartFrameName->getCString());
	SpriteFrame *pFireEndFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(pFireEndFrameName->getCString());
	Vector<SpriteFrame*> frame;
	frame.pushBack(pFireStartFrame);
	frame.pushBack(pFireEndFrame);

	Animation *pAnimationFire = Animation::createWithSpriteFrames(frame, 0.1f);
	pAnimationFire->setRestoreOriginalFrame(true);
	Animate *pAction = Animate::create(pAnimationFire);
	this->m_pSprite->runAction(pAction);

	Bullet *pBullet = Bullet::createWithBulletType(m_nCannonType, this->m_pGameLayer, this->m_pGameLayer->getBatchNodeFishes2AndBullets(), this->m_pGameLayer->getBatchNodeFishes3AndNets());
	pBullet->showTo(this->m_pDirection);

}