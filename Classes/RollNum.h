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
	int m_nNumber;  //��ǰ��ʾ������
	int m_nCurTexH; //��ǰ��ʾ���������λ��
	int m_nEndTexH; //��������ĸ߶�
	bool m_bRolling; //�༭��ǰ�����Ƿ��ڹ���
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
	int m_nDigit; //�������չʾ���ֵ�λ��
	int m_nValue; //����չʾ������
	bool intiWithGaneLayer(GameLayer *pGameLayer, int nDigit);
};
#endif // !__ROLLNUM_H__

