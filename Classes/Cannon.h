#ifndef __CANNON_H__
#define __CANNON_H__

#include "cocos2d.h"

//类型声明
class GameLayer;

class Cannon : public cocos2d::Ref
{
public:
	//静态创建炮台函数
	//CannonType 要创建炮台的类型  根据plist文件 1 2 3 4 5 6 7
	//pGameLayer 游戏世界的指针
	//游戏世界里， 用来装载炮台的容器
	static Cannon *createWithCannonType(int cannonType, GameLayer* pGameLayer, cocos2d::SpriteBatchNode *pBatchNode);

	//调度炮台转向到用户触摸屏幕的方向
	//pt 用户触摸屏幕的点
	void rotateToPoint(cocos2d::Vec2 pt);

	void fire();  //发射子弹
	int getCannnType();  //获取当前大炮类型的ID

	virtual ~Cannon();

private:
	Cannon();  //私有化
	Cannon(const Cannon &obj);  //私有化，防止被浅复制
	//构造函数，被initWithCannonType调用实例化
	Cannon(int cannonType, GameLayer *gameLayer);
	int m_nCannonType; //被指定的炮台类型
	CC_SYNTHESIZE(GameLayer*, m_pGameLayer, GameLayer);

	float m_fRotation; //计算后， 炮台需要转动的方向

	cocos2d::Sprite *m_pSprite; //炮台精灵的实例
	cocos2d::Vec2 m_pDirection; //用于触摸的点、储存炮台的转向、子弹发射的目的方向

	void setRotation(float rotation);  //设置炮台旋转的角度

	bool initWithCannonType(cocos2d::SpriteBatchNode *pBatchNode);
};

#endif // !__CANNON_H__
