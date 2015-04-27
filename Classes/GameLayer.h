#ifndef __GameLayer_H__
#define __GameLayer_H__

#include "cocos2d.h"
#include "Cannon.h"
#include "Bullet.h"
#include "GameConfig.h"
#include "Fish.h"
#include "RollNum.h"

USING_NS_CC;

class GameLayer : public Layer
{
public:
	GameLayer();
	virtual ~GameLayer();
	virtual bool init();
	static Scene* scene();

	//触摸事件
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);

	CC_SYNTHESIZE_RETAIN(Array*, m_pBullets, Bullets); //储存字段对象指针
	CC_SYNTHESIZE_RETAIN(Array*, m_pFishes, Fishes);	//储存鱼对象指针

	CC_SYNTHESIZE(RollNumGroup*, m_pRollNumGroup, RollNumGroup);

	//用来装载鱼和子弹的相关资源的容器，他们分别对应加载一张图片资源
	CC_SYNTHESIZE(SpriteBatchNode*, m_pBatchNodeFishes1, BatchNodeFishes1);
	CC_SYNTHESIZE(SpriteBatchNode*, m_pBatchNodeFishes2AndBullets, BatchNodeFishes2AndBullets);
	CC_SYNTHESIZE(SpriteBatchNode*, m_pBatchNodeFishes3AndNets, BatchNodeFishes3AndNets);
	CC_SYNTHESIZE(SpriteBatchNode*, m_pBatchNodeFishes4, BatchNodeFishes4);

	//使用CREATE_FUNC 宏创建当前类的对象
	CREATE_FUNC(GameLayer);
private:
	int m_nScore;
	GameLayer(const GameLayer &other);
	CC_SYNTHESIZE_RETAIN(Cannon*, m_pCannon, Cannon);  //炮台
	Sprite *m_pSpriteAdd; //炮台升级
	Sprite *m_pSpriteReduce; //炮台降级

	void initFrames(); //载入需要用到的plist文件
	void initBackground(); //加载游戏背景，炮台基座
	void initCannon();   //大炮
	void initFishes();   //加载鱼和子弹资源
	void updateGame(float dt);   //更新游戏整体逻辑
	void updateFishes(float dt);   //鱼创建逻辑
	void addFishes();     //往游戏世界添加鱼
	void initListeners();  //事件监听器
	void addCannon();  //升级大炮型号
	void reduceCannon();  //降级大炮型号
};
#endif // !__GameLayer_H__
