#include "GameScene.h"
#include "LevelScene.h"
#include "HelloWorldScene.h"
USING_NS_CC;

cocos2d::Scene* LevelScene::createScene()
{
	Scene* scene = Scene::create();
	Layer* layer = LevelScene::create();
	scene->addChild(layer);

	return scene;
}

bool LevelScene::init() {
	if (!Layer::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//添加背景
	Sprite * bg = Sprite::create("UI/LEVEL/background.png");
	bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(bg, 0);

	//菜单
	Menu* menu = Menu::create();
	menu->setPosition(0, 0);
	this->addChild(menu);

	//返回按钮
	MenuItemImage* buttonBack = MenuItemImage::create("UI/LEVEL/back-up.png", "UI/LEVEL/back-down.png", "UI/LEVEL/back-up.png", CC_CALLBACK_1(LevelScene::backCallBack, this));
	buttonBack->setPosition(visibleSize.width / 4.5, visibleSize.height / 8);
	menu->addChild(buttonBack);

	//动态生成关卡按钮
	for (int i = 1; i <= 3; i++)
	{
		char but_name_up[32];
		sprintf(but_name_up, "UI/LEVEL/level-%d-up.png", i);
		char but_name_down[32];
		sprintf(but_name_down, "UI/LEVEL/level-%d-down.png", i);

		MenuItemImage* bm = MenuItemImage::create(but_name_up, but_name_down, "UI/LEVEL/level-locked.png", CC_CALLBACK_1(LevelScene::levelsCallBack, this));
		bm->setPosition(visibleSize.width * (0.5 + (i - 2) * 0.2), visibleSize.height / 2.5);
		bm->setTag(i);

		menu->addChild(bm);
	}
	return true;	
}

void LevelScene::backCallBack(cocos2d::Ref* ref) {
	auto reScene = TransitionCrossFade::create(0.3f, HelloWorld::createScene());
	Director::getInstance()->pushScene(reScene);
}

void LevelScene::levelsCallBack(cocos2d::Ref* ref) {
	int level = ((MenuItemImage*)ref)->getTag();
	auto reScene = TransitionFade::create(0.5f, GameScene::createScene(level));
	Director::getInstance()->replaceScene(reScene);
}