#ifndef _GAMEOVERLAYER_H_
#define _GAMEOVERLAYER_H_

#include"cocos2d.h"

USING_NS_CC;

class GameOverLayer :public LayerColor{
public:
	static GameOverLayer* create(const Color4B& color);
	virtual bool initWithColor(const Color4B& color);

};

#endif