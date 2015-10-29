#include"GameLayer.h"
#include"EnemyPlane.h"
#include"PopLayer.h"
#include"ChangeBullet.h"
#include"HelloWorldScene.h"
USING_NS_CC;

bool GameLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}




	initData();

	initUI();

	this->setTouchEnabled(true);
	//系统的刷新  
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
	//_eventDispacther->addEventListenerWithSceneGraphPriority(touchListener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	scheduleUpdate();


	return true;

}

void GameLayer::initData()
{

	auto size = Director::getInstance()->getVisibleSize();
	bgHeight = size.height;
	bgWidht = size.width;
	wSize = size;
	smallPlaneTime = 0;
	mediumPlaneTime = 0;
	bigPlaneTime = 0;
	scoreInt = 0;
	propTime = 0;
	bulletPower = 1;
	fireInterval = 30;
	bulletlastTime = 1200;
	isBigBullet = false;
	isChangeBullet = false;
	planeArray = new Array;
	bombArray = new Array;
	bombArray->init();
	planeArray->init();
	//planeArray->autorelease();
	this->setTouchEnabled(true);

}

void GameLayer::initUI(){
	bgSprite1 = CCSprite::createWithSpriteFrameName("background.png");
	bgSprite1->setAnchorPoint(ccp(0, 0));
	bgSprite1->setPosition(ccp(0, 0));
	float winw = wSize.width; //获取屏幕宽度
	float winh = wSize.height;//获取屏幕高度
	float spx = bgSprite1->getTextureRect().getMaxX();
	float spy = bgSprite1->getTextureRect().getMaxY();
	bgSprite1->setScaleX(winw/spx); //设置精灵宽度缩放比例
	bgSprite1->setScaleY(winh/spx);
	addChild(bgSprite1, 0);


	bgSprite2 = CCSprite::createWithSpriteFrameName("background.png");
	bgSprite2->setAnchorPoint(ccp(0, 0));
	bgSprite2->setPosition(ccp(0, bgHeight-1));
	bgSprite2->setScaleX(winw/spx); //设置精灵宽度缩放比例
	bgSprite2->setScaleY(winh/spx);
	addChild(bgSprite2, 0);

	MenuItemFont::setFontName("MarkerFelt-Thin");
	MenuItemFont::setFontSize(40);
	auto menuItemPause = MenuItemFont::create("PAUSE", CC_CALLBACK_1(GameLayer::onPause, this));

	auto menu = Menu::create();
	menu->setPosition(Point(wSize.width - 100, wSize.height-60));
	menu->addChild(menuItemPause);
	this->addChild(menu,2);

	playSprite = CCSprite::createWithSpriteFrameName("hero1.png");
	playSprite->setPosition(ccp(300, 200));
	/*spriteFrameCache->getSpriteFrameByName("background.png");

	auto bgSprite = Sprite::createWithSpriteFrame(bgspriteFrame);*/

	addChild(playSprite, 3);

	Vector<CCSpriteFrame*> array;

	for (int i = 1; i<=2; i++)
	{

		CCString *string = CCString::createWithFormat("hero%d.png", i);
		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(string->getCString());

		array.pushBack(frame);

	}

	CCAnimation *animation = CCAnimation::createWithSpriteFrames(array, 0.1);
	CCAnimate *animate = CCAnimate::create(animation);

	CCRepeatForever *ac1 = CCRepeatForever::create(animate);

	playSprite->runAction(ac1);

	makeBullet();

	scoreLabel = LabelTTF::create("0", "MarkerFelt-Thin", 20);
	scoreLabel->setPosition(Point(50, wSize.height - 50));
	this->addChild(scoreLabel);
}

void GameLayer::onPause(Ref* pSender){
	PopLayer *poplayer = PopLayer::create(Color4B(0, 0, 0, 180));
	getParent()->addChild(poplayer);
	Director::getInstance()->pause();
}

void GameLayer::scrollBg()
{

	bgHeight--;
	if (bgHeight <= 0)
	{
		bgHeight = wSize.height;
	}
	bgSprite1->setPosition(ccp(bgSprite1->getPosition().x, bgHeight - wSize.height));
	bgSprite2->setPosition(ccp(bgSprite2->getPosition().x, bgHeight - 1));
}

void GameLayer::update(float t){
	scrollBg();
	firingBullets();
	addEnemyPlane();
	moveEnemyPlane();
	collisionDetection();
	addBulletTypeTip();
	bulletLastTime();
}

void GameLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event){
	CCPoint curLocation = Director::getInstance()->convertToGL(
		touch->getLocationInView());
	CCPoint oldLocation = touch->getPreviousLocation();
	CCPoint translation = ccpSub(curLocation, oldLocation);
	playSprite->setPosition(this->boundLayerPos(translation));
}

bool GameLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event){
	return true;
}

void GameLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event){

}

CCPoint GameLayer::boundLayerPos(CCPoint newPos)
{
	CCPoint point = newPos;
	point.x = playSprite->getPosition().x + newPos.x;
	point.y = playSprite->getPosition().y + newPos.y;

	if (point.x >= wSize.width) {
		point.x = wSize.width;
	}
	else if (point.x <= 0) {
		point.x = 0;
	}

	if (point.y >= wSize.height - 50 * 2) {
		point.y = wSize.height - 50 * 2;
	}
	else if (point.y <= 43 * 2) {
		point.y = 43 * 2;
	}
	return point;
}

void GameLayer::makeBullet(){
	CCSprite* bullet;
	if(!isBigBullet)
    bullet = CCSprite::createWithSpriteFrameName("bullet1.png");
	else
    bullet = CCSprite::createWithSpriteFrameName("bullet2.png");
	bullet->setPosition(ccp(playSprite->getPosition().x, playSprite->getPosition().y + 50));
	addChild(bullet, 1);
	bulletVec.pushBack(bullet);
	//bulletSpeed = (wSize.height - (playSprite->getPosition().y + 50)) / 20;
	bulletSpeed = 8;
}
//void GameLayer::resetBullet(){
//	//bulletSpeed = (wSize.height - (playSprite->getPosition().y + 50)) / 15;
//	bulletSpeed = 5;
//	if (bulletSpeed<5)
//	{
//		bulletSpeed = 5;
//	}
//
//	bullet->setPosition(ccp(playSprite->getPosition().x, playSprite->getPosition().y + 50));
//}
void GameLayer::firingBullets(){
    
	for (int i = 0; i < bulletVec.size(); i++){
		bulletVec.at(i)->setPosition(ccp(bulletVec.at(i)->getPosition().x, bulletVec.at(i)->getPosition().y + bulletSpeed));
		if (bulletVec.at(i)->getPosition().y > wSize.height - 20){
			bulletVec.at(i)->removeFromParentAndCleanup(false);
			bulletVec.eraseObject(bulletVec.at(i));
		}
	}
	fireInterval -= 2;

	//if (bullet->getPosition().y > wSize.height - 20)
	if (fireInterval == 0)
    {
		/*this->resetBullet();
		bullet->setVisible(true);*/
		makeBullet();
		fireInterval = 30;
	}
}

