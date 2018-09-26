#include "Brick.h"

USING_NS_CC;

void Brick::initBrick() {
	this->getBody()->SetType(b2_staticBody);
	//物体类型
	this->setType(TYPE_BRICK);
	//会和谁发生碰撞
	this->setMask(
		TYPE_HERO |
		TYPE_OBJECT |
		TYPE_COIN |
		TYPE_MONSTER |
		TYPE_ARTICLE |
		TYPE_WEAPON);
}

bool Brick::init(float x, float y, float width, float height)
{
	if (!PhysicsSprite::init(x, y, width, height))
	{
		return false;
	}
	initBrick();
	return true;
}

bool Brick::init(float x, float y, b2Vec2* points, int count)
{
	if (!PhysicsSprite::init(x, y, points, count))
	{
		return false;
	}
	initBrick();
	return true;
}

