#include "pch.h"
#include "CSphere.h"
#define PI 3.1415926
#include <gl/GL.h>
/*
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
*/
CSphere::CSphere()
{
	initial();
	r = 5;
	ReadVertex();
	ReadFace();
}
CSphere::CSphere(float radius=5)
{
	initial();
	r = radius;
	ReadVertex();
	ReadFace();
}


CSphere::~CSphere()
{

	if (V != NULL)
	{
		delete[]V;
		V = NULL;
	}

	if (V1 != NULL)
	{
		delete[]V1;
		V1 = NULL;
	}
	if (T != NULL)
	{
		delete[]T;
		T = NULL;
	}

	if (T1 != NULL)
	{
		delete[]T1;
		T1 = NULL;
	}
	for (int n = 0; n < N1; n++)
	{
		delete[] F[n];
		F[n] = NULL;
	}
	delete[]F;
	F = nullptr;
}

void CSphere::ReadVertex()//点表
{
	double gAlpha1, gBeta1;
	//计算北极点坐标

	V[0].x = 0, V[0].y = r, V[0].z = 0;
	V1[0].x = 200, V1[0].y = r - 60, V1[0].z = 200;

	T[0].u = 0; T[0].v = 0;//闲置
	T1[0].u = 0; T1[0].v = 0;//闲置

	//按行循环计算球体上的点坐标
	for (int i = 0; i < N1 - 1; i++)
	{
		gAlpha1 = (i + 1) * gAlpha * PI / 180;
		for (int j = 0; j < N2; j++)
		{
			gBeta1 = j * gBeta * PI / 180;
			V[i * N2 + j + 1].x = r * sin(gAlpha1) * sin(gBeta1);
			V[i * N2 + j + 1].y = r * cos(gAlpha1);
			V[i * N2 + j + 1].z = r * sin(gAlpha1) * cos(gBeta1);
			T[i * N2 + j + 1].u = gBeta1 / (2 * PI) ;
			T[i * N2 + j + 1].v = (PI - gAlpha1) / PI;
		}
		for (int j = 0; j < N2; j++)
		{
			gBeta1 = j * gBeta * PI / 180;
			V1[i * N2 + j + 1].x = (r - 50) * sin(gAlpha1) * sin(gBeta1) + 200;
			V1[i * N2 + j + 1].y = (r - 50) * cos(gAlpha1);
			V1[i * N2 + j + 1].z = (r - 50) * sin(gAlpha1) * cos(gBeta1) + 200;
			T1[i * N2 + j + 1].u = gBeta1 / (2 * PI);
			T1[i * N2 + j + 1].v = (PI - gAlpha1) / PI;
		}

	}
	//计算南极点坐标

	V[(N1 - 1) * N2 + 1].x = 0, V[(N1 - 1) * N2 + 1].y = -r, V[(N1 - 1) * N2 + 1].z = 0;
	T[(N1 - 1) * N2 + 1].u = 0; T[(N1 - 1) * N2 + 1].v = 0;//闲置

	V1[(N1 - 1) * N2 + 1].x = 200, V1[(N1 - 1) * N2 + 1].y = -r + 60, V1[(N1 - 1) * N2 + 1].z = 200;
	T1[(N1 - 1) * N2 + 1].u = 0; T1[(N1 - 1) * N2 + 1].v = 0;//闲置


}

void CSphere::ReadFace()//读入面表
{

	for (int j = 0; j < N2; j++)//构造北极三角形面片
	{
		int tempj = j + 1;
		if (tempj == N2) tempj = 0;//面片的首尾连接
		int NorthIndex[3];//北极三角形面片索引号数组
		NorthIndex[0] = 0;
		NorthIndex[1] = j + 1;
		NorthIndex[2] = tempj + 1;
		F[0][j].SetNum(3);
		for (int k = 0; k < F[0][j].vN; k++)
			F[0][j].vI[k] = NorthIndex[k];
	}

	for (int i = 1; i < N1 - 1; i++)//构造球面四边形面片
	{
		for (int j = 0; j < N2; j++)
		{
			int tempi = i + 1;
			int tempj = j + 1;
			if (tempj == N2) tempj = 0;
			int BodyIndex[4];//球面四边形面片索引号数组
			BodyIndex[0] = (i - 1) * N2 + j + 1;
			BodyIndex[1] = (tempi - 1) * N2 + j + 1;
			BodyIndex[2] = (tempi - 1) * N2 + tempj + 1;
			BodyIndex[3] = (i - 1) * N2 + tempj + 1;
			F[i][j].SetNum(4);
			for (int k = 0; k < F[i][j].vN; k++)
				F[i][j].vI[k] = BodyIndex[k];
		}
	}

	for (int j = 0; j < N2; j++)//构造南极三角形面片
	{
		int tempj = j + 1;
		if (tempj == N2) tempj = 0;
		int SouthIndex[3];//南极三角形面片索引号数组
		SouthIndex[0] = (N1 - 2) * N2 + j + 1;
		SouthIndex[1] = (N1 - 1) * N2 + 1;
		SouthIndex[2] = (N1 - 2) * N2 + tempj + 1;
		F[N1 - 1][j].SetNum(3);
		for (int k = 0; k < F[N1 - 1][j].vN; k++)
			F[N1 - 1][j].vI[k] = SouthIndex[k];
	}
}