void GameLayer::addEnemyPlane(){
	smallPlaneTime++;
	mediumPlaneTime++;
	bigPlaneTime++;
	//每60帧生成一架小飞机
	if (smallPlaneTime > 60){
		EnemyPlane* smallPlane = this->makeSmallPlane();
		this->addChild(smallPlane, 3);
		planeArray->addObject(smallPlane);
		smallPlaneTime = 0;
	}
	//每400帧生成一架中型飞机
	if (mediumPlaneTime > 400){
		EnemyPlane* mediumPlane = this->makeMediumPlane();
		this->addChild(mediumPlane, 3);
		planeArray->addObject(mediumPlane);
		mediumPlaneTime = 0;
	}
	//每700帧生成一架大型飞机
	if (bigPlaneTime > 700){
		EnemyPlane* bigPlane = this->makeBigPlane();
		this->addChild(bigPlane, 3);
		planeArray->addObject(bigPlane);
		
		bigPlaneTime = 0;
	}
}
EnemyPlane* GameLayer::makeSmallPlane(){
	EnemyPlane* smallPlane = EnemyPlane::createWithSpriteFrameName("enemy1.png");
	smallPlane->setPosition(ccp(rand() % ((int)(wSize.width*0.8)) + 17, wSize.height + 150));
	smallPlane->planeType = 1;
	smallPlane->hp = 1;
	smallPlane->speed = rand() % 4 + 2;
	return smallPlane;
}
EnemyPlane* GameLayer::makeMediumPlane(){
	EnemyPlane* mediumPlane = EnemyPlane::createWithSpriteFrameName("enemy2.png");
	mediumPlane->setPosition(ccp(rand() % ((int)(wSize.width*0.8)) + 23, wSize.height + 150));
	mediumPlane->planeType = 2;
	mediumPlane->hp = 15;
	mediumPlane->speed = rand() % 3 + 2;
	return mediumPlane;
}
EnemyPlane* GameLayer::makeBigPlane(){
	/*EnemyPlane* bigPlane = EnemyPlane::createWithSpriteFrameName("enemy3_n1.png");
	bigPlane->setPosition(ccp(rand() % 210 + 55, wSize.height + 150));
	bigPlane->planeType = 3;
	bigPlane->hp = 25;
	bigPlane->speed = rand() % 2 + 2;
	return bigPlane;*/
	Vector<CCSpriteFrame*> array;
	for (int i = 1; i <= 2; i++)
	{

		CCString *string = CCString::createWithFormat("enemy3_n%i.png", i);
		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(string->getCString());

		array.pushBack(frame);

	}

	CCAnimation *animation = CCAnimation::createWithSpriteFrames(array, 0.1);
	CCAnimate *animate = CCAnimate::create(animation);

	CCRepeatForever *ac1 = CCRepeatForever::create(animate);



	EnemyPlane *bigPlane = EnemyPlane::createWithSpriteFrameName("enemy3_n1.png");

	bigPlane->setPosition(ccp(rand() % ((int)(wSize.width*0.8)) + 55, wSize.height + 150));

	bigPlane->planeType = 3;
	bigPlane->hp = 25;
	bigPlane->speed = rand() % 2 + 2;

	bigPlane->runAction(ac1);


	array.clear();


	return bigPlane;
}
void GameLayer::moveEnemyPlane(){
	for (int i = 0; i < planeArray->count(); i++){
		EnemyPlane* tmpPlane = (EnemyPlane*)planeArray->objectAtIndex(i);
		tmpPlane->setPosition(ccp(tmpPlane->getPosition().x,
			tmpPlane->getPosition().y - tmpPlane->speed));
		if (tmpPlane->getPosition().y < (-75 * 2)){
			planeArray->removeObject(tmpPlane);
			tmpPlane->removeFromParentAndCleanup(false);
		}
	}
}

void GameLayer::addBomb(){
	for (int i = 0; i < 6; i++){
		Sprite* bomb = Sprite::createWithSpriteFrameName("BM01.png");
		bomb->setPosition(rand() % ((int)wSize.width), rand() % ((int)wSize.height));
		//this->addChild(bomb1);
		bombArray->addObject(bomb);
	}
}

void GameLayer::collisionDetection(){
	//Sprite* bullet = bulletVec.back();
	for (int i = 0; i < bulletVec.size(); i++){
		Sprite* bullet = bulletVec.at(i);
		CCRect bulletRect = bullet->boundingBox();
		for (int i = 0; i < planeArray->count(); i++){
			EnemyPlane* enemyPlane = (EnemyPlane*)planeArray->objectAtIndex(i);
			if (bulletRect.intersectsRect(enemyPlane->boundingBox())&&bullet->isVisible()){
				//this->resetBullet();
				bullet->setVisible(false);
				//bullet->removeFromParentAndCleanup(false);
				//bulletVec.eraseObject(bullet, false);

				enemyPlane->hp -= bulletPower;
				if (enemyPlane->hp <= 0){
					this->enemyPlaneBlowupAnimation(enemyPlane);
					planeArray->removeObject(enemyPlane);
				}
				else{
					this->hitAnimationForPlane(enemyPlane);
				}
			}
		}
	}
	//飞机跟空降物  
	if (isVisible == true)
	{
		CCRect playRect = playSprite->boundingBox();
		CCRect propRect = prop->prop->boundingBox();

		if (playRect.intersectsRect(propRect))
		{
			prop->prop->stopAllActions();
			prop->prop->removeFromParentAndCleanup(true);

			isVisible = false;

			//换子弹  
			if (prop->bulletType == propsTypeBullet)
			{

				isBigBullet = true;
				isChangeBullet = true;

			}
			//炸弹  
			else if (prop->bulletType == propsTypeBomb)
			{
				this->addBomb();
				for (int i = 0; i < bombArray->count(); i++){
					Sprite *bomb = (Sprite *)bombArray->objectAtIndex(i);
					//爆炸动画  
					this->addChild(bomb);
					this->playBombAnimation(bomb);
				}
				bombArray->removeAllObjects();
				for (int i = 0; i < planeArray->count(); i++)
				{
					EnemyPlane *enemyPlane = (EnemyPlane *)planeArray->objectAtIndex(i);
					//爆炸动画  
					this->enemyPlaneBlowupAnimation(enemyPlane);
				}
				planeArray->removeAllObjects();
			}
		}
	}

	CCRect playRec = playSprite->boundingBox();
	playRec.origin.x += 25 * 2;
	playRec.size.width -= 50 * 2;
	playRec.origin.y -= 10 * 2;
	playRec.size.height -= 10 * 2;

	for (int i = 0; i < planeArray->count(); i++)
	{

		EnemyPlane *enemyPlane = (EnemyPlane *)planeArray->objectAtIndex(i);


		if (playRec.intersectsRect(enemyPlane->boundingBox()))
		{


			this->playerBlowupAnimation();
			this->enemyPlaneBlowupAnimation(enemyPlane);
			planeArray->removeObject(enemyPlane);
			this->gameOver();


		}
	}
}

