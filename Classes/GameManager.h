#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include "cocos2d.h"
#include "PhysicsSprite.h"
#include "Hero.h"
#include "HudLayer.h"
class PhysicsSprite;
class Hero;


enum GAME_STATIC
{
	WIN,
	FAILED,
	PLAYING
};

class GameManager : public cocos2d::Ref, public b2ContactListener
{
private:
	static GameManager* gameManager;
	cocos2d::Vector<PhysicsSprite*> _deleteSprites;	//��ɾ����������
	b2World* world;
	float sceneX;	//��Ļ��ǰλ��X
	float sceneY;	//��Ļ��ǰλ��Y
					//int level;
	GameManager();
public:
	cocos2d::Layer* staticLayer;	//��̬�� �ײ�
	cocos2d::Layer* gameLayer;		//��Ϸ����--��ͼ��
	cocos2d::Layer* bkLayer;		//�Ӳ����
	cocos2d::Layer* settingLayer;	//���ò�
	cocos2d::Layer* weaponLayer;	//�ӵ���
	cocos2d::Layer* heroLayer;		//Ӣ�۲�
	cocos2d::Layer* monsterLayer;	//�����
	cocos2d::Layer* thingLayer;		//�����
	HudLayer* hudLayer;
	int level;
	Hero* hero;			//Ӣ��
public:
	static GameManager* getInstance();
	static void destroyInstance();
	~GameManager();

	/*��ʼ����������*/
	void initPhysicsWorld(float gravity);
	/*������������*/
	void step(float time);
	/*��ȡ��������*/
	b2World* getWorld();

	///*��ʼ����Դ*/
	void initRes();

	/*��ȡAnimation*/
	cocos2d::Animation* getAnimation(const char* src, float delay = 0.0f, unsigned int loops = 1U);
	/*��ȡAnimate*/
	cocos2d::Animate* getAnimate(const char* src, float delay = 0.0f, unsigned int loops = 1U);

	/*������ѹ��ɾ��ջ*/
	void pushDeleteSprite(PhysicsSprite* sprite);

	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

	 	/*��ǰ�ؿ�*/
	 void setLevel(int level);
	 int getLevel();
};

#endif	