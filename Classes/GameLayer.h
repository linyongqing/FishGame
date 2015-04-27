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

	//�����¼�
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);

	CC_SYNTHESIZE_RETAIN(Array*, m_pBullets, Bullets); //�����ֶζ���ָ��
	CC_SYNTHESIZE_RETAIN(Array*, m_pFishes, Fishes);	//���������ָ��

	CC_SYNTHESIZE(RollNumGroup*, m_pRollNumGroup, RollNumGroup);

	//����װ������ӵ��������Դ�����������Ƿֱ��Ӧ����һ��ͼƬ��Դ
	CC_SYNTHESIZE(SpriteBatchNode*, m_pBatchNodeFishes1, BatchNodeFishes1);
	CC_SYNTHESIZE(SpriteBatchNode*, m_pBatchNodeFishes2AndBullets, BatchNodeFishes2AndBullets);
	CC_SYNTHESIZE(SpriteBatchNode*, m_pBatchNodeFishes3AndNets, BatchNodeFishes3AndNets);
	CC_SYNTHESIZE(SpriteBatchNode*, m_pBatchNodeFishes4, BatchNodeFishes4);

	//ʹ��CREATE_FUNC �괴����ǰ��Ķ���
	CREATE_FUNC(GameLayer);
private:
	int m_nScore;
	GameLayer(const GameLayer &other);
	CC_SYNTHESIZE_RETAIN(Cannon*, m_pCannon, Cannon);  //��̨
	Sprite *m_pSpriteAdd; //��̨����
	Sprite *m_pSpriteReduce; //��̨����

	void initFrames(); //������Ҫ�õ���plist�ļ�
	void initBackground(); //������Ϸ��������̨����
	void initCannon();   //����
	void initFishes();   //��������ӵ���Դ
	void updateGame(float dt);   //������Ϸ�����߼�
	void updateFishes(float dt);   //�㴴���߼�
	void addFishes();     //����Ϸ���������
	void initListeners();  //�¼�������
	void addCannon();  //���������ͺ�
	void reduceCannon();  //���������ͺ�
};
#endif // !__GameLayer_H__
