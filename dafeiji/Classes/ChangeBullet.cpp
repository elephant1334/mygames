#include"cocos2d.h"
#include"ChangeBullet.h"
USING_NS_CC;
ChangeBullet::ChangeBullet(){}

ChangeBullet::~ChangeBullet(){}

ChangeBullet* ChangeBullet::create(){
	ChangeBullet* pRet = new ChangeBullet();
	if (pRet&&pRet->init()){
		pRet->autorelease();
	}
	else{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

void ChangeBullet::initWithType(proType type){
	bulletType = type;
	CCString* string = CCString::createWithFormat("ufo%i.png", type);
	prop = CCSprite::createWithSpriteFrameName(string->getCString());
	prop->setPosition(ccp((rand() % 240 + 23)*2, 632*2));
}

void ChangeBullet::propAnimation(){
	CCMoveTo *ac1 = CCMoveTo::create(1, ccp(prop->getPosition().x, 250 * 2));
	CCMoveTo *ac2 = CCMoveTo::create(0.4, ccp(prop->getPosition().x, 252 * 2));
	CCMoveTo *ac3 = CCMoveTo::create(1, ccp(prop->getPosition().x, 500));
	CCMoveTo *ac4 = CCMoveTo::create(2, ccp(prop->getPosition().x, -55 * 2));

	prop->runAction(CCSequence::create(ac1, ac2, ac3, ac4, NULL));
}