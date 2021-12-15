#include <GL/glut.h>
#include<iostream>

constexpr auto LEFT_EDGE = 1;;
constexpr auto RIGHT_EDGE = 2;
constexpr auto BOTTOM_EDGE = 4;
constexpr auto TOP_EDGE = 8;

void LineGL(int x0, int  y0, int x1, int y1)
{
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(x0, y0);
	glVertex2f(x1, y1);
	glEnd();
}

struct MyRect
{
	float xmin, xmax, ymin, ymax;
};

MyRect  rect;
int xx0, yy0, xx1, yy1;

int CompCode(int x, int y, MyRect rect)
{
	int code = 0x00;
	if (y < rect.ymin)
		code = code | 4;
	if (y > rect.ymax)
		code = code | 8;
	if (x > rect.xmax)
		code = code | 2;
	if (x < rect.xmin)
		code = code | 1;
	return code;
}

int cohenSutherlandLineClip(MyRect  rect, int& x0, int& y0, int& x1, int& y1)
{
	int accept, done;
	float x, y;
	accept = 0;
	done = 0;

	int code1, code2, codeout;
	code1 = CompCode(x0, y0, rect);
	code2 = CompCode(x1, y1, rect);
	do {
		if (!(code1 | code2))
		{
			accept = 1;
			done = 1;
		}
		else if (code1 & code2)
			done = 1;
		else
		{
			if (code1 != 0)
				codeout = code1;
			else
				codeout = code2;

			if (codeout & LEFT_EDGE) {
				y = y0 + (y1 - y0) * (rect.xmin - x0) / (x1 - x0);
				x = (float)rect.xmin;
			}
			else if (codeout & RIGHT_EDGE) {
				y = y0 + (y1 - y0) * (rect.xmax - x0) / (x1 - x0);
				x = (float)rect.xmax;
			}
			else if (codeout & BOTTOM_EDGE) {
				x = x0 + (x1 - x0) * (rect.ymin - y0) / (y1 - y0);
				y = (float)rect.ymin;
			}
			else if (codeout & TOP_EDGE) {
				x = x0 + (x1 - x0) * (rect.ymax - y0) / (y1 - y0);
				y = (float)rect.ymax;
			}

			if (codeout == code1)
			{
				x0 = x; y0 = y;
				code1 = CompCode(x0, y0, rect);
			}
			else
			{
				x1 = x; y1 = y;
				code2 = CompCode(x1, y1, rect);
			}
		}
	} while (!done);

	if (accept)
		LineGL(x0, y0, x1, y1);
	return accept;
}

void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	glRectf(rect.xmin, rect.ymin, rect.xmax, rect.ymax);

	LineGL(xx0, yy0, xx1, yy1);

	glFlush();
}

void Init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);

	rect.xmin = 100;
	rect.xmax = 300;
	rect.ymin = 100;
	rect.ymax = 300;

	xx0 = 450, yy0 = 0, xx1 = 0, yy1 = 450;
	std::cout<<"Press key '1' to Clip!"<<std::endl;
	std::cout<<"Press key '2' to Restore!"<<std::endl;
}

void myReshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}

void myKeyboard(unsigned char key, int x, int y)
{
		exit(0);
}
void myMouse(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		if (button == GLUT_LEFT_BUTTON) {
			cohenSutherlandLineClip(rect, xx0, yy0, xx1, yy1);
			glutPostRedisplay();
		}
		else if (button == GLUT_RIGHT_BUTTON) {
			Init();
			glutPostRedisplay();
			glFlush();
		}
	}
	return;
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 480);
	glutCreateWindow("窗口裁剪");

	Init();
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	//注册交互函数以进行交互
	glutMouseFunc(myMouse);
	glutKeyboardFunc(myKeyboard);
	glutMainLoop();
	return 0;
}
