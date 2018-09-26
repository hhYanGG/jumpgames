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
	setCoin(0);//��� todo
	

	speed = 0.5;	//�����ٶ�
	spring = 1.6;	//������
	
	//���ó���
	this->setDir(2);
	//����Ѫ��
	this->setHp(3);
	//���������
	this->setType(TYPE_HERO);
	//�����Щ���巽ʽ��ײ
	this->setMask(
		TYPE_BRICK |
		TYPE_COIN |
		TYPE_MONSTER |
		TYPE_PRIZE |
		TYPE_ARTICLE |
		TYPE_WEAPON);
	//ȡ������ת
	this->getBody()->SetFixedRotation(true);
	b2MassData mass;
	mass.mass = SD_FLOAT("hero_float_mass");
	mass.I = SD_FLOAT("hero_float_i");
	mass.center = this->getBody()->GetLocalCenter();
	this->getBody()->SetMassData(&mass);
	scheduleUpdate();
	//����ֹͣ����
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
	/*�����ƶ�*/
	if (moveState == 1)
	{
		b2Vec2 vec = this->getBody()->GetLinearVelocity();
		vec.x = -speed;
		this->getBody()->SetLinearVelocity(vec);
	}
	/*�����ƶ�*/
	if (moveState == 2)
	{
		b2Vec2 vec = this->getBody()->GetLinearVelocity();
		vec.x = speed;
		this->getBody()->SetLinearVelocity(vec);
	}
	

}

void Hero::moveStop()
{
	//������ǵ�һ��stop  ��δ�ƶ� ��ô������ֹͣ����
	if (!startTag && moveState == 0)
	{
		return;
	}
	startTag = false;	//��һ�α�ʶ����false
	moveState = 0;
	b2Vec2 vec = this->getBody()->GetLinearVelocity();
	vec.x = 0;
	this->getBody()->SetLinearVelocity(vec);

	//ֹͣ����

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

	//���Ŷ���
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

	//���Ŷ���
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

	jumpCount++; //�ۼ� ��������
}

void Hero::BeginContact(PhysicsSprite* other, b2Contact* contact)
{
	if (other->getType() == TYPE_BRICK)
	{//�ȵ��ذ��������ʱ��
	 //��ȡ��ײ������ĺ�������
		float y = contact->GetManifold()->localNormal.y;
		if (y > 0)
		{ //�ȵ��ذ�
			jumpCount = 0;	//��Ծ����
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
	////���»���Ǯ������
	GameManager::getInstance()->hudLayer->replaceCoinHud();
}

int Hero::getCoin()
{
	return coin;
}

void Hero::setHp(int var)
{
	LifeObject::setHp(var);
	//����HUD
	GameManager::getInstance()->hudLayer->replaceHpHud();
}

