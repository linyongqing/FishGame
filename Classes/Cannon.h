#ifndef __CANNON_H__
#define __CANNON_H__

#include "cocos2d.h"

//��������
class GameLayer;

class Cannon : public cocos2d::Ref
{
public:
	//��̬������̨����
	//CannonType Ҫ������̨������  ����plist�ļ� 1 2 3 4 5 6 7
	//pGameLayer ��Ϸ�����ָ��
	//��Ϸ����� ����װ����̨������
	static Cannon *createWithCannonType(int cannonType, GameLayer* pGameLayer, cocos2d::SpriteBatchNode *pBatchNode);

	//������̨ת���û�������Ļ�ķ���
	//pt �û�������Ļ�ĵ�
	void rotateToPoint(cocos2d::Vec2 pt);

	void fire();  //�����ӵ�
	int getCannnType();  //��ȡ��ǰ�������͵�ID

	virtual ~Cannon();

private:
	Cannon();  //˽�л�
	Cannon(const Cannon &obj);  //˽�л�����ֹ��ǳ����
	//���캯������initWithCannonType����ʵ����
	Cannon(int cannonType, GameLayer *gameLayer);
	int m_nCannonType; //��ָ������̨����
	CC_SYNTHESIZE(GameLayer*, m_pGameLayer, GameLayer);

	float m_fRotation; //����� ��̨��Ҫת���ķ���

	cocos2d::Sprite *m_pSprite; //��̨�����ʵ��
	cocos2d::Vec2 m_pDirection; //���ڴ����ĵ㡢������̨��ת���ӵ������Ŀ�ķ���

	void setRotation(float rotation);  //������̨��ת�ĽǶ�

	bool initWithCannonType(cocos2d::SpriteBatchNode *pBatchNode);
};

#endif // !__CANNON_H__
