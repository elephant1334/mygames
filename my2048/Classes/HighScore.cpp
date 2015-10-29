#include"HighScore.h"

USING_NS_CC;

static HighScore* sharedHighScore = NULL;

HighScore* HighScore::getInstance(){
	if (!sharedHighScore){
		sharedHighScore = new HighScore();
		sharedHighScore->init();
	}
	return sharedHighScore;
}

void HighScore::distroyInstance(){
	CC_SAFE_DELETE(sharedHighScore);
}

HighScore::HighScore(){
	m_score = 0;
	m_highScore = 0;
}

HighScore::~HighScore(){
	distroyInstance();
}

bool HighScore::init(){
	m_highScore = UserDefault::getInstance()->getIntegerForKey("HighScore");

	return true;
}

int HighScore::getHighScore()
{
	return m_highScore;
}

int HighScore::getScore()
{
	return m_score;
}

void HighScore::setScore(int score)
{
	m_score = score;
	if (score > m_highScore) {
		m_highScore = score;
		UserDefault::getInstance()->setIntegerForKey("HighScore", score);
	}
}