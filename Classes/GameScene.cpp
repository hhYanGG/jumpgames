#include "GameScene.h"
#include "HelloWorldScene.h"
#include "MapScene.h"
#include "GameManager.h"
#include "StaticData.h"
#include "PhysicsSprite.h"
#include "HudLayer.h"

USING_NS_CC;

int GameScene::level = 1;

Scene* GameScene::createScene(int level) {
	GameScene::level = level;
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init() {
	if (!LayerColor::initWithColor(Color4B(0, 250, 250, 255)))
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	
	
	pause = false;	//暂停标识为假

	staticLayer = this;		//游戏静态层
	GameManager::getInstance()->staticLayer = staticLayer;

	gameLayer = Layer::create();		//游戏主层
	GameManager::getInstance()->gameLayer = gameLayer;
	staticLayer->addChild(gameLayer);

	ParallaxNode* praNode = ParallaxNode::create();
	bkLayer = Layer::create();		//背景层-视差层
	GameManager::getInstance()->bkLayer = bkLayer;
	gameLayer->addChild(praNode, -2); //应该小于加载地图层
	praNode->addChild(bkLayer, 1, Vec2(0.5, 0.8), Vec2(0, 0));
		
	thingLayer = Layer::create();		//事物层
	GameManager::getInstance()->thingLayer = thingLayer;
	gameLayer->addChild(thingLayer);

	monsterLayer = Layer::create();	//怪物层
	GameManager::getInstance()->monsterLayer = monsterLayer;
	gameLayer->addChild(monsterLayer);

	heroLayer = Layer::create();		//英雄层
	GameManager::getInstance()->heroLayer = heroLayer;
	gameLayer->addChild(heroLayer, 10);

	weaponLayer = Layer::create();	//特效层
	GameManager::getInstance()->weaponLayer = weaponLayer;
	gameLayer->addChild(weaponLayer);

	hudLayer = HudLayer::create();	//HUD层----------todo
	GameManager::getInstance()->hudLayer = hudLayer;
	staticLayer->addChild(hudLayer);

	settingLayer = Layer::create();	//设置层
	GameManager::getInstance()->settingLayer = settingLayer;
	staticLayer->addChild(settingLayer);

	
	////////设置层初始化/////////
	//默认不打开设置层
	settingLayer->setVisible(false);
	//背景
	Sprite* settingBk = Sprite::create("UI/GAME/bk.png");
	//settingBk->setAnchorPoint(Vec2(0, 0));
	settingBk->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	settingLayer->addChild(settingBk);


	//菜单
	Menu* settingMenu = Menu::create();
	settingMenu->setAnchorPoint(Vec2(0, 0));
	settingMenu->setPosition(0, 0);
	settingLayer->addChild(settingMenu);
	//返回按钮
	MenuItemImage* backButton = MenuItemImage::create("UI/GAME/up_back.png", "UI/GAME/down_back.png", "UI/GAME/down_back.png", CC_CALLBACK_1(GameScene::backButton, this));
	backButton->setPosition(visibleSize.width * 0.3, visibleSize.height / 2);
	settingMenu->addChild(backButton);
	MenuItemImage* homeButton = MenuItemImage::create("UI/GAME/up_home.png", "UI/GAME/down_home.png", "UI/GAME/down_home.png", CC_CALLBACK_1(GameScene::homeButton, this));
	homeButton->setPosition(visibleSize.width * 0.5, visibleSize.height / 2);
	settingMenu->addChild(homeButton);
	MenuItemImage* breakButton = MenuItemImage::create("UI/GAME/up_break.png", "UI/GAME/down_break.png", "UI/GAME/down_break.png", CC_CALLBACK_1(GameScene::breakButton, this));
	breakButton->setPosition(visibleSize.width * 0.7, visibleSize.height / 2);
	settingMenu->addChild(breakButton);

	/////初始化地图////////
	

	MapScene* mapAnalysis = MapScene::getInstance();
	mapAnalysis->initMap(level);
	hero= GameManager::getInstance()->hero ;
	
	
	//操作的按键
	//按键精灵
	Sprite* but_left = Sprite::create("HUD/button_up_left.png");
	but_left->setAnchorPoint(Vec2(0, 0));
	but_left->setPosition(but_left->getContentSize().width / 2, but_left->getContentSize().height / 2);
	hudLayer->addChild(but_left);

	Sprite* but_right = Sprite::create("HUD/button_up_right.png");
	but_right->setAnchorPoint(Vec2(0, 0));
	but_right->setPosition(but_right->getContentSize().width * 2, but_right->getContentSize().height / 2);
	hudLayer->addChild(but_right);

	Sprite* but_A = Sprite::create("HUD/button_up_A.png");
	but_A->setAnchorPoint(Vec2(0, 0));
	but_A->setPosition(visibleSize.width - but_A->getContentSize().width * 5 / 2, but_A->getContentSize().width / 2);
	hudLayer->addChild(but_A);

	Sprite* but_B = Sprite::create("HUD/button_up_B.png");
	but_B->setAnchorPoint(Vec2(0, 0));
	but_B->setPosition(visibleSize.width - but_A->getContentSize().width * 1.4, but_A->getContentSize().width / 2);
	hudLayer->addChild(but_B);

	//hud菜单
	Menu* hudMenu = Menu::create();
	hudMenu->setAnchorPoint(Vec2(0, 0));
	hudMenu->setPosition(0, 0);
	hudLayer->addChild(hudMenu);
	//暂停按钮
	MenuItemImage* pauseButton = MenuItemImage::create("UI/GAME/pause_up.png", "UI/GAME/pause_down.png", "UI/GAME/pause_down.png", CC_CALLBACK_1(GameScene::pauseButton, this));
	pauseButton->setPosition(visibleSize.width / 8 * 7, visibleSize.height / 8 * 7);
	hudMenu->addChild(pauseButton);

	//按键包围盒
	Rect rect_but_left = but_left->getBoundingBox();
	Rect rect_but_right = but_right->getBoundingBox();
	Rect rect_but_A = but_A->getBoundingBox();
	Rect rect_but_B = but_B->getBoundingBox();

	//申请键盘监听
	EventListenerKeyboard* event = EventListenerKeyboard::create();
	event->onKeyPressed = [=](EventKeyboard::KeyCode code, Event* event) {
		if (code == EventKeyboard::KeyCode::KEY_K)
		{
			hero->jump();
		}
		else if (code == EventKeyboard::KeyCode::KEY_A)
		{
			hero->moveLeft();
		}
		else if (code == EventKeyboard::KeyCode::KEY_D)
		{
			hero->moveRight();
		}
		else if (code == EventKeyboard::KeyCode::KEY_J)
		{
			hero->fire();
		}
	};
	event->onKeyReleased = [=](EventKeyboard::KeyCode code, Event* event) {
		if (code == EventKeyboard::KeyCode::KEY_A && hero->moveState == 1)
		{
			hero->moveStop();
		}
		else if (code == EventKeyboard::KeyCode::KEY_D && hero->moveState == 2)
		{
			hero->moveStop();
		}
	};

	//申请触摸监听
	EventListenerTouchAllAtOnce* touchEvent = EventListenerTouchAllAtOnce::create();

	touchEvent->onTouchesBegan = [=](const std::vector<Touch*>& touches, Event* event) {
		for (auto &item : touches)       //遍历容器中的各个成员
		{
			auto touch = item;
			auto location = touch->getLocation();
			//LEFT
			if (rect_but_left.containsPoint(location))
			{
				hero->moveLeft();
			}
			//RIGHT
			else if (rect_but_right.containsPoint(location))
			{
				hero->moveRight();
			}
			//A
			else if (rect_but_A.containsPoint(location))
			{
				hero->fire();
			}
			//B
			else if (rect_but_B.containsPoint(location))
			{
				hero->jump();
			}
		}
	};
	//触摸时
	touchEvent->onTouchesMoved = [=](const std::vector<Touch*>& touches, Event* event) {
		bool left = false;
		bool right = false;
		for (auto &item : touches)       //遍历容器中的各个成员
		{
			auto touch = item;
			auto location = touch->getLocation();

			if (rect_but_left.containsPoint(location))
			{
				left = true;
				hero->moveLeft();
			}
			else if (rect_but_right.containsPoint(location))
			{
				right = true;
				hero->moveRight();
			}
		}
		setLeft(left);
		setRight(right);
		if (!left && !right)
		{
			hero->moveStop();
		}
	};
	//触摸抬起
	touchEvent->onTouchesEnded = [=](const std::vector<Touch*>& touches, Event* event) {
		bool left = isLeft();
		bool right = isRight();
		for (auto &item : touches)       //遍历容器中的各个成员
		{
			auto touch = item;
			auto location = touch->getLocation();

			if (rect_but_left.containsPoint(location))
			{
				left = false;
			}
			else if (rect_but_right.containsPoint(location))
			{
				right = false;
			}
		}
		setLeft(left);
		setRight(right);
		if (!left && !right)
		{
			hero->moveStop();
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(event, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchEvent, this);
	scheduleUpdate();
	return true;
}

void GameScene::setLeft(bool left)
{
	_left = left;
}

bool GameScene::isLeft()
{
	return _left;
}

void GameScene::setRight(bool right)
{
	_right = right;
}

bool GameScene::isRight()
{
	return _right;
}

void GameScene::update(float time) {
	if (!pause)
		GameManager::getInstance()->step(time);
}

void GameScene::pauseButton(Ref* ref) {
	pause = true;
	settingLayer->setVisible(true);
}
void GameScene::backButton(Ref* ref) {
	settingLayer->setVisible(false);
}
void GameScene::homeButton(Ref* ref) {
	
	Scene* scene = TransitionCrossFade::create(0.3f, HelloWorld::createScene());
	Director::getInstance()->pushScene(scene);
}
void GameScene::breakButton(Ref* ref) {
	hero->dead();
}