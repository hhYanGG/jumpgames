#ifndef _DOOR_H_
#define _DOOR_H_
#include "PhysicsSprite.h"

class Door : public PhysicsSprite {
	public:
		virtual bool init(float x, float y, float width, float height);
		CREATE_FUNC_4(Door, float, float, float, float);

		virtual void BeginContact(PhysicsSprite* other, b2Contact* contact);

};
#endif // 
