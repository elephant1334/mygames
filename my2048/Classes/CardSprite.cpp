#include"CardSprite.h"
USING_NS_CC;

CardSprite* CardSprite::createCardSprite(int number, int wight, int height, Point position)
{
	//这里是创建一个自定义精灵类，格式很规范化
	CardSprite *card = new CardSprite();
	if (card && card->init())
	{
		card->autorelease();
		card->initCard(number, wight, height, position.x, position.y);
		return card;
	}
	CC_SAFE_DELETE(card);

	return NULL;
}

void CardSprite::initCard(int number, int width, int height, float CardSpriteX, float CardSpriteY){
	this->number = number;

	colorBackGround = LayerColor::create(Color4B(200, 190, 180, 155), width - 15, height - 15);
	colorBackGround->setPosition(Point(CardSpriteX, CardSpriteY));

	if (number > 0){
		labelCardNumber = Label::createWithSystemFont(__String::createWithFormat("%i", number)->getCString(),"Consolas",40);
		labelCardNumber->setPosition(Point(colorBackGround->getContentSize().width / 2, colorBackGround->getContentSize().height / 2));
		labelCardNumber->setTag(8);
		colorBackGround->addChild(labelCardNumber);
	}
	else{
		    labelCardNumber = Label::createWithSystemFont("", "Consolas", 40);
			labelCardNumber->setPosition(Point(colorBackGround->getContentSize().width / 2, colorBackGround->getContentSize().height / 2));
			labelCardNumber->setTag(8);
			colorBackGround->addChild(labelCardNumber);
	}
	this->addChild(colorBackGround);
}
int CardSprite::getNumber(){
	return number;
}

void CardSprite::setNumber(int num){
	number = num;
	if (num > 0){
		labelCardNumber->setString(__String::createWithFormat("%i", number)->getCString());
	}
	else{
		labelCardNumber->setString("");
	}
	labelCardNumber->setSystemFontSize(40);
	if (number == 0){
		colorBackGround->setColor(Color3B(200, 190, 180));
	}
	if (number == 2) {
		colorBackGround->setColor(Color3B(240, 230, 220));
	}
	if (number == 4) {
		colorBackGround->setColor(Color3B(240, 220, 200));
	}
	if (number == 8) {
		colorBackGround->setColor(Color3B(240, 180, 120));
	}
	if (number == 16) {
		colorBackGround->setColor(Color3B(240, 140, 90));
	}
	if (number == 32) {
		colorBackGround->setColor(Color3B(240, 120, 90));
	}
	if (number == 64) {
		colorBackGround->setColor(Color3B(240, 90, 60));
	}
	if (number == 128) {
		colorBackGround->setColor(Color3B(240, 90, 60));
	}
	if (number == 256) {
		colorBackGround->setColor(Color3B(240, 200, 70));
	}
	if (number == 512) {
		colorBackGround->setColor(Color3B(240, 200, 70));
	}
	if (number == 1024) {
		colorBackGround->setColor(Color3B(0, 130, 0));
	}
	if (number == 2048) {
		colorBackGround->setColor(Color3B(0, 130, 0));
	}
}