#include "Spikes.h"
#include "Hero.h"
#include "StaticData.h"

USING_NS_CC;

bool Spikes::init(float x, float y, float width, float height)
{
	if (!PhysicsSprite::init(x, y, width, height))
	{
		return false;
	}
	atk = SD_INT("spikes_int_atk");

	this->getBody()->SetType(b2_staticBody);
	this->setType(TYPE_BRICK);
	this->setMask(TYPE_HERO);
	return true;
}

void Spikes::PreSolve(PhysicsSprite* other, b2Contact* contact, const b2Manifold* oldManifold)
{
	contact->SetEnabled(false);
	if (other->getType() == TYPE_HERO)
	{
		Hero* hero = (Hero*)other;
		hero->setHp(hero->getHp() - atk);

	}
}
