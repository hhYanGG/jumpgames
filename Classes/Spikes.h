#ifndef _SPIKES_H_
#define _SPIKES_H_

#include "PhysicsSprite.h"

/*·æ´Ì*/
class Spikes : public PhysicsSprite
{
private:
	int atk;
public:
	virtual bool init(float x, float y, float width, float height);
	CREATE_FUNC_4(Spikes, float, float, float, float);

	virtual void PreSolve(PhysicsSprite* other, b2Contact* contact, const b2Manifold* oldManifold);
};
#endif