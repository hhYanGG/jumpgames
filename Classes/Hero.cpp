#include "Hero.h"
#include "PhysicsSprite.h"
#include "Define.h"
#include "GameManager.h"
#include "StaticData.h"
#include "OverScene.h"
#include "HudLayer.h"
#include "Grenade.h"

USING_NS_CC;

Size visibleSize = Director::getInstance()->getVisibleSize();
Vec2 origin = Director::getInstance()->getVisibleOrigin();


void Hero::initParam()
{
	startTag = true;
	jumpCount = 0;
	setCoin(0);//金币 todo
	

	speed = 0.5;	//行走速度
	spring = 1.6;	//弹跳力
	
	//设置朝向
	this->setDir(2);
	//设置血量
	this->setHp(3);
	//物体的类型
	this->setType(TYPE_HERO);
	//会和哪些物体方式碰撞
	this->setMask(
		TYPE_BRICK |
		TYPE_COIN |
		TYPE_MONSTER |
		TYPE_PRIZE |
		TYPE_ARTICLE |
		TYPE_WEAPON);
	//取消自旋转
	this->getBody()->SetFixedRotation(true);
	b2MassData mass;
	mass.mass = SD_FLOAT("hero_float_mass");
	mass.I = SD_FLOAT("hero_float_i");
	mass.center = this->getBody()->GetLocalCenter();
	this->getBody()->SetMassData(&mass);
	scheduleUpdate();
	//触动停止动画
	moveStop();
}

bool Hero::init(float x, float y, float width, float height)
{
	if (!PhysicsSprite::init(x, y, width, height))
	{
		return false;
	}
	initParam();

	return true;
}

bool Hero::init(float x, float y, b2Vec2* points, int count)
{
	if (!PhysicsSprite::init(x, y, points, count))
	{
		return false;
	}
	initParam();
	return true;
}

void Hero::dead()
{
	LifeObject::dead();
	this->moveStop();
	Animate* animate = GameManager::getInstance()->getAnimate("hero_dead", 0.4);
	Action* action = Sequence::createWithTwoActions(animate, CallFunc::create(CC_CALLBACK_0(Hero::ended, this)));
	this->stopAllActions();
	this->runAction(action);
}
void Hero::fire()
{
	if (isDie() || isOver())
		return;
	Grenade* g = Grenade::create(this);
	g->setScale(0.5, 0.5);
	GameManager::getInstance()->heroLayer->addChild(g, 51);
}

void Hero::ended()
{
	LifeObject::ended();
	auto over = OverScene::createScene(coin);
	Director::getInstance()->replaceScene(over);
}

void Hero::update(float ft)
{
	LifeObject::update(ft);
	/*向左移动*/
	if (moveState == 1)
	{
		b2Vec2 vec = this->getBody()->GetLinearVelocity();
		vec.x = -speed;
		this->getBody()->SetLinearVelocity(vec);
	}
	/*向右移动*/
	if (moveState == 2)
	{
		b2Vec2 vec = this->getBody()->GetLinearVelocity();
		vec.x = speed;
		this->getBody()->SetLinearVelocity(vec);
	}
	

}

void Hero::moveStop()
{
	//如果不是第一次stop  且未移动 那么不播放停止动作
	if (!startTag && moveState == 0)
	{
		return;
	}
	startTag = false;	//第一次标识更改false
	moveState = 0;
	b2Vec2 vec = this->getBody()->GetLinearVelocity();
	vec.x = 0;
	this->getBody()->SetLinearVelocity(vec);

	//停止动画

	Animate* animate = GameManager::getInstance()->getAnimate("hero_stop", 0.7);
	this->stopAllActions();
	this->runAction(RepeatForever::create(animate));
}

void Hero::moveLeft()
{
	if (moveState == 1)
		return;
	if (isDie() || isOver())
		return;

	this->setDir(1);
	moveState = 1;

	//播放动画
	Animate* animate = GameManager::getInstance()->getAnimate(SD_CHARS("hero_animate_walk_left"), SD_FLOAT("hero_float_walk_left_speed"));
	this->stopAllActions();
	this->runAction(RepeatForever::create(animate));
}

void Hero::moveRight()
{
	if (moveState == 2)
		return;
	if (isDie() || isOver())
		return;

	this->setDir(2);
	moveState = 2;

	//播放动画
	Animate* animate = GameManager::getInstance()->getAnimate(SD_CHARS("hero_animate_walk_right"), SD_FLOAT("hero_float_walk_right_speed"));
	this->stopAllActions();
	this->runAction(RepeatForever::create(animate));
}

void Hero::jump()
{
	if (jumpCount >= 2)
		return;
	if (isDie() || isOver())
		return;

	b2Vec2 vec = this->getBody()->GetLinearVelocity();
	vec.y = spring;
	this->getBody()->SetLinearVelocity(vec);

	jumpCount++; //累加 二段跳用
}

void Hero::BeginContact(PhysicsSprite* other, b2Contact* contact)
{
	if (other->getType() == TYPE_BRICK)
	{//踩到地板或者物体时候
	 //获取碰撞后产生的合力方向
		float y = contact->GetManifold()->localNormal.y;
		if (y > 0)
		{ //踩到地板
			jumpCount = 0;	//跳跃清零
		}
	}
	else if (other->getType() == TYPE_ARTICLE)
	{
		jumpCount = 0;
	}
}

void Hero::setCoin(int coin)
{
	this->coin = coin;
	////重新绘制钱包数量
	GameManager::getInstance()->hudLayer->replaceCoinHud();
}

int Hero::getCoin()
{
	return coin;
}

void Hero::setHp(int var)
{
	LifeObject::setHp(var);
	//更新HUD
	GameManager::getInstance()->hudLayer->replaceHpHud();
}

