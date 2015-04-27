#include "Bullet.h"

Bullet *Bullet::createWithBulletType(int bulletType, GameLayer *gameLayer, SpriteBatchNode *pBatchNodeBullet, SpriteBatchNode *pBatchNodeNet)
{
	Bullet *pBullet = new Bullet();
	if (pBullet && pBullet->initWithBulletType(bulletType, gameLayer, pBatchNodeBullet, pBatchNodeNet))
	{
		pBullet->autorelease();
		return pBullet;
	}
	else
	{
		CC_SAFE_DELETE(pBullet);
		return NULL;
	}
}

bool Bullet::initWithBulletType(int bulletType, GameLayer *gameLayer, SpriteBatchNode *pBatchNodeBullet, SpriteBatchNode *pBatchNodeNet){
	//设置初始化参数
	m_pCaught = false;
	this->setBulletType(bulletType);
	this->setGameLayer(gameLayer);

	//设置子弹精灵
	String *bulletName = String::createWithFormat("bullet0%d.png", m_pBulletType);
	this->setSpriteBullet(Sprite::createWithSpriteFrameName(bulletName->getCString()));
	m_pSpriteBullet->setPosition(Vec2(520, 50));
	pBatchNodeBullet->addChild(m_pSpriteBullet);

	//创建预备撒网动画
	String *nodeNetName = String::createWithFormat("net0%d.png", m_pBulletType);
	this->setSpriteNet(Sprite::createWithSpriteFrameName(nodeNetName->getCString()));
	this->m_pSpriteNet->setVisible(false);
	pBatchNodeNet->addChild(m_pSpriteNet);

	//让游戏主界面 持有子弹对象的指针
	m_pGameLayer->getBullets()->addObject(this);
	return true;
}

void Bullet::showTo(Vec2 targetDirection)
{
	Vec2 ptFrom = m_pSpriteBullet->getPosition();
	Vec2 pt = targetDirection;
	float angle = atan2f(pt.y - ptFrom.y, pt.x - ptFrom.x);
	float rotation = angle / M_PI * 180.0f;
	m_pSpriteBullet->setRotation(90.0f - rotation);

	Size size = Director::getInstance()->getWinSize();
	
	float distance = MAX(size.width, size.height);
	//计算子弹的目的地
	Vec2 targetPt = Vec2(ptFrom.x + distance * cosf(angle), ptFrom.y + distance * sinf(angle));
	
	//通过动作 实现子弹发射
	MoveTo *moveTo = MoveTo::create(1.0f, targetPt);
	//定义动作的回调函数
	CallFunc *callFunc = CallFunc::create(this, callfunc_selector(Bullet::removeSelf));
	Sequence *sequence = Sequence::create(moveTo, callFunc, NULL);

	m_pSpriteBullet->runAction(sequence);
}

//子弹击中鱼的时候 播放撒网动画
void Bullet::showNet()
{
	//标记子弹击中的鱼
	m_pCaught = true;
	//停止子弹的效果
	m_pSpriteBullet->stopAllActions();
	//击中鱼的子弹不可见
	m_pSpriteBullet->setVisible(false);
	m_pSpriteNet->setVisible(true);

	//使用缩放动画 实现撒网捕鱼
	ScaleTo *scale = ScaleTo::create(0.3f, 1.25f);
	CallFunc *callFuc = CallFunc::create(this, callfunc_selector(Bullet::removeSelf));
	Sequence *sequence = Sequence::create(scale, callFuc, NULL);
	m_pSpriteNet->runAction(sequence);
	m_pSpriteNet->setPosition(m_pSpriteBullet->getPosition());

	//在播放撒网的时候 播放粒子效果 表示被击中
	ParticleSystem *particle = ParticleSystemQuad::create("netparticle.plist");
	particle->setPosition(m_pSpriteNet->getPosition());
	particle->setPositionType(ParticleSystem::PositionType::GROUPED);
	particle->setAutoRemoveOnFinish(true);
	m_pGameLayer->addChild(particle, 100);
}

void Bullet::removeSelf()
{
	this->getGameLayer()->getBullets()->removeObject(this);
	m_pSpriteBullet->removeFromParentAndCleanup(true);
	m_pSpriteNet->removeFromParentAndCleanup(true);
	log("removeSelf");
}