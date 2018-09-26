#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//背景
	Sprite* background = Sprite::create("UI/START/background.png");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(background);
		    
	//开始按钮
	MenuItemImage* buttonStart = MenuItemImage::create("UI/START/start-up.png", "UI/START/start-down.png",  CC_CALLBACK_1(HelloWorld::startCallBack, this));
	buttonStart->setPosition(visibleSize.width / 2, visibleSize.height / 2.5);

	//关于按钮
	MenuItemImage* buttonAbout = MenuItemImage::create("UI/START/START_UI_UP_0003__.png", "UI/START/START_UI_DOWN_0003__.png", CC_CALLBACK_1(HelloWorld::aboutCallBack, this));
	buttonAbout->setScale(0.5, 0.5);
	buttonAbout->setPosition(visibleSize.width / 6, visibleSize.height / 6);

	//退出按钮
	MenuItemImage* exitStart = MenuItemImage::create("UI/START/exit-up.png", "UI/START/exit-down.png", CC_CALLBACK_1(HelloWorld::exitCallBack, this));
	exitStart->setPosition(visibleSize.width / 2, visibleSize.height / 4.5);

	Menu* menu = Menu::create(buttonStart, buttonAbout, exitStart, NULL);
	menu->setPosition(0, 0);
	this->addChild(menu, 1);
    
    return true;
}


void HelloWorld::aboutCallBack(cocos2d::Ref* ref)
{
	auto reScene = TransitionCrossFade::create(0.3f, AboutScene::createScene());
	Director::getInstance()->pushScene(reScene);
}

void HelloWorld::startCallBack(cocos2d::Ref* ref)
{
	auto reScene = TransitionCrossFade::create(0.3f, LevelScene::createScene());
	Director::getInstance()->replaceScene(reScene);
}

void HelloWorld::exitCallBack(cocos2d::Ref* ref)
{
	Director::getInstance()->end();
}