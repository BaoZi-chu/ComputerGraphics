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

void CSphere::ReadVertex()//���
{
	double gAlpha1, gBeta1;
	//���㱱��������

	V[0].x = 0, V[0].y = r, V[0].z = 0;
	V1[0].x = 200, V1[0].y = r - 60, V1[0].z = 200;

	T[0].u = 0; T[0].v = 0;//����
	T1[0].u = 0; T1[0].v = 0;//����

	//����ѭ�����������ϵĵ�����
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
	//�����ϼ�������

	V[(N1 - 1) * N2 + 1].x = 0, V[(N1 - 1) * N2 + 1].y = -r, V[(N1 - 1) * N2 + 1].z = 0;
	T[(N1 - 1) * N2 + 1].u = 0; T[(N1 - 1) * N2 + 1].v = 0;//����

	V1[(N1 - 1) * N2 + 1].x = 200, V1[(N1 - 1) * N2 + 1].y = -r + 60, V1[(N1 - 1) * N2 + 1].z = 200;
	T1[(N1 - 1) * N2 + 1].u = 0; T1[(N1 - 1) * N2 + 1].v = 0;//����


}

void CSphere::ReadFace()//�������
{

	for (int j = 0; j < N2; j++)//���챱����������Ƭ
	{
		int tempj = j + 1;
		if (tempj == N2) tempj = 0;//��Ƭ����β����
		int NorthIndex[3];//������������Ƭ����������
		NorthIndex[0] = 0;
		NorthIndex[1] = j + 1;
		NorthIndex[2] = tempj + 1;
		F[0][j].SetNum(3);
		for (int k = 0; k < F[0][j].vN; k++)
			F[0][j].vI[k] = NorthIndex[k];
	}

	for (int i = 1; i < N1 - 1; i++)//���������ı�����Ƭ
	{
		for (int j = 0; j < N2; j++)
		{
			int tempi = i + 1;
			int tempj = j + 1;
			if (tempj == N2) tempj = 0;
			int BodyIndex[4];//�����ı�����Ƭ����������
			BodyIndex[0] = (i - 1) * N2 + j + 1;
			BodyIndex[1] = (tempi - 1) * N2 + j + 1;
			BodyIndex[2] = (tempi - 1) * N2 + tempj + 1;
			BodyIndex[3] = (i - 1) * N2 + tempj + 1;
			F[i][j].SetNum(4);
			for (int k = 0; k < F[i][j].vN; k++)
				F[i][j].vI[k] = BodyIndex[k];
		}
	}

	for (int j = 0; j < N2; j++)//�����ϼ���������Ƭ
	{
		int tempj = j + 1;
		if (tempj == N2) tempj = 0;
		int SouthIndex[3];//�ϼ���������Ƭ����������
		SouthIndex[0] = (N1 - 2) * N2 + j + 1;
		SouthIndex[1] = (N1 - 1) * N2 + 1;
		SouthIndex[2] = (N1 - 2) * N2 + tempj + 1;
		F[N1 - 1][j].SetNum(3);
		for (int k = 0; k < F[N1 - 1][j].vN; k++)
			F[N1 - 1][j].vI[k] = SouthIndex[k];
	}
}


void CSphere::Draw()//��������
{
	float v0[3];//�����붥�������ζ�������
	float v1[3];
	float v2[3];
	float v3[3];
	CT2 Texture3[3];//�����붥����������������
	float Normal3[3];//�����붥�������η�ʸ������
	CPi3 Point4[4];//�����ı��ζ�������
	CT2 Texture4[4];//�����ı�����������

	for (int i = 0; i < N1; i++)
	{
		for (int j = 0; j < N2; j++)
		{
			
			F[i][j].SetFaceNormal(V[F[i][j].vI[0]], V[F[i][j].vI[1]], V[F[i][j].vI[2]]);//����С��Ƭ��ʸ��

			F[i][j].fNormal.Normalize();//��λ����ʸ��

				if (3 == F[i][j].vN)//������������Ƭ
				{
						
					double tempi = i + 1, tempj = j + 1;//����������Ƭ�������⴦��
					Texture3[0].u = gBeta * (j) / 360.0; Texture3[0].v = (1.0 - gAlpha * i / 180.0);
					Texture3[1].u = gBeta * (j) / 360.0; Texture3[1].v = (1.0 - gAlpha * tempi / 180.0);
					Texture3[2].u = gBeta * tempj / 360.0; Texture3[2].v = (1.0 - gAlpha * i / 180.0);
					//������������Ƭ
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
				else//�����ı�����Ƭ
				{
					for (int m = 0; m < F[i][j].vN; m++)
					{
						//Normal4[m] = CVector3(V[F[i][j].vI[m]]);
						Texture4[m] = T[F[i][j].vI[m]];
					}
					if (N2 - 1 == j)//����ͼ������Ľӷ�
					{
						Texture4[2].u = 1.0;
						Texture4[3].u = 1.0;
					}
					//�����Ǹ��ݵ������������㷨
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
	gAlpha = 4, gBeta = 8;//��Ƭ�н�
	N1 = 180 / gAlpha, N2 = 360 / gBeta;//N1Ϊγ������,N2Ϊ��������

	V = new CP3d[(N1 - 1) * N2 + 2];
	V1 = new CP3d[(N1 - 1) * N2 + 2];

	T = new CT2[(N1 - 1) * N2 + 2];
	T1 = new CT2[(N1 - 1) * N2 + 2];
	F = new CFace * [N1];//������
	for (int n = 0; n < N1; n++)
		F[n] = new CFace[N2];//������
}
