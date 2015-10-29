#include"EnemyPlane.h"

USING_NS_CC;
EnemyPlane::EnemyPlane(){

}

EnemyPlane::~EnemyPlane(){}

EnemyPlane* EnemyPlane::createWithSpriteFrameName(const char* spriteFrameName){
	EnemyPlane* pPlane = new EnemyPlane;
	if (pPlane&&pPlane->initWithSpriteFrameName(spriteFrameName)){
		pPlane->autorelease();
		return pPlane;
	}
	CC_SAFE_RELEASE(pPlane);
	return NULL;
}
