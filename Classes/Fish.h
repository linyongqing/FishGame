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
	// Method:    createWithFishType ����һ����
	// Returns:   Fish *
	// Qualifier:
	// Parameter: int fishType	�������
	// Parameter: GameLayer * gameLayer		��Ϸ������
	// Parameter: SpriteBatchNode * pBatchNodeFish	װ���������
	//************************************
	static Fish *createWithFishType(int fishType, GameLayer* gameLayer, SpriteBatchNode *pBatchNodeFish);
	void showCaught(); //չʾ��������Ч��
public:
	//���Ƿ񱻲��ı��
	CC_SYNTHESIZE_READONLY(bool, m_bCaught, Caught);
	CC_SYNTHESIZE_READONLY(Sprite*, m_pSpriteFish, SpriteFish); //��������ľ���

	void offsetPoit(Vec2 &pt, float offsetX, float offsetY);
private:
	//ʵ���㱻�����ĵط�
	bool initWithFishType(int fishType, GameLayer *gameLayer, SpriteBatchNode *pBatchNodeFish);

	//������ʱ��
	void removeSelf();

	//��������˶��켣
	void getPath(MoveTo *&moveTo);

private:
	CC_SYNTHESIZE(GameLayer *, m_pGameLayer, GameLayer); //��Ϸ������
	CC_SYNTHESIZE(SpriteBatchNode*, m_pBatchNodeFish, BatchNodeFish); //����������װ����ĵط�
	CC_SYNTHESIZE(int, m_nFishType, FishType); //�������
	//ĳЩ���˶�ʱ�����������Ч��
	CC_SYNTHESIZE(ParticleSystem*, m_pParticleBubble, ParticleBubble);
	//��ǵ�ǰ�����Ƿ�������Ч��
	bool m_bParticleBulle;
};
#endif // !__FISH_H__
