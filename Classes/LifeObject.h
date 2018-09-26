#ifndef _LIFE_BOJECT_H_
#define _LIFE_BOJECT_H_
#include "cocos2d.h"
#include "PhysicsSprite.h"
USING_NS_CC;
class LifeObject : public PhysicsSprite {
protected:
	bool die;
	bool over;
	//int dir;
public:
	

	/*virtual void setDir(int var) {
		dir = var;
	}

	virtual int getDir() {
		return dir;
	}*/

	virtual bool init(float x, float y, float width, float height) override;
	CREATE_FUNC_4(LifeObject, float, float, float, float);

	virtual bool init(float x, float y, b2Vec2* points, int count) override;
	CREATE_FUNC_4(LifeObject, float, float, b2Vec2*, int);

	//Ӣ����������
	CC_SYNTHESIZE(int, dir, Dir);
	//Ѫ��
	CC_SYNTHESIZE(int, hp, Hp);	
	//������
	CC_SYNTHESIZE(int, atk, Atk);	

	/*��������״̬*/
	virtual void setDie(bool die);
	/*�жϵ�ǰ�������Ƿ�����*/
	virtual bool isDie() const;
	/*���ý���״̬*/
	virtual void setOver(bool over);
	/*���������Ƿ����*/
	virtual bool isOver() const;

	/*��֡�ص�����*/
	virtual void update(float ft);
	
	/* �Զ����� ����ʱ�Ļص����� �����������д�ú������� �ú�������hp����0ʱ�Զ�����һ��*/
	virtual void dead();

	virtual void ended();
};

#endif