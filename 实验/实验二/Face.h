#pragma once
#include "CT2.h"
#include "Vector3.h"

class CFace
{
public:
	CFace();
	virtual ~CFace();
	void SetNum(int vN);//设置小面的顶点数
	void SetFaceNormal(CP3d, CP3d, CP3d);//设置小面法矢量
public:
	int vN;          //小面的顶点数
	int *vI;         //小面的顶点索引
	CVector3 fNormal; //小面的法矢量
	CT2 *t;          //纹理顶点动态数组
};

