#ifndef _CHANGEBULLET_H_
#define _CHANGEBULLET_H_

typedef enum{
	propsTypeBomb = 2,
	propsTypeBullet = 1
}proType;

#include"cocos2d.h"

class ChangeBullet :public cocos2d::CCNode{
public:
	cocos2d::CCSprite* prop;
	proType bulletType;
	void initWithType(proType type);
	static ChangeBullet* create();
	void propAnimation();
	CC_SYNTHESIZE_RETAIN(cocos2d::CCSprite*, _prop, Prop);
	ChangeBullet();
	~ChangeBullet();
};
#endif