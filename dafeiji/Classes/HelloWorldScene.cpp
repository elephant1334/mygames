#include "HelloWorldScene.h"
#include "GameLayer.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	auto wSize = Director::getInstance()->getVisibleSize();

	auto spriteFrameCache = SpriteFrameCache::getInstance();
	spriteFrameCache->addSpriteFramesWithFile("shoot_background.plist");
	spriteFrameCache->addSpriteFramesWithFile("shoot.plist");
	spriteFrameCache->addSpriteFramesWithFile("BM.plist");

	auto bgspriteFrame = spriteFrameCache->getSpriteFrameByName("background.png");

	auto bgSprite = Sprite::createWithSpriteFrame(bgspriteFrame);
	bgSprite->setPosition(CCPoint(wSize.width / 2, wSize.height / 2));
	float winw = wSize.width; //获取屏幕宽度
	 float winh = wSize.height;//获取屏幕高度
	 float spx = bgSprite->getTextureRect().getMaxX();
	 float spy = bgSprite->getTextureRect().getMaxY();
	 bgSprite->setScaleX(winw/spx); //设置精灵宽度缩放比例
	 bgSprite->setScaleY(winh/spx);
	this->addChild(bgSprite, 0);


	auto dazhanFrame = spriteFrameCache->getSpriteFrameByName("shoot_copyright.png");

	auto dazhanSprite = Sprite::createWithSpriteFrame(dazhanFrame);
	dazhanSprite->setPosition(CCPoint(wSize.width / 2, wSize.height / 2 + 50));
	this->addChild(dazhanSprite, 0);

	CCMenuItemFont *startItem = CCMenuItemFont::create("GAME START", CC_CALLBACK_0(HelloWorld::startGame,this));


	startItem->setPosition(ccp(wSize.width / 2, wSize.height / 2 - 200));
	startItem->setFontSizeObj(55);
	startItem->setFontNameObj("Georgia-Bold");

	CCMenu *pMenu = CCMenu::create(startItem, NULL);

	pMenu->setPosition(CCPoint(0, 0));

	this->addChild(pMenu, 1);
    return true;
}

void HelloWorld::initData(){

}

void HelloWorld::startGame(){
	CCScene *scene = CCScene::create();

	GameLayer *layer = GameLayer::create();

	scene->addChild(layer);

	//跳跃式动画  
	CCDirector::sharedDirector()->replaceScene(CCTransitionJumpZoom::create(1.2f, scene));
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
