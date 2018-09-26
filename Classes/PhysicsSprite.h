#ifndef _PHYSICS_SPRITE_H_
#define _PHYSICS_SPRITE_H_

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "Define.h"

#define GRAVITY		5
#define PTM_RATIO	96.0f //96


#define CREATE_FUNC_1(varType, var1)\
public: static varType* create(var1 x)\
{\
	varType *pRet = new varType(); \
	if (pRet && pRet->init(x)) \
	{ \
	pRet->autorelease(); \
	return pRet; \
	} \
	else \
	{ \
	delete pRet; \
	pRet = NULL; \
	return NULL; \
	} \
}
/////////////////////////////////////////////////////////////////

#define CREATE_FUNC_2(varType, var1, var2)\
public: static varType* create(var1 x, var2 y)\
{\
	varType *pRet = new varType(); \
	if (pRet && pRet->init(x, y)) \
	{ \
	pRet->autorelease(); \
	return pRet; \
	} \
	else \
	{ \
	delete pRet; \
	pRet = NULL; \
	return NULL; \
	} \
}
/////////////////////////////////////////////////////////////////

#define CREATE_FUNC_3(varType, var1, var2, var3)\
public: static varType* create(var1 x, var2 y, var3 width)\
{\
	varType *pRet = new varType(); \
	if (pRet && pRet->init(x, y, width)) \
	{ \
	pRet->autorelease(); \
	return pRet; \
	} \
	else \
	{ \
	delete pRet; \
	pRet = NULL; \
	return NULL; \
	} \
}
/////////////////////////////////////////////////////////////////

#define CREATE_FUNC_4(varType, var1, var2, var3, var4)\
public: static varType* create(var1 x, var2 y, var3 width, var4 height)\
{\
	varType *pRet = new varType(); \
	if (pRet && pRet->init(x, y, width, height)) \
	{ \
	pRet->autorelease(); \
	return pRet; \
	} \
	else \
	{ \
	delete pRet; \
	pRet = NULL; \
	return NULL; \
	} \
}
/////////////////////////////////////////////////////////////////

#define CREATE_FUNC_5(varType, var1, var2, var3, var4, var5)\
public: static varType* create(var1 x, var2 y, var3 width, var4 height, var5 five)\
{\
	varType *pRet = new varType(); \
	if (pRet && pRet->init(x, y, width, height, five)) \
	{ \
	pRet->autorelease(); \
	return pRet; \
	} \
	else \
	{ \
	delete pRet; \
	pRet = NULL; \
	return NULL; \
	} \
}

class PhysicsSprite : public cocos2d::Sprite
{
protected:
	b2Body* body;
	b2Fixture* fixture;
	float width;
	float height;
public:
	virtual bool init(float x, float y, float width, float height);

	CREATE_FUNC_4(PhysicsSprite, float, float, float, float);
	virtual bool init(float x, float y, b2Vec2* points, int count);
	CREATE_FUNC_4(PhysicsSprite, float, float, b2Vec2*, int);

	void initBody(float x, float y, float width, float height);
	void initBody(float x, float y, b2Vec2* points, int count);

	/*������������ ��:���ˡ��ذ塢�Ѿ���  ��������ײ���  type�����ͷ�ļ�������*/
	virtual void setType(uint16 type);
	/*��ȡ�������� ��:���ˡ��ذ塢�Ѿ���  ��������ײ���  type�����ͷ�ļ�������*/
	virtual uint16 getType() const;
	/*���øþ��������Щ�������巢����ײ*/
	virtual void setMask(uint16 types);

	/*��ȡ��Χ�п�
	*ע�� ����ֵΪ��ʵ�����ص�λ
	*/
	virtual float getBodyBoundingBoxWidth();
	/*��ȡ��Χ�и�
	*ע�� ����ֵΪ��ʵ�����ص�λ
	*/
	virtual float getBodyBoundingBoxHeight();

	/*��ȡb2body����*/
	virtual b2Body* getBody() const;
	/*��ȡ��ǰ����ļо�*/
	virtual b2Fixture* getFixture() const;

	/* ��������body�뾫������ ��Ļ����Ϊ��λ
	*/
	virtual void setPhysicsSpritePosition(float x, float y);
	/* ��������body�뾫������ ��Ļ����Ϊ��λ
	*/
	virtual void setPhysicsSpritePosition(cocos2d::Vec2 vec2);
	/* ��������body����
	*/
	virtual void setPhysicsPosition(float x, float y);
	/* ��������body����
	*/
	virtual void setPhysicsPosition(cocos2d::Vec2 vec2);

	/* ֱ��ɾ����������뾫��
	*/
	virtual void removePhysicsSprite();
	/* ֱ��ɾ������body ע������ͬ��
	*/
	virtual void removeBody();

	/* ɾ�������뾫�� �Ƽ�*/
	virtual void autoRemovePhysicsSprite();

	virtual void BeginContact(PhysicsSprite* other, b2Contact* contact);
	virtual void EndContact(PhysicsSprite* other, b2Contact* contact);
	virtual void PreSolve(PhysicsSprite* other, b2Contact* contact, const b2Manifold* oldManifold);
	virtual void PostSolve(PhysicsSprite* other, b2Contact* contact, const b2ContactImpulse* impulse);
};

#endif