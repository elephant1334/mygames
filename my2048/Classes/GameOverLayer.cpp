#include "GameOverLayer.h"

#include "GameOverLayer.h"
#include "HelloWorldScene.h"
#include "HighScore.h"

GameOverLayer* GameOverLayer::create(const Color4B& color)
{
	GameOverLayer *pRet = new GameOverLayer();
	if (pRet && pRet->initWithColor(color))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return NULL;
}

bool GameOverLayer::initWithColor(const Color4B& color)
{
	if (!LayerColor::initWithColor(color)) {
		return false;
	}

	Size winSize = Director::getInstance()->getWinSize();
	Point centerPos = Point(winSize.width / 2, winSize.height / 2);

	auto gameOverTitle = Label::createWithSystemFont("GAME OVER", "Consolas", 80);
	gameOverTitle->setPosition(Point(centerPos.x, centerPos.y + 150));
	addChild(gameOverTitle);

	char score[64];
	sprintf(score, "%d", HighScore::getInstance()->getScore());
	auto scoreTitle = Label::createWithSystemFont(score, "Consolas", 60);
	scoreTitle->setPosition(Point(centerPos.x, centerPos.y + 50));
	addChild(scoreTitle);

	char temp[64];
	sprintf(temp, "BEST:%d", HighScore::getInstance()->getHighScore());
	auto highScoreTitle = Label::createWithSystemFont(temp, "Consolas", 40);
	highScoreTitle->setPosition(Point(centerPos.x, centerPos.y - 50));
	addChild(highScoreTitle);

	MenuItemFont::setFontName("Consolas");
	MenuItemFont::setFontSize(80);
	auto menuItemRestart = MenuItemFont::create("RESTART", [](Ref* pSender){
		Director::getInstance()->replaceScene(HelloWorld::createScene());
		Director::getInstance()->resume();
	});


	auto menu = Menu::create(menuItemRestart, NULL);
	addChild(menu);
	menu->setPosition(Point(centerPos.x, centerPos.y - 150));


	//ÉèÖÃ´¥ÃþÊÂ¼þ¼àÌý
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [](Touch* touch, Event* event){ return true; };
	touchListener->onTouchMoved = [](Touch* touch, Event* event){ };
	touchListener->onTouchEnded = [](Touch* touch, Event* event){ };
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	touchListener->setSwallowTouches(true);

	return true;
}