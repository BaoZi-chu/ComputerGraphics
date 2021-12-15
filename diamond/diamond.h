#ifndef diamond_h
#define diamond_h
#define _USE_MATH_DEFINES
#include<gl/glut.h>
#include<math.h>

class Point
{
public:
	Point();
	~Point();
	int x;
	int y;
private:

};
class diamond
{
public:
	diamond();
	diamond(int n, int r);
	~diamond();
	int n;//点数
	void show();
	void revolve(int step);
private:
	void caculatePoint();
	int initial_r;
	int r;//半径
	Point* p;//顶点数组
	double theta;
	double alpha;
};
#endif