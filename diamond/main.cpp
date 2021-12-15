#include<iostream>
#include<gl/glut.h>
#include"diamond.h"

using namespace std;

diamond d(20,60);
//diamond d;
double t = 0;
void Initial(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);          //设置窗口背景色为白色
	glMatrixMode(GL_PROJECTION);        //指定设定投影参数
	gluOrtho2D(0.0, 200, 0.0, 200);            //设置投影参数
}


void show() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	d.show();//钻石对象
	glFlush();                          //清空OpenGL命令缓冲区，执行OpenGL命令 
	glutSwapBuffers();

}
void myTimerfunc(int value) {
	
	d.revolve(1);
	glutPostRedisplay();
	glutTimerFunc(10, myTimerfunc, 1);
}
void myIdle(void)
{
	
	d.revolve(1);
	show();
}
int main(int argc, char* argv[]) {
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); //初始化窗口的显示模式
	glutInitWindowPosition(100, 100);                //设置窗口的位置
	glutInitWindowSize(400, 400);                   //设置窗口的大小
	glutCreateWindow("钻石图");       //创建窗口
	
	glutDisplayFunc(&show);                  //设置当前窗口的显示回调函数
	Initial();                                     //完成窗口初始化
	glutTimerFunc(10, myTimerfunc, 1);
	//glutIdleFunc(&myIdle);
	glutMainLoop();                              //启动主 GLUT事件处理循环
	return 0;
}