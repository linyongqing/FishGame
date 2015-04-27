#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"
#include "GameLayer.h"

USING_NS_CC;

class GameLayer;

class Bullet : public Ref
{
public:
	static Bullet *createWithBulletType(int bulletType, GameLayer *gameLayer, SpriteBatchNode *pBatchNodeBullet, SpriteBatchNode *pBatchNodeNet);

	CC_SYNTHESIZE_READONLY(bool, m_pCaught, Caught);
	
	//ָ�������ӵ��ķ���
	void showTo(Vec2 targetDirection);
	//ָ���������ʱ�򣬲�����������
	void showNet();
private:
	CC_SYNTHESIZE(GameLayer*, m_pGameLayer, GameLayer);
	CC_SYNTHESIZE(int, m_pBulletType, BulletType);
	CC_SYNTHESIZE(Sprite*, m_pSpriteBullet, SpriteBullet);
	CC_SYNTHESIZE(Sprite*, m_pSpriteNet, SpriteNet);

	//�����ӵ���ʵ��
	bool initWithBulletType(int bulletType, GameLayer *gameLayer, SpriteBatchNode *pBatchNodeBullet, SpriteBatchNode *pBatchNodeNet);

	void removeSelf();  //���ӵ�����Ļ���ʱ������

};
#endif // !__BULLET_H__