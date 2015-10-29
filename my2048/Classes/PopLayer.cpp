#include"PopLayer.h"
#include"HelloWorldScene.h"
USING_NS_CC;

PopLayer* PopLayer::create(const cocos2d::Color4B& color){
	PopLayer* pRet = new PopLayer();
	if (pRet&&pRet->initWithColor(color)){
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool PopLayer::initWithColor(const Color4B& color)
{
	if (!LayerColor::initWithColor(color)) {
		return false;
	}

	Size winSize = Director::getInstance()->getWinSize();
	Point centerPos = Point(winSize.width / 2, winSize.height / 2);

	MenuItemFont::setFontName("Consolas");
	MenuItemFont::setFontSize(80);

	auto menuItemContinue = MenuItemFont::create("CONTINUE", [&](Ref* pSender){
		removeFromParent();
		Director::getInstance()->resume();
	});
	auto menuItemRestart = MenuItemFont::create("RESTART", [](Ref* pSender){
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


	auto menu = Menu::create(menuItemContinue, menuItemRestart, menuItemExit, NULL);
	menu->alignItemsVertically();
	addChild(menu);
	menu->setPosition(centerPos);


	//ÉèÖÃ´¥ÃşÊÂ¼ş¼àÌı
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [](Touch* touch, Event* event){return true; };
	touchListener->onTouchMoved = [](Touch* touch, Event* event){};
	touchListener->onTouchEnded = [](Touch* touch, Event* event){};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	touchListener->setSwallowTouches(true);

	return true;
}

//void PopLayer::onContinue(Ref* pSender)
//{
//	removeFromParent();
//	Director::getInstance()->resume();
//}
