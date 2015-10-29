#include "HelloWorldScene.h"
#include"CardSprite.h"
#include"SimpleRecognizer.h"
#include"PopLayer.h"
#include"HighScore.h"
#include"GameOverLayer.h"
USING_NS_CC;
HelloWorld::~HelloWorld(){
	delete recognizer;
}
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

//创建卡片
void HelloWorld::createCardSprite(Size size){
	int cardSize = (size.height - 36) / 4;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++){
			CardSprite* card = CardSprite::createCardSprite(0, cardSize, cardSize, Point(cardSize*i + 80, cardSize*j + 20));
			cardArr[i][j] = card;
			addChild(card);
		}
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
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto layerColorBG = LayerColor::create(Color4B(180, 170, 160, 255));
	this->addChild(layerColorBG);

	MenuItemFont::setFontName("Consolas");
	MenuItemFont::setFontSize(80);
	auto menuItemPause = MenuItemFont::create("PAUSE", CC_CALLBACK_1(HelloWorld::onPause, this));

	auto menu = Menu::create();
	menu->setPosition(Point(visibleSize.width - 150, visibleSize.height / 2 + 200));
	menu->addChild(menuItemPause);
	this->addChild(menu);

	auto cardNumberTitle = Label::createWithSystemFont("SCORE", "Consolas", 80);
	cardNumberTitle->setPosition(Point(visibleSize.width - 150, visibleSize.height / 2 + 50));
	this->addChild(cardNumberTitle);

	cardNumberTTF = Label::createWithSystemFont("0", "Consolas", 80);
	cardNumberTTF->setPosition(Point(visibleSize.width - 150, visibleSize.height / 2 - 50));
	this->addChild(cardNumberTTF);
    

	createCardSprite(visibleSize);

	//初始时生成2个2 
	createCardNumber();
	createCardNumber();

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	//_eventDispacther->addEventListenerWithSceneGraphPriority(touchListener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	recognizer = new SimpleRecognizer();
	score = 0;
    return true;
}

void HelloWorld::onPause(Ref* pSender){
	PopLayer *poplayer = PopLayer::create(Color4B(0, 0, 0, 180));
	getParent()->addChild(poplayer);
	Director::getInstance()->pause();
}

void HelloWorld::createCardNumber(){
	while (true) {
		int i = CCRANDOM_0_1() * 4;        //生成0~3随机数 
		int j = CCRANDOM_0_1() * 4;

		if (cardArr[i][j]->getNumber() == 0)
		{
			//2和4的生成率为9:1 
			cardArr[i][j]->setNumber(CCRANDOM_0_1() * 10 < 1 ? 4 : 2);
			break;
		}
	}
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event){
	Point beginTouch = touch->getLocation();
	recognizer->beginPoint(beginTouch);
	return true;
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event){
	Point pos = touch->getLocation();
	recognizer->movePoint(pos);
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event){
	Point pos = touch->getLocation();
	SimpleGestures rtn = recognizer->endPoint(pos);
	switch (rtn){
	case SimpleGesturesLeft:
		doLeft();
		doCheck();
		setScore();
		break;
	case SimpleGesturesRight:
		doRight();
		doCheck();
		setScore();
		break;
	case SimpleGesturesUp:
		doUp();
		doCheck();
		setScore();
		break;
	case SimpleGesturesDown:
		doDown();
		doCheck();
		setScore();
		break;
	default:
		break;
	}
}

void HelloWorld::doLeft(){
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			for (int x1 = x + 1; x1<4; x1++)
			{
				if (cardArr[x1][y]->getNumber() > 0)
				{
					if (cardArr[x][y]->getNumber() <= 0)
					{
						cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber());
						cardArr[x1][y]->setNumber(0);
						x--;
						//isMove = true;
					}
					else if (cardArr[x][y]->getNumber() == cardArr[x1][y]->getNumber())
					{
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x1][y]->setNumber(0);

						//改变分数 
						score += cardArr[x][y]->getNumber();
						//isMove = true;
					}
					break;
				}
			}
		}
	}
}
void HelloWorld::doRight(){
	for (int y = 0; y < 4; y++)
	{
		for (int x = 3; x >= 0; x--)
		{
			for (int x1 = x - 1; x1>=0; x1--)
			{
				if (cardArr[x1][y]->getNumber() > 0)
				{
					if (cardArr[x][y]->getNumber() <= 0)
					{
						cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber());
						cardArr[x1][y]->setNumber(0);
						x++;
						//isMove = true;
					}
					else if (cardArr[x][y]->getNumber() == cardArr[x1][y]->getNumber())
					{
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x1][y]->setNumber(0);

						//改变分数 
						score += cardArr[x][y]->getNumber();
						//isMove = true;
					}
					break;
				}
			}
		}
	}
}

