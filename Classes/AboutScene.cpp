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

	//��Ϸ��Ϣ
	TTFConfig ttfConfig("fonts/font.ttf", 16);
	auto number = Label::createWithTTF(ttfConfig, "��Ϸ����\n��������puppy�����ͼ�յ㼴�ɻ��ʤ��\nͨ��������ť����>��<�������������ƶ���\nͨ����ťB����������Ծ��\n��������Ծ���Σ�ͨ����ťA�������� \n ʹ�ü��� A D ���Ʒ��� J �����ӵ� K ��Ծ");
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