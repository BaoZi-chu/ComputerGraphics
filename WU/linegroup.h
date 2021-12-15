#ifndef linegroup_h
#define linegroup_h
#define _USE_MATH_DEFINES
#include<gl/glut.h>
#include<math.h>
class Point
{
public:
	int x;
	int y;
};
class linegroup
{
public:
	Point* p;
	double theta;
	double alpha;
	linegroup();
	linegroup(int n, int r);
	~linegroup();
	void drawline(int x0, int y0, int x1, int y);//直线起始点、终点坐标
	void drawPoint(int x, int y, float e);
	void drawLineWU(int x0, int y0, int x1, int y1);
	void show();
	void showWU();
	void revolve(int step);
private:
	
	void caculatePoint();
	int n;//线的条数
	int r;
};
#endif

