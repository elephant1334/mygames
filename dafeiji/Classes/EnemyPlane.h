#ifndef _ENEMYPLANE_H_
#define _ENEMYPLANE_H_

#include"cocos2d.h"
class EnemyPlane :public cocos2d::Sprite{
public:
	int planeType;//三种飞机类型
	int hp;//飞机血量
	int speed;
	EnemyPlane();
	~EnemyPlane();
	static EnemyPlane* createWithSpriteFrameName(const char* spriteFrameName);
};

#endif