#ifndef _SIMPLERECOGNIZER_H_
#define _SIMPLERECOGNIZER_H_

#include"cocos2d.h"

typedef enum {
	SimpleGesturesRight,
	SimpleGesturesLeft,
	SimpleGesturesUp,//
	SimpleGesturesDown,//
	SimpleGesturesError,//
	SimpleGesturesNotSupport

} SimpleGestures;

class SimpleRecognizer
{
protected:
	double X;
	double Y;
	SimpleGestures result;
	std::vector<cocos2d::Point> points;

public:
	SimpleRecognizer();

	void beginPoint(cocos2d::Point point);
	void movePoint(cocos2d::Point point);
	SimpleGestures endPoint(cocos2d::Point point);

	std::vector<cocos2d::Point>& getPoints();

};
#endif