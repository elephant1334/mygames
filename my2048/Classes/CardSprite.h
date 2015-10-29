#ifndef _CARDSPRITE_H_
#define _CARDSPRITE_H_

#include"cocos2d.h"

class CardSprite:public cocos2d::Sprite{
public:
	static CardSprite* createCardSprite(int number, int wight, int height, cocos2d::Point position);
	void initCard(int number, int width, int height, float CardSpriteX, float CardSpriteY);
	void setNumber(int num);
	int  getNumber();
	CREATE_FUNC(CardSprite);
private:
	int number;
	cocos2d::LayerColor* colorBackGround;
	cocos2d::Label* labelCardNumber;
};

#endif