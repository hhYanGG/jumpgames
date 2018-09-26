#include "Monster.h"
#include "GameManager.h"
#include "Hero.h"
#include "StaticData.h"
USING_NS_CC;

bool Monster::init(float x, float y, float width, float height)
{
	if (!LifeObject::init(x, y, width, height))
	{
		return false;
	}

	this->setHp(SD_INT("slime_int_hp"));
	this->getBody()->SetType(b2_dynamicBody);
	this->setType(TYPE_MONSTER);
	this->setMask(
		TYPE_ARTICLE |
		TYPE_BRICK |
		TYPE_HERO |
		TYPE_WEAPON);
	this->setDir(1);
	this->setSpeed(0.1);

	return true;
}

void Monster::update(float ft)
{
	LifeObject::update(ft);

	if (this->isDie())
		return;
	//向着英雄靠拢
	b2Vec2 vec = this->getBody()->GetLinearVelocity();

	float heroX = GameManager::getInstance()->hero->getPositionX();
	float heroY = GameManager::getInstance()->hero->getPositionY();
	//作用范围
	if (abs(this->getPosition().x - heroX) > 50 || abs(this->getPosition().y - heroY) > 50)
	{
		vec.x = 0;
		vec.y = 0;
		this->getBody()->SetLinearVelocity(vec);
		return;
	}

	if (heroX < this->getPositionX())
	{
		if (getDir() != 1)
		{
			setDir(1);
			moveLeft();
		}
		vec.x = -getSpeed();
	}
	else
	{
		if (getDir() != 2)
		{
			setDir(2);
			moveRight();
		}
		vec.x = getSpeed();
	}

	this->getBody()->SetLinearVelocity(vec);
}

void Monster::moveLeft()
{
	//设置动画
	Animate* action = GameManager::getInstance()->getAnimate(SD_CHARS("slime_animate_walk_left"), SD_FLOAT("slime_float_walk_left_speed"));
	this->stopAllActions();
	this->runAction(RepeatForever::create(action));
}

void Monster::moveRight()
{
	//设置动画
	Animate* action = GameManager::getInstance()->getAnimate(SD_CHARS("slime_animate_walk_right"), SD_FLOAT("slime_float_walk_right_speed"));
	this->stopAllActions();
	this->runAction(RepeatForever::create(action));
}

void Monster::dead()
{
	LifeObject::dead();
	setMask(
		0);

	Animate* animate = GameManager::getInstance()->getAnimate(SD_CHARS("slime_animate_dead"), SD_FLOAT("slime_float_dead_speed"));
	Sequence* action = Sequence::createWithTwoActions(
		animate,
		CallFunc::create(CC_CALLBACK_0(Monster::ended, this)));
	this->stopAllActions();
	this->runAction(action);
	this->getBody()->SetLinearVelocity(b2Vec2(0, 2));
}

void Monster::ended()
{
	LifeObject::ended();
	this->autoRemovePhysicsSprite();
}

void Monster::PreSolve(PhysicsSprite* other, b2Contact* contact, const b2Manifold* oldManifold)
{
	if (other->getType() == TYPE_HERO)
	{
		Hero* hero = GameManager::getInstance()->hero;
		if (hero->isDie())
			return;
		hero->setHp(hero->getHp() - 1);
		//应当英雄受伤后设置一个短暂的无敌时间

		//获取碰撞后产生的合力方向
		float y = contact->GetManifold()->localNormal.y;
		if (y < 0)
		{
			b2Vec2 vec = hero->getBody()->GetLinearVelocity();
			vec.y = 1;
			//使英雄跳跃
			hero->getBody()->SetLinearVelocity(vec);
			
			this->setHp(getHp() - 1);
		}
	}
}
