#ifndef _OVER_SCENE_H_
#define _OVER_SCENE_H_

#include "cocos2d.h"
#include "PhysicsSprite.h"

class OverScene : public cocos2d::Layer
{
private:
	bool win;
	int coin;
	//int level;
public:
	static cocos2d::Scene* createScene(int coin);

	virtual bool init(int coin);

	//CREATE_FUNC(FinishScene);
	CREATE_FUNC_1(OverScene, int);

	void setCoin(int coin);

	void nextCallBack(cocos2d::Ref* ref);
	void againCallBack(cocos2d::Ref* ref);
};

#endif