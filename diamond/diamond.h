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
	int n;//����
	void show();
	void revolve(int step);
private:
	void caculatePoint();
	int initial_r;
	int r;//�뾶
	Point* p;//��������
	double theta;
	double alpha;
};
#endif