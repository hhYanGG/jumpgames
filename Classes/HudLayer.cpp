#include "HudLayer.h"
#include "GameManager.h"
#include "Hero.h"
#include "StaticData.h"


USING_NS_CC;

bool HudLayer::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (!Layer::init())
		return false;
	//血量HUD	
	int hp = 3;
	for (int i = 0; i < hp; i++)
	{
		Sprite* s_hp = Sprite::create("HUD/hud_heartFull.png");
		char name[20];
		sprintf(name, "HP_%d", i);
		s_hp->setName(name);
		s_hp->setPosition(s_hp->getContentSize().width * (i * 4.0 / 3 + 1), visibleSize.height - s_hp->getContentSize().height);
		this->addChild(s_hp);
	}
	//////////////////金币HUD///////////////////
	//金币图标
	Sprite* c_hp = Sprite::create("HUD/hud_coins.png");
	c_hp->setPosition(c_hp->getContentSize().width * 1.1, visibleSize.height - c_hp->getContentSize().height * 2.5);
	this->addChild(c_hp);
	//数字
	plabelAtlas = LabelAtlas::create("0123456789", "HUD/hud_num.png", 15, 40, '0');
	//plabelAtlas->setAnchorPoint(Vec2(0, 0.5));
	plabelAtlas->setPosition(c_hp->getContentSize().width * 1.8, visibleSize.height - c_hp->getContentSize().height * 3.9);
	this->addChild(plabelAtlas);

	return true;
}

void HudLayer::replaceHpHud()
{
	Hero* hero = GameManager::getInstance()->hero;
	if (hero == nullptr)
	{
		return;
	}
	int hp = hero->getHp();
	//更新HUD
	for (int i = 0; i <3; i++)
	{
		char name[10];
		sprintf(name, "HP_%d", i);
		Sprite* s_hp = (Sprite*)GameManager::getInstance()->hudLayer->getChildByName(name);
		if (s_hp != nullptr)
		{
			s_hp->setTexture("HUD/hud_heartFull.png");
		}
	}
	for (int i = 3; i >= hp; i--)
	{
		char name[10];
		sprintf(name, "HP_%d", i);
		Sprite* s_hp = (Sprite*)GameManager::getInstance()->hudLayer->getChildByName(name);
		if (s_hp != nullptr)
		{
			s_hp->setTexture("HUD/hud_heartEmpty.png");
		}
	}
}

void HudLayer::replaceCoinHud()
{
	Hero* hero = GameManager::getInstance()->hero;
	if (hero == nullptr)
	{
		plabelAtlas->setString("0");
		return;
	}
	int coin = hero->getCoin();
	char c_coin[6] = "0";
	sprintf(c_coin, "%d", coin);
	//设置显示文字
	plabelAtlas->setString(c_coin);
}

