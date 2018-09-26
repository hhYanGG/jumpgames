#include "Door.h"
#include "StaticData.h"
#include "OverScene.h"
#include "GameManager.h"
#include "Hero.h"
#include "PhysicsSprite.h"
USING_NS_CC;

bool Door::init(float x, float y, float width, float height)
{
	if (!PhysicsSprite::init(x, y, width, height))
	{
		return false;
	}
	
	this->getBody()->SetType(b2_staticBody);
	this->setType(TYPE_PRIZE);	//�൱��ս��Ʒ
	this->setMask(TYPE_HERO);

	return true;
}

void Door::BeginContact(PhysicsSprite* other, b2Contact* contact)
{
	contact->SetEnabled(false);
	//��Ӣ����ײʤ��
	if (other->getType() == TYPE_HERO)
	{
		auto over = OverScene::createScene(GameManager::getInstance()->hero->getCoin());
		Director::getInstance()->replaceScene(over);
	}
}

