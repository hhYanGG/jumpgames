#include "Wall.h"
#include "StaticData.h"

USING_NS_CC;

void Wall::initParam()
{
	this->getBody()->SetType(b2_staticBody);
	//��������
	this->setType(TYPE_BRICK);
	//���˭������ײ
	this->setMask(
		TYPE_HERO |
		TYPE_OBJECT |
		TYPE_COIN |
		TYPE_MONSTER |
		TYPE_ARTICLE |
		TYPE_WEAPON);
	//��������-һ�㲻��
	//this->setTexture(SD_STRING("wall_path_texture"));
}

bool Wall::init(float x, float y, float width, float height)
{
	if (!PhysicsSprite::init(x, y, width, height))
	{
		return false;
	}
	initParam();
	return true;
}

bool Wall::init(float x, float y, b2Vec2* points, int count)
{
	if (!PhysicsSprite::init(x, y, points, count))
	{
		return false;
	}
	initParam();
	return true;
}

