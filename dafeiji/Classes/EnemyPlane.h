#ifndef _ENEMYPLANE_H_
#define _ENEMYPLANE_H_

#include"cocos2d.h"
class EnemyPlane :public cocos2d::Sprite{
public:
	int planeType;//���ַɻ�����
	int hp;//�ɻ�Ѫ��
	int speed;
	EnemyPlane();
	~EnemyPlane();
	static EnemyPlane* createWithSpriteFrameName(const char* spriteFrameName);
};

#endif