#include"diamond.h"
Point::Point()
{
	x = 0;
	y = 0;

}

Point::~Point()
{
}


diamond::diamond()
{
	n = 21;
	r = 15;
	p = new Point[n];
	alpha = 0;
	theta = 360.0 / n;
	caculatePoint();
	
}

diamond::diamond(int n, int r) {
	this->n = n;

	this->r = r;
	p = new Point[n];
	alpha = 0;
	theta = 360.0 / n;
	caculatePoint();
}

diamond::~diamond()
{
	delete[]p;
	p = nullptr;
}

void diamond::caculatePoint() {
	double bata = 0;
	for (int i = 0; i < n; i++) {
		bata = ((i - 0.5) * theta + alpha) / 180 * M_PI;
		p[i].x = round(r * cos(bata)) + 100;
		p[i].y = round(r * sin(bata)) + 100;
	}
}
/*���� show չʾ��ʯ�����������ַ�ʽ����
*/
void diamond::show() {
	
	int k = 0;
	double color = alpha / 400;
	glClear(GL_COLOR_BUFFER_BIT);        //�õ�ǰ����ɫ��䴰��
	//glColor3f(0.0f, 0.0f, 0.0f);                  //���õ�ǰ�Ļ�ͼ��ɫΪ��ɫ
	glColor3f(color, color, color);

	if (n % 2) {
		glBegin(GL_LINE_LOOP);
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < i * n; j = j + i) {
				k = j % n;
				glVertex2f(p[k].x, p[k].y);
			}
		}
	}
	else {
		glBegin(GL_LINES);
		for (int i = 0; i < n - 1; i++) {
			for (int j = i; j < n; j++) {
				glVertex2f(p[i].x, p[i].y);
				glVertex2f(p[j].x, p[j].y);
			}
		}
	}
	glEnd();
}

void diamond::revolve(int step=1) {
	if (alpha > 360) alpha = 0;
	caculatePoint();
	alpha += step;
}

