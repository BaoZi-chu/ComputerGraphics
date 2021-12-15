#pragma once
#include"P3d.h"
#include"CT2.h"
#include"Face.h"
class CSphere
{
public:
	CSphere();
	CSphere(float radius);
	virtual~CSphere();
	void ReadVertex();//读入顶点坐标
	void ReadFace();//读入面坐标
	void Draw();//绘制球面
	void setRadius(float radius);
public:
	CP3d* V;//圆柱顶点一维数组
	CP3d* V1;
	CT2* T;//圆柱纹理一维数组
	CT2* T1;
	CFace** F;//面的二维数组
	int N1, N2;//N1为经度区间,N2为纬度区间
	int N3, N4;
	int gAlpha, gBeta;//纬度角与经度角
	int gA1pha1, gBeta1;
	float r;//球体半径
private:
	//void GetGeometry(float radius);
	void initial();
	void tran(CVector3 p, float* v) {

		v[0] = p.x;
		v[1] = p.y;
		v[2] = p.z;

	}
};

