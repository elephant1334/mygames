#ifndef _POPLAYER_H_
#define _POPLAYER_H_

#include"cocos2d.h"

class PopLayer :public cocos2d::LayerColor{
public:
	static PopLayer* create(const cocos2d::Color4B& color);
	bool initWithColor(const cocos2d::Color4B& color);
	//void onContinue(Ref* pSender);

};

#endif