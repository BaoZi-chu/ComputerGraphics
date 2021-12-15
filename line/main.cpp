#include <iostream>
#include<GL/glut.h>
#include"linegroup.h"
using namespace std;
void Initial(void);
void myDisplay(void);
void grid(void);
void gridwindow(int* argcp, char** argv);
void myTimerfunc(int value);
linegroup l(20, 100);
int main(int argc, char* argv[])

{
	gridwindow(&argc, argv);
    return 0;

}

void gridwindow(int* argcp, char** argv) {
	glutInit(argcp, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE); //初始化窗口的显示模式
	glutInitWindowPosition(100, 100);                //设置窗口的位置
	glutInitWindowSize(400, 400);                   //设置窗口的大小
	glutCreateWindow("绘制直线");       //创建窗口
	glutDisplayFunc(&myDisplay);                  //设置当前窗口的显示回调函数
	Initial();                                     //完成窗口初始化
	glutTimerFunc(20, myTimerfunc, 1);
	glutMainLoop();                              //启动主 GLUT事件处理循环
}
void Initial(void) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);          //设置窗口背景色为白色
	glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);        //指定设定投影参数
    gluOrtho2D(-1.0, 401.0, -1.0, 401.0);            //设置投影参数
}
void myDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT);        //用当前背景色填充窗口
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);          //设置窗口背景色为白色
	grid();
	//bress(10,0,10,200);
	l.show();
	glFlush();
}
void myTimerfunc(int value) {
	l.revolve(1);
	glutPostRedisplay();
	glutTimerFunc(1000, myTimerfunc, 1);
}
void grid(void) {
	//画10*10网格
	glColor3f(0.0f, 1.0f, 0.0f); //绿色
	for (int i = 0; i <= 10; i++) //11条水平线
	{
		glBegin(GL_LINES);
		glVertex2d(0.0, i * 40.0);
		glVertex2d(400.0, i * 40.0);
		glEnd();
	}
	glBegin(GL_LINES); //11条竖线
	for (int i = 0; i <= 10; i++)
	{
		glVertex2d(i * 40.0, 0.0);
		glVertex2d(i * 40.0, 400.0);
	}
	glEnd();
}


