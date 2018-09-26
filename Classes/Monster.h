#ifndef _SLIME_H_
#define _SLIME_H_

#include "LifeObject.h"
#include "PhysicsSprite.h"

class Monster : public LifeObject
{
protected:
	CC_SYNTHESIZE(float, speed, Speed);
	CC_SYNTHESIZE(int, dir, Dir);
public:
	
	virtual bool init(float x, float y, float width, float height) override;
	CREATE_FUNC_4(Monster, float, float, float, float);

	virtual void update(float ft);

	virtual void dead();

	virtual void ended();
	/*
	virtual void BeginContact(GameObject* other, b2Contact* contact);
	*/
	virtual void PreSolve(PhysicsSprite* other, b2Contact* contact, const b2Manifold* oldManifold);
	/*向左移动*/
	virtual void moveLeft();
	/*向右移动*/
	virtual void moveRight();
};

#endif
