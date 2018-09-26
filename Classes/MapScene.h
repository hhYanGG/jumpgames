#ifndef _MAP_SCENE_H_
#define _MAP_SCENE_H_

#include "cocos2d.h"

class MapScene : public cocos2d::Ref
{

protected:
	static MapScene* _mapScene;
public:
	static MapScene* getInstance();
	~MapScene();
	void initMap(char* leveName);
	void initMap(int level);
};

#endif