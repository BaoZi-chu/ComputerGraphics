#include "pch.h"
#include "Face.h"

CFace::CFace()
{
	vI = NULL;
	t = NULL;
	fNormal = CVector3(CP3d(0.0, 0.0, 1.0));
}

CFace::~CFace()
{
	if (vI != NULL)
	{
		delete[]vI;
		vI = NULL;
	}
	if (t != NULL)
	{
		delete[] t;
		t = NULL;
	}
}

void CFace::SetNum(int vN)
{
	this->vN = vN;
	vI = new int[vN];
	t = new CT2[vN];
}

void CFace::SetFaceNormal(CP3d pt0, CP3d pt1, CP3d pt2)//计算小面法矢量
{
	CVector3 V01(pt0, pt1);
	CVector3 V02(pt0, pt2);
	fNormal = Cross(V01, V02);
}