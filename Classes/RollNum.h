#ifndef __ROLLNUM_H__
#define __ROLLNUM_H__
#include "cocos2d.h"

class GameLayer;

class RollNum : public cocos2d::Sprite
{
public:
	RollNum();
	virtual ~RollNum();
	CREATE_FUNC(RollNum);
	CC_SYNTHESIZE(bool, m_bUp, UpDirection);
	void setNumber(int var, bool bUp);
	int getNumber();

private:
	bool init();
	int m_nNumber;  //当前显示的数字
	int m_nCurTexH; //当前显示数字纹理的位置
	int m_nEndTexH; //数字纹理的高度
	bool m_bRolling; //编辑当前数字是否在滚动
	cocos2d::Texture2D *m_pTexture;
	void updateNumber(float dt);

};


class RollNumGroup : public cocos2d::Ref
{
public:
	RollNumGroup();
	virtual ~RollNumGroup();
	static RollNumGroup *createWithGameLayer(GameLayer *pGameLayer, int nDigit);
	CC_SYNTHESIZE(cocos2d::SpriteBatchNode*, m_pBatchNode, BatchNode);
	CC_SYNTHESIZE(GameLayer*, m_pGameLayer, GameLayer);
	CC_SYNTHESIZE_RETAIN(cocos2d::Array*, m_pRollNumArray, RollNumArray);
	void setValue(int value);
	void setPosition(cocos2d::Vec2 pt);

private:
	cocos2d::Vec2 m_ptPosition;
	int m_nDigit; //这个用来展示数字的位数
	int m_nValue; //做被展示的数字
	bool intiWithGaneLayer(GameLayer *pGameLayer, int nDigit);
};
#endif // !__ROLLNUM_H__

