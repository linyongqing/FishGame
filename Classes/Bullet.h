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
	
	//指定发射子弹的方向
	void showTo(Vec2 targetDirection);
	//指定击中鱼的时候，播放撒网动画
	void showNet();
private:
	CC_SYNTHESIZE(GameLayer*, m_pGameLayer, GameLayer);
	CC_SYNTHESIZE(int, m_pBulletType, BulletType);
	CC_SYNTHESIZE(Sprite*, m_pSpriteBullet, SpriteBullet);
	CC_SYNTHESIZE(Sprite*, m_pSpriteNet, SpriteNet);

	//创建子弹的实例
	bool initWithBulletType(int bulletType, GameLayer *gameLayer, SpriteBatchNode *pBatchNodeBullet, SpriteBatchNode *pBatchNodeNet);

	void removeSelf();  //当子弹到屏幕外的时候，销毁

};
#endif // !__BULLET_H__