void GameLayer::playBombAnimation(cocos2d::Sprite* bomb){
	Vector<CCSpriteFrame*> array;
	for (int i = 1; i <= 9; i++){
		CCString* string = CCString::createWithFormat("BM0%i.png",i);
		CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()
			->spriteFrameByName(string->getCString());
		array.pushBack(frame);
	}
	CCAnimation* animation = CCAnimation::createWithSpriteFrames(array, 0.1);
	CCAnimate* animate = CCAnimate::create(animation);

	CCSequence* seq = CCSequence::create(animate, CCCallFuncN::create(CC_CALLBACK_1(GameLayer::blowupEnd, this)), NULL);
	bomb->runAction(seq);
	array.clear();
}

void GameLayer::enemyPlaneBlowupAnimation(EnemyPlane* enemyPlane){
	int animationNum = 0;
	if (enemyPlane->planeType == 1){
		animationNum = 4;
		scoreInt += 2000;
	}
	if (enemyPlane->planeType == 2){
		animationNum = 4;
		scoreInt += 10000;
	}
	if (enemyPlane->planeType == 3){
		animationNum = 6;
		scoreInt += 40000;
	}
	CCString* string = CCString::createWithFormat("%i", scoreInt);
	scoreLabel->setString(string->getCString());

	Vector<CCSpriteFrame*> array;
	for (int i = 1; i <= animationNum; i++){
		CCString* string = CCString::createWithFormat("enemy%i_down%i.png",enemyPlane->planeType ,i);
		CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()
			->spriteFrameByName(string->getCString());
		array.pushBack(frame);
	}
	CCAnimation* animation = CCAnimation::createWithSpriteFrames(array, 0.1);
	CCAnimate* animate = CCAnimate::create(animation);

	CCSequence* seq = CCSequence::create(animate, CCCallFuncN::create(CC_CALLBACK_1(GameLayer::blowupEnd,this)), NULL);
	enemyPlane->runAction(seq);
	array.clear();
}

//动画结束后处理
void GameLayer::blowupEnd(CCObject* object){
	EnemyPlane* enemyPlane = (EnemyPlane*)object;
	enemyPlane->removeFromParentAndCleanup(false);
}

//飞机被击打的动画  
void GameLayer::hitAnimationForPlane(EnemyPlane *enemyPlane)
{

	//中等飞机  
	if (enemyPlane->planeType == 2)
	{

		if (enemyPlane->hp == 3)
		{


			Vector<CCSpriteFrame *> array;
			CCString *string = CCString::create("enemy2_hit.png");
			CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(string->getCString());
			array.pushBack(frame);


			CCAnimation *animation = CCAnimation::createWithSpriteFrames(array, 0.1);
			CCAnimate *animate = CCAnimate::create(animation);

			CCRepeatForever *ac1 = CCRepeatForever::create(animate);

			enemyPlane->runAction(ac1);

			array.clear();

		}




	}
	//大飞机  
	else if (enemyPlane->planeType == 3)
	{

		if (enemyPlane->hp == 20)
		{
			Vector<CCSpriteFrame *> array;


				CCString *string = CCString::create("enemy3_hit.png");
				CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(string->getCString());

				array.pushBack(frame);


			CCAnimation *animation = CCAnimation::createWithSpriteFrames(array, 0.1);
			CCAnimate *animate = CCAnimate::create(animation);

			CCRepeatForever *ac1 = CCRepeatForever::create(animate);

			enemyPlane->runAction(ac1);

			array.clear();


		}


	}


}