void CSphere::Draw()//绘制球面
{
	float v0[3];//底面与顶面三角形顶点数组
	float v1[3];
	float v2[3];
	float v3[3];
	CT2 Texture3[3];//底面与顶面三角形纹理数组
	float Normal3[3];//底面与顶面三角形法矢量数组
	CPi3 Point4[4];//侧面四边形顶点数组
	CT2 Texture4[4];//侧面四边形纹理数组

	for (int i = 0; i < N1; i++)
	{
		for (int j = 0; j < N2; j++)
		{
			
			F[i][j].SetFaceNormal(V[F[i][j].vI[0]], V[F[i][j].vI[1]], V[F[i][j].vI[2]]);//计算小面片法矢量

			F[i][j].fNormal.Normalize();//单位化法矢量

				if (3 == F[i][j].vN)//处理三角形面片
				{
						
					double tempi = i + 1, tempj = j + 1;//对三角形面片进行特殊处理
					Texture3[0].u = gBeta * (j) / 360.0; Texture3[0].v = (1.0 - gAlpha * i / 180.0);
					Texture3[1].u = gBeta * (j) / 360.0; Texture3[1].v = (1.0 - gAlpha * tempi / 180.0);
					Texture3[2].u = gBeta * tempj / 360.0; Texture3[2].v = (1.0 - gAlpha * i / 180.0);
					//绘制三角形面片
					tran(F[i][j].fNormal, Normal3);
					tran(V[F[i][j].vI[0]],v0);
					tran(V[F[i][j].vI[1]],v1);
					tran(V[F[i][j].vI[2]],v2);
					glBegin(GL_TRIANGLES);
					glNormal3fv(Normal3);
					glTexCoord2f(Texture3[0].u, Texture3[0].v); glVertex3fv(v0);
					glTexCoord2f(Texture3[1].u, Texture3[1].v); glVertex3fv(v1);
					glTexCoord2f(Texture3[2].u, Texture3[2].v); glVertex3fv(v2);
					glEnd();
				}
				else//处理四边形面片
				{
					for (int m = 0; m < F[i][j].vN; m++)
					{
						//Normal4[m] = CVector3(V[F[i][j].vI[m]]);
						Texture4[m] = T[F[i][j].vI[m]];
					}
					if (N2 - 1 == j)//消除图像纹理的接缝
					{
						Texture4[2].u = 1.0;
						Texture4[3].u = 1.0;
					}
					//这里是根据点表绘制立方体算法
					tran(F[i][j].fNormal, Normal3);
					tran(V[F[i][j].vI[0]], v0);
					tran(V[F[i][j].vI[1]], v1);
					tran(V[F[i][j].vI[2]], v2);
					tran(V[F[i][j].vI[3]], v3);
					glBegin(GL_QUADS);
					glNormal3fv(Normal3);
					glTexCoord2f(Texture4[0].u, Texture4[0].v); glVertex3fv(v0);
					glTexCoord2f(Texture4[1].u, Texture4[1].v); glVertex3fv(v1);
					glTexCoord2f(Texture4[2].u, Texture4[2].v); glVertex3fv(v2);
					glTexCoord2f(Texture4[3].u, Texture4[3].v); glVertex3fv(v3);
					glEnd();
				}
			}
		}
	}

void CSphere::setRadius(float radius)
{
	r = radius;
	ReadVertex();
	ReadFace();
}

void CSphere::initial()
{
	gAlpha = 4, gBeta = 8;//面片夹角
	N1 = 180 / gAlpha, N2 = 360 / gBeta;//N1为纬度区域,N2为经度区域

	V = new CP3d[(N1 - 1) * N2 + 2];
	V1 = new CP3d[(N1 - 1) * N2 + 2];

	T = new CT2[(N1 - 1) * N2 + 2];
	T1 = new CT2[(N1 - 1) * N2 + 2];
	F = new CFace * [N1];//设置行
	for (int n = 0; n < N1; n++)
		F[n] = new CFace[N2];//设置列
}
