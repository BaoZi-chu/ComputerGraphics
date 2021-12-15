#include <gl/glut.h>
#include <math.h>
#include<GL/glut.h>
//绘制前的准备，设置全局变量方便改变
const GLfloat Pi = 3.1415926536f;
const GLfloat m = 1.0f;
float t = 0.0;
GLfloat a = m / sqrt((2 - 2 * cos(72 * Pi / 180)));
GLfloat bx = a * cos(18 * Pi / 180);
GLfloat by = a * sin(18 * Pi / 180);
GLfloat cx = a * cos(54 * Pi / 180);
GLfloat cy = -a * sin(54 * Pi / 180);
GLfloat Point[10] = { 0,a,bx,by,cx,cy,-cx,cy,-bx,by };
GLfloat Point1[10] = { 0,a,cx,cy,-bx,by,bx,by,-cx,cy };
GLfloat Point2[10];


//绘制函数，里面加上自己想要绘制图形的代码，然后调用即可
void myDisplay(void)
{

    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(1.0f);//设置点的大小
    glLineWidth(1.5f);//设置直线的宽度
    /*
    * glBegin与glend之间放入的点会以某种方式绘制出来，具体的方式为glbegin后面的参数
    * 以下列出几种常用的方式
    * 1、画点 GL_POINTS，点的大小可用上面的函数设置
    * 2、GL_LINES，最简单的画线，将点两两相连，线的宽度可由上面函数设置
    * 3、GL_LINE_STRIP，画线将点连起来（串起来，有几个点连几个）
    * 4、GL_LINE_LOOP，画线将点连起来（串起来，自动将首位相连）
    */

    glBegin(GL_LINE_LOOP);
    glVertex2f(Point2[0], Point2[1]);
    glVertex2f(Point2[2], Point2[3]);
    glVertex2f(Point2[4], Point2[5]);
    glVertex2f(Point2[6], Point2[7]);
    glVertex2f(Point2[8], Point2[9]);
    glEnd();
    glFlush();
}

//回调函数的具体实现
/*
* 实现原理：
* glutTimerFunc(500, myTimerfunc, 1);首先该函数调用myTimerfunc，
*然后myTimerfunc改变与绘制有关的参数进而调用glutPostRedisplay();进行重绘，
*后调用glutTimerFunc重复该过程；
*/

void myTimerfunc(int value) {
    if (t > 1.0) t = 0;
    for (int i = 1; i < 10; i++) {
        Point2[i] = Point[i] * (1 - t) + Point1[i] * t;
    }
    t = t + 0.1;
    glutPostRedisplay();//重绘函数，调用mydisplay
    glutTimerFunc(50, myTimerfunc, 1);
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE); //初始化窗口的显示模式
    glutInitWindowPosition(100, 100);                //设置窗口的位置
    glutInitWindowSize(400, 400);                   //设置窗口的大小
    glutCreateWindow("五角星变化");       //创建窗口
    glutDisplayFunc(&myDisplay);                  //设置当前窗口的显示回调函数
    glutTimerFunc(50, myTimerfunc, 1);           //注册回调函数
    glutMainLoop();                              //启动主 GLUT事件处理循环
    return 0;
}
