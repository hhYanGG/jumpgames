#ifndef _LIFE_BOJECT_H_
#define _LIFE_BOJECT_H_
#include "cocos2d.h"
#include "PhysicsSprite.h"
USING_NS_CC;
class LifeObject : public PhysicsSprite {
protected:
	bool die;
	bool over;
	//int dir;
public:
	

	/*virtual void setDir(int var) {
		dir = var;
	}

	virtual int getDir() {
		return dir;
	}*/

	virtual bool init(float x, float y, float width, float height) override;
	CREATE_FUNC_4(LifeObject, float, float, float, float);

	virtual bool init(float x, float y, b2Vec2* points, int count) override;
	CREATE_FUNC_4(LifeObject, float, float, b2Vec2*, int);

	//英雄所朝方向
	CC_SYNTHESIZE(int, dir, Dir);
	//血量
	CC_SYNTHESIZE(int, hp, Hp);	
	//攻击力
	CC_SYNTHESIZE(int, atk, Atk);	

	/*设置死亡状态*/
	virtual void setDie(bool die);
	/*判断当前生命体是否死亡*/
	virtual bool isDie() const;
	/*设置结束状态*/
	virtual void setOver(bool over);
	/*该生命体是否结束*/
	virtual bool isOver() const;

	/*逐帧回调函数*/
	virtual void update(float ft);
	
	/* 自动调用 死亡时的回调函数 动画神马的重写该函数即可 该函数会在hp低于0时自动调用一次*/
	virtual void dead();

	virtual void ended();
};

#endif