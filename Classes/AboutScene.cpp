#include "AboutScene.h"
#pragma execution_character_set("utf-8");
USING_NS_CC;
Scene* AboutScene::createScene()
{
	Scene* scene = Scene::create();
	Layer* layer = AboutScene::create();

	scene->addChild(layer);
	return scene;
}

bool AboutScene::init() {
	if (!Layer::init())
	{
		return false;
	}
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite* down_bk = Sprite::create("UI/FINISH/background.png");
	//down_bk->setAnchorPoint(Vec2(0, 0));
	down_bk->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(down_bk);

	//游戏信息
	TTFConfig ttfConfig("fonts/font.ttf", 16);
	auto number = Label::createWithTTF(ttfConfig, "游戏规则：\n操作主角puppy到达地图终点即可获得胜利\n通过操作按钮——>、<——控制主角移动，\n通过按钮B控制主角跳跃，\n可连续跳跃两次，通过按钮A发射武器 \n 使用键盘 A D 控制方向 J 发射子弹 K 跳跃");
	number->setTextColor(Color4B(0,0,0,200));
	number->setPosition(visibleSize.width * 0.55,visibleSize.height/2);
	this->addChild(number,0);

	auto event = EventListenerTouchOneByOne::create();
	event->onTouchBegan = [](Touch* t, Event* e) {
		Director::getInstance()->popScene();
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(event, this);
}