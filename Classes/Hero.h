#ifndef _HERO_H_
#define _HERO_H_
#include "cocos2d.h"
#include "PhysicsSprite.h"
#include "LifeObject.h"
USING_NS_CC;

class Hero : public LifeObject
{
protected:
	bool startTag;	//��һ�ο�ʼ��ʶ
	int jumpCount;
	int coin;	//���
	float speed;  //�ٶ�
	float spring;  //������
	//int dir; //1���� 2����
public:
	/*��ʼ��Ӣ�� ֻΪ�˷����̬*/
	int moveState; //�ƶ�״̬�� 0��ֹͣ�� 1:���� 2:����
	virtual void initParam();

	virtual bool init(float x, float y, float width, float height) override;

	CREATE_FUNC_4(Hero, float, float, float, float);

	virtual bool init(float x, float y, b2Vec2* points, int count) override;
	CREATE_FUNC_4(Hero, float, float, b2Vec2*, int);

	virtual void dead() override;

	virtual void ended()override;

	/*���*/
	void setCoin(int coin);
	int getCoin();

	/*ֹͣ�ƶ�*/
	virtual void moveStop();
	/*�����ƶ�*/
	virtual void moveLeft();
	/*�����ƶ�*/
	virtual void moveRight();
	/*��Ծ*/
	virtual void jump();
	/*����*/
	virtual void fire();

	virtual void update(float ft) override;

	virtual void BeginContact(PhysicsSprite* other, b2Contact* contact);

	virtual void setHp(int var);

};

#endif