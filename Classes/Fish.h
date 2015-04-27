#ifndef __FISH_H__
#define __FISH_H__
#include "cocos2d.h"

USING_NS_CC;
class GameLayer;
class Fish : public Ref
{
public:
	virtual ~Fish();
	//************************************
	// Method:    createWithFishType 创建一条鱼
	// Returns:   Fish *
	// Qualifier:
	// Parameter: int fishType	鱼的类型
	// Parameter: GameLayer * gameLayer		游戏主场景
	// Parameter: SpriteBatchNode * pBatchNodeFish	装载鱼的容器
	//************************************
	static Fish *createWithFishType(int fishType, GameLayer* gameLayer, SpriteBatchNode *pBatchNodeFish);
	void showCaught(); //展示鱼死亡的效果
public:
	//鱼是否被捕的标记
	CC_SYNTHESIZE_READONLY(bool, m_bCaught, Caught);
	CC_SYNTHESIZE_READONLY(Sprite*, m_pSpriteFish, SpriteFish); //被创建鱼的精灵

	void offsetPoit(Vec2 &pt, float offsetX, float offsetY);
private:
	//实际鱼被创建的地方
	bool initWithFishType(int fishType, GameLayer *gameLayer, SpriteBatchNode *pBatchNodeFish);

	//被捕的时候
	void removeSelf();

	//构造鱼的运动轨迹
	void getPath(MoveTo *&moveTo);

private:
	CC_SYNTHESIZE(GameLayer *, m_pGameLayer, GameLayer); //游戏主场景
	CC_SYNTHESIZE(SpriteBatchNode*, m_pBatchNodeFish, BatchNodeFish); //主场景用来装载鱼的地方
	CC_SYNTHESIZE(int, m_nFishType, FishType); //鱼的类型
	//某些鱼运动时，跟随的粒子效果
	CC_SYNTHESIZE(ParticleSystem*, m_pParticleBubble, ParticleBubble);
	//标记当前的鱼是否有粒子效果
	bool m_bParticleBulle;
};
#endif // !__FISH_H__
