#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
class CardSprite;
class SimpleRecognizer;
class HelloWorld : public cocos2d::Layer
{
public:
	cocos2d::Label* cardNumberTTF;
	int score;
	cocos2d::LayerColor* successLayer;
	SimpleRecognizer* recognizer;
	CardSprite *cardArr[4][4];
    static cocos2d::Scene* createScene();
	~HelloWorld();
    virtual bool init();
	void doLeft();
	void doRight();
	void doUp();
	void doDown();
	void doCheck();
	bool isWin();
	void setScore();
	//void doCheck();
	void onPause(Ref* pSender);
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void createCardNumber();
	void createCardSprite(cocos2d::Size size);
	void removeSuccessLayer();
    CREATE_FUNC(HelloWorld);
};

#endif
