
#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_
#include "cocos2d.h"
#include "Hero.h"
#include "HudLayer.h"
class GameScene : public cocos2d::LayerColor
{
private:
	bool pause;			//��ͣ��ʶ
	cocos2d::Layer* staticLayer;	//��̬�� - ����
	cocos2d::Layer* gameLayer;		//��Ϸ����--��ͼ�㣺staticLayer
	cocos2d::Layer* bkLayer;		//������-�Ӳ��
	cocos2d::Layer* settingLayer;	//���ò�
	cocos2d::Layer* weaponLayer;	//��Ч��
	HudLayer* hudLayer;
	cocos2d::Layer* heroLayer;		//Ӣ�۲�
	cocos2d::Layer* monsterLayer;	//�����
	cocos2d::Layer* thingLayer;		//�����

	Hero* hero;			//Ӣ��
	bool _left;
	bool _right;
public:
	static int level;

	static cocos2d::Scene* createScene(int level);

	virtual bool init();

	CREATE_FUNC(GameScene);

	void update(float time);

	void setLeft(bool left);
	bool isLeft();
	void setRight(bool right);
	bool isRight();

	//��ͣ��İ�ť�ص�
	void pauseButton(Ref* ref);
	void backButton(Ref* ref);
	void homeButton(Ref* ref);
	void breakButton(Ref* ref);
};

#endif