#include "Hero.h"
#include "PhysicsSprite.h"
#include "Define.h"
#include "GameManager.h"
#include "StaticData.h"
#include "OverScene.h"
#include "HudLayer.h"
#include "Grenade.h"

USING_NS_CC;

bool Grenade::init(LifeObject* hero)
{
	//位置和碰撞大小
	if (!LifeObject::init(hero->getPositionX(), hero->getPositionY(), 7, 7))
		return false;

	countTime = 0;
	bombTime = 2;	//2秒后引燃爆炸
	this->getBody()->SetFixedRotation(true);
	this->setTexture(SD_STRING("grenade_path_texture"));
	this->getBody()->SetFixedRotation(true);
	this->getBody()->SetBullet(true);
	this->getFixture()->SetRestitution(0.2);	//弹力
	this->getFixture()->SetFriction(0.8);	//摩擦力

	b2MassData mass;
	mass.mass = SD_FLOAT("grenade_float_mass");
	mass.I = SD_FLOAT("grenade_float_i");
	mass.center = this->getBody()->GetLocalCenter();
	this->getBody()->SetMassData(&mass);

	this->setType(TYPE_WEAPON);
	if (hero->getType() == TYPE_HERO)
		this->setMask(
			TYPE_WEAPON |
			TYPE_BRICK |
			TYPE_MONSTER |
			TYPE_ARTICLE);
	else
		this->setMask(
			TYPE_BRICK |
			TYPE_HERO |
			TYPE_ARTICLE);

	int dir = hero->getDir();
	this->setDir(dir);

	////扔出手雷
	if (this->getDir() == 1)
	{
		this->getBody()->SetAngularVelocity(0.3);
		this->getBody()->SetLinearVelocity(b2Vec2(-3, 2));
	}
	else
	{
		this->getBody()->SetAngularVelocity(0.3);
		this->getBody()->SetLinearVelocity(b2Vec2(3, 2));
	}
		
	return true;
}

void Grenade::dead()
{
	LifeObject::dead();
	this->getBody()->SetType(b2_kinematicBody);
	//播放爆炸动画
	Animate* animate = GameManager::getInstance()->getAnimate(SD_CHARS("grenade_animate_dead"), SD_FLOAT("grenade_float_dead_speed"));
	Sequence* action = Sequence::createWithTwoActions(
		animate,
		CallFunc::create(CC_CALLBACK_0(Grenade::ended, this)));
	this->stopAllActions();
	this->runAction(action);

}

void Grenade::ended()
{
	LifeObject::ended();
	this->autoRemovePhysicsSprite();
}

void Grenade::update(float ft)
{
	LifeObject::update(ft);
	//countTime = countTime + ft;
	//if (!isDie() && countTime >= bombTime)	//N秒后开始引燃手榴弹
	//{
	//	dead();
	//}
}

