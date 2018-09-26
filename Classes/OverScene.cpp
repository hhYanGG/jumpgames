#include "GameManager.h"
#include "LevelScene.h"
#include "GameScene.h"
#include "Hero.h"
#include "HelloWorldScene.h"
#include "OverScene.h"
#include "StaticData.h"
#include "DynamicData.h"

USING_NS_CC;


cocos2d::Scene* OverScene::createScene(int coin)
{
	Scene* scene = Scene::create();
	Layer* layer = OverScene::create(coin);
	scene->addChild(layer);
	return scene;
}

bool OverScene::init(int coin) {

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	if (!Layer::init()) {
		return false;
	}
	setCoin(coin);

	Sprite* down_bk = Sprite::create("UI/GAME/bk.png");
	//down_bk->setAnchorPoint(Vec2(0, 0));
	down_bk->setPosition(visibleSize.width/2, visibleSize.height/2);
	this->addChild(down_bk);

	Menu* menu = Menu::create();
	menu->setAnchorPoint(Vec2(0, 0));
	menu->setPosition(0, 0);
	this->addChild(menu);

	if (!GameManager::getInstance()->hero->isDie()) { //通过关卡
	   //按钮
		MenuItemImage* buttonStart = MenuItemImage::create("UI/GAME/next1.png", "UI/GAME/next2.png", "UI/GAME/next2.png", CC_CALLBACK_1(OverScene::nextCallBack, this));
		buttonStart->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		menu->addChild(buttonStart);
	}
	else {
		MenuItemImage* buttonStart = MenuItemImage::create("UI/GAME/up_break.png", "UI/GAME/down_break.png", "UI/START_UI_UP_0003__.png", CC_CALLBACK_1(OverScene::againCallBack, this));
		buttonStart->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		menu->addChild(buttonStart);
	}
	return true;
}


void OverScene::setCoin(int coin)
{
	OverScene::coin = coin;
}

void OverScene::nextCallBack(cocos2d::Ref* ref) {
	//level
	int lastLevel = DynamicData::getInstance()->getLevel();
	if (lastLevel < 3)	//开启关卡
	{
		DynamicData::getInstance()->setLevel(GameScene::level + 1);
	}
	GameManager::destroyInstance();

	if (GameScene::level > 3)
	{
		Scene* scene = TransitionFade::create(1.0f, HelloWorld::createScene(), Color3B(0, 0, 0));
		Director::getInstance()->replaceScene(scene);
	}
	else
	{
		Scene* scene = TransitionFade::create(1.0f, GameScene::createScene(GameScene::level + 1), Color3B(0, 0, 0));
		Director::getInstance()->replaceScene(scene);
	}
}
void OverScene::againCallBack(cocos2d::Ref* ref) {
	GameManager::destroyInstance();

	//跳转场景
	Scene* scene = TransitionFade::create(1.0f, GameScene::createScene(GameScene::level), Color3B(0, 0, 0));
	Director::getInstance()->replaceScene(scene);
}