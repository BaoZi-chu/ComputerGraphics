#include "linegroup.h"
#include<iostream>
linegroup::linegroup()
{
	n = 21;
	r = 15;
	p = new Point[n];
	alpha = 0;
	theta = 360.0 / n;
	caculatePoint();
}

linegroup::linegroup(int n, int r)
{
	this->n = n;
	this->r = r;
	p = new Point[n];
	alpha = 0;
	theta = 360.0 / n;
	caculatePoint();
}

linegroup::~linegroup()
{
	delete[]p;
	p = nullptr;
}

void linegroup::show()
{
	Point A{};
	A.x = A.y = 200;
	for (int i = 0; i < n; i++)
		drawline(A.x, A.y, p[i].x, p[i].y);
}

void linegroup::revolve(int step)
{
	if (alpha > 360) alpha = 0;
	caculatePoint();
	alpha += step;
}
/*����ֱ�ߺ���
* ������� ֱ����ʼ��x��y���յ�����y��z����
*/
void linegroup::drawline(int x0, int y0, int x1, int y1) {
	int x, y;
	if (x0 > x1) {
		x = x1;
		y = y1;
		x1 = x0;
		y1 = y0;
		x0 = x;
		y0 = y;
	}//��ʼ�㡢�յ㽻��
	else {
		if (x0 == x1) {
			x = x0;
			if (y0 > y1) {
				y = y1;
				y1 = y0;
			}
			else {
				y = y0;
			}
			while (y <= y1) {
				glColor3f(0.0f, 0.0f, 1.0f);
				glBegin(GL_POINTS);
				glVertex2d(x * 1.0, y * 1.0);
				glEnd();
				y++;
			}
			return;
		}//���߻���

	}
	x = x0;
	y = y0;//��ʼ��
	double k = (y1 - y) * 1.0 / ((x1 - x) * 1.0);//ֱ��б�ʼ���
	double d = 0;
	float e = d - 0.5;//�����ж���һ��λ��
	GLfloat color = 0;
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_POINTS);
	glVertex2d(x * 1.0, y * 1.0);
	int dx = x1 - x0;
	int dy = y1 - y0;
	int flag = 0;
	if (k > 0) {
		flag = 1;
	}
	else {
		flag = -1;
	}
	int i = 0;
	if (abs(k) <= 1) {
		while (i <= abs(dy) && x <= x1) {
			e = e + k;
			x++;
			if (e * flag > 0) {
				i++;
				y += flag;
				e -= flag;
			}
			glVertex2d(x * 1.0, y * 1.0);
		}
	}//б����-1~1֮��ֱ�ߵĻ���
	else {
		k = 1 / k;

		while ((i <= abs(dy)) && x <= x1) {
			e = e + k;
			y += flag;
			if (e * flag >= 0) {
				i++;
				x++;
				e -= flag;
			}
			glVertex2d(x * 1.0, y * 1.0);
		}
	}//б�ʾ���ֵ����һ��ֱ�߻���

	glEnd();
}




void linegroup::caculatePoint()
{
	double bata = 0;
	for (int i = 0; i < n; i++) {
		bata = ((i - 0.5) * theta + alpha) / 180 * M_PI;
		p[i].x = round(r * cos(bata)) + 200;
		p[i].y = round(r * sin(bata)) + 200;
	}
}
