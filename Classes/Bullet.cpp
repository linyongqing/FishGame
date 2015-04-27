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
	//���ó�ʼ������
	m_pCaught = false;
	this->setBulletType(bulletType);
	this->setGameLayer(gameLayer);

	//�����ӵ�����
	String *bulletName = String::createWithFormat("bullet0%d.png", m_pBulletType);
	this->setSpriteBullet(Sprite::createWithSpriteFrameName(bulletName->getCString()));
	m_pSpriteBullet->setPosition(Vec2(520, 50));
	pBatchNodeBullet->addChild(m_pSpriteBullet);

	//����Ԥ����������
	String *nodeNetName = String::createWithFormat("net0%d.png", m_pBulletType);
	this->setSpriteNet(Sprite::createWithSpriteFrameName(nodeNetName->getCString()));
	this->m_pSpriteNet->setVisible(false);
	pBatchNodeNet->addChild(m_pSpriteNet);

	//����Ϸ������ �����ӵ������ָ��
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
	//�����ӵ���Ŀ�ĵ�
	Vec2 targetPt = Vec2(ptFrom.x + distance * cosf(angle), ptFrom.y + distance * sinf(angle));
	
	//ͨ������ ʵ���ӵ�����
	MoveTo *moveTo = MoveTo::create(1.0f, targetPt);
	//���嶯���Ļص�����
	CallFunc *callFunc = CallFunc::create(this, callfunc_selector(Bullet::removeSelf));
	Sequence *sequence = Sequence::create(moveTo, callFunc, NULL);

	m_pSpriteBullet->runAction(sequence);
}

//�ӵ��������ʱ�� ������������
void Bullet::showNet()
{
	//����ӵ����е���
	m_pCaught = true;
	//ֹͣ�ӵ���Ч��
	m_pSpriteBullet->stopAllActions();
	//��������ӵ����ɼ�
	m_pSpriteBullet->setVisible(false);
	m_pSpriteNet->setVisible(true);

	//ʹ�����Ŷ��� ʵ����������
	ScaleTo *scale = ScaleTo::create(0.3f, 1.25f);
	CallFunc *callFuc = CallFunc::create(this, callfunc_selector(Bullet::removeSelf));
	Sequence *sequence = Sequence::create(scale, callFuc, NULL);
	m_pSpriteNet->runAction(sequence);
	m_pSpriteNet->setPosition(m_pSpriteBullet->getPosition());

	//�ڲ���������ʱ�� ��������Ч�� ��ʾ������
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