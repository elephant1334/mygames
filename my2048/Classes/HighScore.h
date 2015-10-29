#ifndef _HIGHSCORE_H_
#define _HIGHSCROE_H_

#include"cocos2d.h"

class HighScore{
public:
	static HighScore* getInstance();
	static void distroyInstance();
	~HighScore();
	int getHighScore();
	int getScore();
	void setScore(int score);
private:
	HighScore();
	bool init();
	int m_score;
	int m_highScore;
};
#endif