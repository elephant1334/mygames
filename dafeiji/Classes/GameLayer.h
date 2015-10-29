#ifndef _GAMELAYER_H_
#define _GAMELAYER_H_

#include "cocos2d.h"
class EnemyPlane;
class ChangeBullet;
class GameLayer :public cocos2d::CCLayer{
public:
	float bulletSpeed;
	
	virtual bool init();

	static cocos2d::CCScene* createScene();

	//virtual void ccTouchesMoved(cocos2d::CCSet* pTouched, cocos2d::CCEvent* pEvent);
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	cocos2d::CCPoint boundLayerPos(cocos2d::CCPoint newPos);
	CREATE_FUNC(GameLayer);

private:
	void initUI();
	void initData();
	void scrollBg();
	void update(float t);
	void makeBullet();
	//void resetBullet();
	void firingBullets();
	void addEnemyPlane();
	void addBomb();
	void collisionDetection();
	void enemyPlaneBlowupAnimation(EnemyPlane* enemyPlane);
	void hitAnimationForPlane(EnemyPlane* enemyPlane);
	void playerBlowupAnimation();
	void playBombAnimation(cocos2d::Sprite* bomb);
	void gameOver();
	void blowupEnd(cocos2d::CCObject* object);
	void onPause(Ref* pSender);
	EnemyPlane* makeSmallPlane();
	EnemyPlane* makeMediumPlane();
	EnemyPlane* makeBigPlane();
	void moveEnemyPlane();
	cocos2d::CCSprite* bgSprite1;
	cocos2d::CCSprite* bgSprite2;

	int bgHeight;
	int bgWidht;
	int fireInterval;
	int smallPlaneTime;
	int mediumPlaneTime;
	int bigPlaneTime;
	//空降物品计时
	int propTime;
	bool isVisible;
	bool isBigBullet;
	bool isChangeBullet;

	//子弹威力
	int bulletPower;
	//子弹持续时间
	int bulletlastTime;
	void bulletLastTime();
	void addBulletTypeTip();
	//记录得分
	int scoreInt;
	cocos2d::CCSize wSize;
	cocos2d::Array* planeArray;
	cocos2d::Array* bombArray;
	cocos2d::Vector<cocos2d::Sprite* > bulletVec;
	//cocos2d::CCSprite* bullet;

	//cocos2d::CCSprite* bullet1;
	//cocos2d::CCSprite* bullet2;

	cocos2d::CCSprite* playSprite;
	cocos2d::LabelTTF* scoreLabel;

	ChangeBullet* prop;
};

#endif