#ifndef _BRICK_H_
#define _BRICK_H_

#include "PhysicsSprite.h"

class Brick : public PhysicsSprite
{
private:
	/*初始化Brick 只为了方便多态*/
	void initBrick();
protected:
public:
	virtual bool init(float x, float y, float width, float height) override;
	CREATE_FUNC_4(Brick, float, float, float, float);

	virtual bool init(float x, float y, b2Vec2* points, int count) override;
	CREATE_FUNC_4(Brick, float, float, b2Vec2*, int);

};

#endif