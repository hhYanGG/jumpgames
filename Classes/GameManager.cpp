#include "GameManager.h"
#include "Hero.h"
#include "Define.h"
#include "PhysicsSprite.h"
#include "StaticData.h"
USING_NS_CC;

GameManager* GameManager::gameManager = nullptr;

GameManager* GameManager::getInstance()
{
	if (!gameManager)
	{
		gameManager = new GameManager();
		gameManager->retain();	//����+1
	}
	return gameManager;
}

GameManager::GameManager()
{
	hero = nullptr;
	////��ʼ����Դ
	initRes();
	//��ʼ����������
	initPhysicsWorld(GRAVITY);
	
}

GameManager::~GameManager()
{
	CC_SAFE_RELEASE(gameManager);
	CC_SAFE_DELETE(world);
}

void GameManager::initPhysicsWorld(float gravity) {
	world = new b2World(b2Vec2(0, -gravity));
	world->SetContactListener(this);
	//��Ļλ��
	sceneX = Director::getInstance()->getVisibleSize().width / 2;
	sceneY = Director::getInstance()->getVisibleSize().height / 2;
}

b2World* GameManager::getWorld()
{
	return world;
}

void GameManager::step(float time) {
	//--Ӣ���ϴ�λ��
	Vec2 heroLastPostion = hero->getPosition();

	world->Step(time, 8, 3);
	//���¾���λ�á��Ƕ�
	for (b2Body* body = world->GetBodyList(); body; body = body->GetNext())
	{
		Sprite* sprite = (Sprite*)body->GetUserData();
		if (sprite == NULL)
			continue;
		sprite->setPosition(body->GetPosition().x* PTM_RATIO, body->GetPosition().y*PTM_RATIO);
		sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(body->GetAngle()));	//���ýǶ�
	}

	//�ͷ����ٻ���ջ�е�������
	for (auto it = _deleteSprites.begin(); it != _deleteSprites.end(); )
	{
		(*it)->removePhysicsSprite();
		it = _deleteSprites.erase(it);
	}

	//--Ӣ�۵�ǰλ��
	Vec2 heroNowPostion = hero->getPosition();
	sceneX = sceneX + heroLastPostion.x - heroNowPostion.x;
	sceneY = sceneY + heroLastPostion.y - heroNowPostion.y;
	GameManager::getInstance()->gameLayer->setPosition(sceneX, sceneY);
	//CCLog("%f", sceneX);

}
Animation* GameManager::getAnimation(const char* src, float delay, unsigned int loops)
{
	Vector<SpriteFrame*> frames;

	char _src[30];
	for (int i = 0; i<10000; i++)
	{
		sprintf(_src, "%s%04d", src, i);
		SpriteFrame* sf = SpriteFrameCache::getInstance()->getSpriteFrameByName(_src);
		if (sf == nullptr)
		{
			break;
		}
		frames.pushBack(sf);
	}
	return Animation::createWithSpriteFrames(frames, delay, loops);
}

cocos2d::Animate* GameManager::getAnimate(const char* src, float delay /*= 0.0f*/, unsigned int loops /*= 1U*/)
{
	Animation* animation = getAnimation(src, delay, loops);
	return Animate::create(animation);
}


void GameManager::pushDeleteSprite(PhysicsSprite* sprite) {
	_deleteSprites.pushBack(sprite);
}

void GameManager::initRes()
{
	std::string path = FileUtils::getInstance()->fullPathForFilename("load.xml");
	ValueMap vm = FileUtils::getInstance()->getValueMapFromFile(path);
	for (int i = 0; i < vm.size(); i++)
	{
		char buf[12];
		sprintf(buf, "%d", i + 1);
		std::string s = vm.at(buf).asString();
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(s);
	}
	vm.clear();
}


void GameManager::destroyInstance()
{
	CC_SAFE_DELETE(gameManager);
}

void GameManager::BeginContact(b2Contact* contact)
{
	PhysicsSprite* a = (PhysicsSprite*)contact->GetFixtureA()->GetBody()->GetUserData();
	PhysicsSprite* b = (PhysicsSprite*)contact->GetFixtureB()->GetBody()->GetUserData();

	a->BeginContact(b, contact);
	b->BeginContact(a, contact);
}

void GameManager::EndContact(b2Contact* contact)
{
	PhysicsSprite* a = (PhysicsSprite*)contact->GetFixtureA()->GetBody()->GetUserData();
	PhysicsSprite* b = (PhysicsSprite*)contact->GetFixtureB()->GetBody()->GetUserData();

	a->EndContact(b, contact);
	b->EndContact(a, contact);
}

void GameManager::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	PhysicsSprite* a = (PhysicsSprite*)contact->GetFixtureA()->GetBody()->GetUserData();
	PhysicsSprite* b = (PhysicsSprite*)contact->GetFixtureB()->GetBody()->GetUserData();

	a->PreSolve(b, contact, oldManifold);
	b->PreSolve(a, contact, oldManifold);
}

void GameManager::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
	PhysicsSprite* a = (PhysicsSprite*)contact->GetFixtureA()->GetBody()->GetUserData();
	PhysicsSprite* b = (PhysicsSprite*)contact->GetFixtureB()->GetBody()->GetUserData();

	a->PostSolve(b, contact, impulse);
	b->PostSolve(a, contact, impulse);
}
void GameManager::setLevel(int level)
{
	GameManager::level = level;
}

int GameManager::getLevel()
{
	return level;
}
