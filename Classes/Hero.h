#ifndef _HERO_H_
#define _HERO_H_
#include "cocos2d.h"
#include "PhysicsSprite.h"
#include "LifeObject.h"
USING_NS_CC;

class Hero : public LifeObject
{
protected:
	bool startTag;	//第一次开始标识
	int jumpCount;
	int coin;	//金币
	float speed;  //速度
	float spring;  //弹跳力
	//int dir; //1向左， 2向右
public:
	/*初始化英雄 只为了方便多态*/
	int moveState; //移动状态， 0：停止， 1:向左， 2:向右
	virtual void initParam();

	virtual bool init(float x, float y, float width, float height) override;

	CREATE_FUNC_4(Hero, float, float, float, float);

	virtual bool init(float x, float y, b2Vec2* points, int count) override;
	CREATE_FUNC_4(Hero, float, float, b2Vec2*, int);

	virtual void dead() override;

	virtual void ended()override;

	/*金币*/
	void setCoin(int coin);
	int getCoin();

	/*停止移动*/
	virtual void moveStop();
	/*向左移动*/
	virtual void moveLeft();
	/*向右移动*/
	virtual void moveRight();
	/*跳跃*/
	virtual void jump();
	/*开火*/
	virtual void fire();

	virtual void update(float ft) override;

	virtual void BeginContact(PhysicsSprite* other, b2Contact* contact);

	virtual void setHp(int var);

};

#endif