//空降物  
void GameLayer::addBulletTypeTip()
{
	propTime++;
	if (propTime>500)
	{
		prop = ChangeBullet::create();
		prop->initWithType((proType)(rand() % 2 + 1));
		this->addChild(prop->prop,3);
		prop->propAnimation();
		prop->retain();
		propTime = 0;
		isVisible = true;
	}
}


void GameLayer::bulletLastTime()
{

	if (isBigBullet)
	{
		/*CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bullet2.png");
		for (int i = 0; i < bulletVec.size();i++)
			bulletVec.at(i)->setDisplayFrame(frame);*/
		bulletPower = 2;
		if (bulletlastTime > 0)
		{
			bulletlastTime--;
		}
		else
		{
			bulletlastTime = 1200;
			isBigBullet = false;
			isChangeBullet = true;
			/*CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("bullet1.png");
			for (int i = 0; i < bulletVec.size(); i++)
				bulletVec.at(i)->setDisplayFrame(frame);*/
			bulletPower = 1;
		}
	}

}

void GameLayer::playerBlowupAnimation(){
	playSprite->stopAllActions();

	Vector<CCSpriteFrame*> array;

	for (int i = 1; i <= 4; i++)
	{

		CCString *string = CCString::createWithFormat("hero_blowup_n%i.png", i);
		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(string->getCString());
		
		array.pushBack(frame);

	}

	CCAnimation *animation = CCAnimation::createWithSpriteFrames(array, 0.1);
	CCAnimate *animate = CCAnimate::create(animation);

	CCRepeatForever *ac1 = CCRepeatForever::create(animate);

	playSprite->runAction(ac1);

	array.clear();
}

void GameLayer::gameOver(){
	Director::getInstance()->pause();

	for (auto sp : this->getChildren())
	{

		sp->stopAllActions();

	}

	CCLayerColor *gameoverLayer = CCLayerColor::create(Color4B(0, 0, 0, 180), wSize.width, wSize.height);


	//gameoverLayer->setPosition(ccp((wSize.width - 480) / 2, 20));

	this->addChild(gameoverLayer, 3);


	CCLabelTTF *ttfLabel = CCLabelTTF::create("YOUR SCORE", "MarkerFelt-Thin", 50);
	ttfLabel->setPosition(ccp(gameoverLayer->getContentSize().width / 2 - ttfLabel->getContentSize().width / 2, gameoverLayer->getContentSize().height / 2 + 220));
	//ttfLabel->setColor(ccc3(0, 0, 0));
	ttfLabel->setAnchorPoint(ccp(0, 0));
	gameoverLayer->addChild(ttfLabel, 1);



	CCLabelTTF *scLabel = CCLabelTTF::create(scoreLabel->getString(), "MarkerFelt-Thin", 44);
	scLabel->setPosition(ccp(gameoverLayer->getContentSize().width / 2 - scLabel->getContentSize().width / 2, gameoverLayer->getContentSize().height / 2 + 140));
	//scLabel->setColor(ccc3(0, 0, 0));
	scLabel->setAnchorPoint(ccp(0, 0));
	gameoverLayer->addChild(scLabel, 1);



	CCMenuItemFont *startItem = CCMenuItemFont::create("CONTINUE", [](Ref* pSender){
		Director::getInstance()->replaceScene(HelloWorld::createScene());
		Director::getInstance()->resume();
	});

	auto menuItemExit = MenuItemFont::create("EXIT", [](Ref* pSender){
		#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
			MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
			return;
		#endif

			Director::getInstance()->end();

		#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			exit(0);
		#endif
		});

	//startItem->setPosition(ccp(gameoverLayer->getContentSize().width / 2, 60));
	startItem->setFontSizeObj(50);
	startItem->setFontNameObj("MarkerFelt-Thin");

	menuItemExit->setFontSizeObj(50);
	menuItemExit->setFontNameObj("MarkerFelt-Thin");
	//startItem->setColor(ccc3(0, 0, 0));

	CCMenu *pMenu = CCMenu::create(startItem, menuItemExit, NULL);
	pMenu->alignItemsVertically();

	pMenu->setPosition(CCPoint(wSize.width/2,wSize.height/2));

	gameoverLayer->addChild(pMenu, 1);

	//设置触摸事件监听
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [](Touch* touch, Event* event){ return true; };
	touchListener->onTouchMoved = [](Touch* touch, Event* event){};
	touchListener->onTouchEnded = [](Touch* touch, Event* event){};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, gameoverLayer);
	touchListener->setSwallowTouches(true);
}