void HelloWorld::doDown(){
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			for (int y1 = y + 1; y1<4; y1++)
			{
				if (cardArr[x][y1]->getNumber() > 0)
				{
					if (cardArr[x][y]->getNumber() <= 0)
					{
						cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber());
						cardArr[x][y1]->setNumber(0);
						y--;
						//isMove = true;
					}
					else if (cardArr[x][y]->getNumber() == cardArr[x][y1]->getNumber())
					{
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x][y1]->setNumber(0);

						//改变分数 
						score += cardArr[x][y]->getNumber();
						//isMove = true;
					}
					break;
				}
			}
		}
	}
}

void HelloWorld::doUp(){
	for (int x = 0; x < 4; x++)
	{
		for (int y = 3; y >= 0; y--)
		{
			for (int y1 = y - 1; y1>=0; y1--)
			{
				if (cardArr[x][y1]->getNumber() > 0)
				{
					if (cardArr[x][y]->getNumber() <= 0)
					{
						cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber());
						cardArr[x][y1]->setNumber(0);
						y++;
						//isMove = true;
					}
					else if (cardArr[x][y]->getNumber() == cardArr[x][y1]->getNumber())
					{
						cardArr[x][y]->setNumber(cardArr[x][y]->getNumber() * 2);
						cardArr[x][y1]->setNumber(0);

						//改变分数 
						score += cardArr[x][y]->getNumber();
						//isMove = true;
					}
					break;
				}
			}
		}
	}
}

void HelloWorld::doCheck(){
	bool isGameOver = true;
	for (int y = 0; y < 4; y++)
		for (int x = 0; x < 4; x++){
			if (cardArr[x][y] == 0 ||
				(x>0 && cardArr[x][y]->getNumber() == cardArr[x - 1][y]->getNumber()) ||
				(x < 3 && cardArr[x][y]->getNumber() == cardArr[x + 1][y]->getNumber()) ||
				(y>0 && cardArr[x][y]->getNumber() == cardArr[x][y - 1]->getNumber()) ||
				(y < 3 && cardArr[x][y]->getNumber() == cardArr[x][y + 1]->getNumber()))
				isGameOver = false;
		}
	if (isWin()) {

		successLayer = LayerColor::create(Color4B(0, 0, 0, 180));
		Size winSize = Director::getInstance()->getWinSize();
		Point centerPos = Point(winSize.width / 2, winSize.height / 2);
		auto gameOverTitle = Label::createWithSystemFont("YOU WIN", "Consolas", 80);
		gameOverTitle->setPosition(centerPos);
		successLayer->addChild(gameOverTitle);

		addChild(successLayer, 1);

		scheduleOnce(SEL_SCHEDULE(&HelloWorld::removeSuccessLayer), 2);
		return;
	}

	//isGameOver = true; 
	if (isGameOver)
	{
		UserDefault::getInstance()->setBoolForKey("history", false);

		HighScore::getInstance()->setScore(score);
		GameOverLayer *gameoverLayer = GameOverLayer::create(Color4B(0, 0, 0, 180));
		addChild(gameoverLayer, 1);

		Director::getInstance()->pause();
	}
	else
	{
			createCardNumber();

			//saveStatus();
	}
}

bool HelloWorld::isWin(){
	bool win = false;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (2048 == cardArr[i][j]->getNumber())
			{
				win = true;
				break;
			}
		}
	}

	return win;
}

void HelloWorld::setScore(){
	cardNumberTTF->setString(__String::createWithFormat("%i", score)->getCString());
	//cardNumberTTF = Label::createWithSystemFont("0", "Consolas", 80);
}

void HelloWorld::removeSuccessLayer()
{
	successLayer->removeFromParent();
}
