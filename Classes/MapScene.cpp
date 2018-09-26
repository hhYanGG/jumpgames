#include "MapScene.h"
#include "GameManager.h"
#include "Hero.h"
#include "Brick.h"
#include "Wall.h"
#include "Door.h"
#include "StaticData.h"
#include "Monster.h"
#include "Coin.h"
#include "Spikes.h"
USING_NS_CC;

MapScene* MapScene::_mapScene = nullptr;

MapScene* MapScene::getInstance()
{
	if (_mapScene == nullptr)
	{
		_mapScene = new MapScene();
		CC_SAFE_RETAIN(_mapScene);
	}
	return _mapScene;
}
void MapScene::initMap(char* levelName) {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	GameManager* gameManager = GameManager::getInstance();
	//读取Tiled地图资源
	TMXTiledMap* tiledMap = TMXTiledMap::create(levelName);
	//tiledMap->setAnchorPoint(Vec2(0.5, 0.5));
	gameManager->gameLayer->addChild(tiledMap, -1);

	TMXObjectGroup* brickLayer = tiledMap->getObjectGroup("BrickLayer");
	ValueVector bricks = brickLayer->getObjects();
	for (int i = 0; i < bricks.size(); i++)
	{
		ValueMap brick = bricks.at(i).asValueMap();
		float w = brick.at("width").asFloat();
		float h = brick.at("height").asFloat();
		float x = brick.at("x").asFloat() + w / 2.0f;
		float y = brick.at("y").asFloat() + h / 2.0f;

		if (brick.at("name").asString() == "Brick")//台阶
		{
			Brick* b = Brick::create(x, y, w, h);
			gameManager->gameLayer->addChild(b);
		}
		else if (brick.at("name").asString() == "Wall")//墙
		{
			Wall* wa = Wall::create(x, y, w, h);
			gameManager->gameLayer->addChild(wa);
		}
		
	}

	TMXObjectGroup* articleLayer = tiledMap->getObjectGroup("ArticleLayer");
	ValueVector articles = articleLayer->getObjects();
	for (int i = 0; i < articles.size(); i++)
	{
		ValueMap article = articles.at(i).asValueMap();
		
		//Door 门
		if (article.at("name").asString() == "Door")
		{
			float w = SD_FLOAT("door_float_width");
			float h = SD_FLOAT("door_float_height");
			float x = article.at("x").asFloat() + w / 2.0f;
			float y = article.at("y").asFloat() + h / 2.0f;

			Door* a = Door::create(x, y, w, h);
			a->setScale(0.5, 0.5);
			gameManager->thingLayer->addChild(a);
		}
	}

	TMXObjectGroup* heroLayer = tiledMap->getObjectGroup("HeroLayer");
	ValueVector heros = heroLayer->getObjects();
	for (int i = 0; i < heros.size(); i++) {
		ValueMap hero = heros.at(i).asValueMap();
		
		if (hero.at("name").asString() == "Hero")
		{
			float w = 10;
			float h = 10;
			float x = hero.at("x").asFloat() + w / 2.0f;
			float y = hero.at("y").asFloat() + h / 2.0f;

			Hero* e = Hero::create(x, y, w, h);
			e->setScale(0.3,0.3);
			gameManager->heroLayer->addChild(e);
			GameManager::getInstance()->hero = e;
		}
	}

	TMXObjectGroup* fireLayer = tiledMap->getObjectGroup("FireLayer");
	ValueVector fires = fireLayer->getObjects();
	for (int i = 0; i < fires.size(); i++) {
		ValueMap fire = fires.at(i).asValueMap();

	
			float w = fire.at("width").asFloat();
			float h = fire.at("height").asFloat();
			float x = fire.at("x").asFloat() + w / 2.0f;
			float y = fire.at("y").asFloat() + h / 2.0f;

			Spikes* e = Spikes::create(x, y, w, h);
			e->setScale(0.3, 0.3);
			gameManager->thingLayer->addChild(e);

		
	}



	TMXObjectGroup* monsterLayer = tiledMap->getObjectGroup("MonsterLayer");
	ValueVector monsters = monsterLayer->getObjects();
	for (int i = 0; i < monsters.size(); i++)
	{
		ValueMap monster = monsters.at(i).asValueMap();

		if (monster.at("name").asString() == "Monster")
		{
			float w = 16;
			float h = 8;
			float x = monster.at("x").asFloat() + w / 2.0f;
			float y = monster.at("y").asFloat() + h / 2.0f;

			Monster* s = Monster::create(x, y, w, h);
			s->setScale(0.5, 0.5);
			gameManager->monsterLayer->addChild(s);
		}
	}

	TMXObjectGroup* coinLayer = tiledMap->getObjectGroup("CoinLayer");
	ValueVector coins = coinLayer->getObjects();
	for (int i = 0; i < coins.size(); i++)
	{
		ValueMap coin = coins.at(i).asValueMap();
		float w = coin.at("width").asFloat();
		float h = coin.at("height").asFloat();
		float x = coin.at("x").asFloat() + w / 2.0f;
		float y = coin.at("y").asFloat() + h / 2.0f;

		Coin* c = Coin::create(x, y, w, h);
		c->setScale(0.4, 0.4);
		gameManager->thingLayer->addChild(c);
	}
}

void MapScene::initMap(int level)
{
	char levle_s[128];
	sprintf(levle_s, "level_%d.tmx", level);
	initMap(levle_s);
}

MapScene::~MapScene() {
	CC_SAFE_RELEASE_NULL(_mapScene);
}