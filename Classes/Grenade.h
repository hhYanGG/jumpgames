#ifndef _GRENADE_H_
#define _GRENADE_H_
/*
 ÷¡ÒµØ
*/
#include "LifeObject.h"

USING_NS_CC;
class Grenade : public LifeObject {
protected:
	float countTime;
	float bombTime;
public:
	virtual bool init(LifeObject* aware);
	CREATE_FUNC_1(Grenade, LifeObject*);

	virtual void dead();

	virtual void ended();

	virtual void update(float ft);

};

#endif