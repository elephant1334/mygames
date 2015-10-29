#include "SimpleRecognizer.h"

USING_NS_CC;

#define MAX_DOUBLE std::numeric_limits<double>::max();

// class define
SimpleRecognizer::SimpleRecognizer()
{
	this->result = SimpleGesturesError;
}

// be called in onTouchBegan
void SimpleRecognizer::beginPoint(cocos2d::Point point)
{
	this->result = SimpleGesturesError;
	points.clear();
	points.push_back(point);
}

void SimpleRecognizer::movePoint(cocos2d::Point point)
{
	points.push_back(point);
}

SimpleGestures SimpleRecognizer::endPoint(cocos2d::Point point)
{
	points.push_back(point);

	if (this->points.size() < 3) {
		return SimpleGesturesError;
	}

	SimpleGestures newRtn = SimpleGesturesError;
	int len = this->points.size();
	//ÿ�������ƶ�ʱ,�ڵ�ǰ�����֮ǰ����֮����㲻ͬ��x�����y����
	double dx = this->points[len - 1].x - this->points[0].x;
	double dy = this->points[len - 1].y - this->points[0].y;

	if (abs(dx) > abs(dy)) {
		//�����������,�˶����ƵĴ�����x�᷽��
		if (dx > 0) {
			newRtn = SimpleGesturesRight;
		}
		else {
			newRtn = SimpleGesturesLeft;
		}
	}
	else {
		//�����������,�˶����ƵĴ�����y�᷽��
		if (dy > 0) {
			newRtn = SimpleGesturesUp;
		}
		else {
			newRtn = SimpleGesturesDown;
		}
	}

	// first set result
	if (result == SimpleGesturesError) {
		result = newRtn;
	}

	// if diretcory change, not support Recongnizer
	if (result != newRtn) {
		result = SimpleGesturesNotSupport;
	}
	return result;
}

std::vector<Point>& SimpleRecognizer::getPoints()
{
	return points;
}