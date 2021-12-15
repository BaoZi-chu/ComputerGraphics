#include "pch.h"
#include "Fill.h"
#include "math.h"
#define ROUND(f) int(floor(f+0.5))//��������궨��

CFill::CFill(void)
{
	PNum = 0;
	P = NULL;
	pEdge = NULL;
	pHeadB = NULL;
	pHeadE = NULL;
}


CFill::~CFill(void)
{
	if (P != NULL)
	{
		delete[] P;
		P = NULL;
	}
	ClearMemory();
}

void CFill::SetPoint(CPi2* p, int m)
{
	P = new CPi2[m];//����һά��̬����
	for (int i = 0; i < m; i++)
	{
		P[i] = p[i];
	}
	PNum = m;
}

void CFill::CreateBucket()//����Ͱ��
{
	int yMin, yMax;
	yMin = yMax = P[0].y;
	for (int i = 0; i < PNum; i++)//���Ҷ���������ǵ���С�����ɨ����
	{
		if (P[i].y < yMin)
		{
			yMin = P[i].y;//ɨ���ߵ���Сֵ
		}
		if (P[i].y > yMax)
		{
			yMax = P[i].y;//ɨ���ߵ����ֵ
		}
	}
	for (int y = yMin; y <= yMax; y++)
	{
		if (yMin == y)//�����ɨ���ߵ���Сֵ
		{
			pHeadB = new CBucket;//����Ͱ��ͷ���
			pCurrentB = pHeadB;//pCurrentBΪCBucket��ǰ���ָ��
			pCurrentB->ScanLine = yMin;
			pCurrentB->pET = NULL;//û�����ӱ߱�
			pCurrentB->pNext = NULL;
		}
		else//����ɨ����
		{
			pCurrentB->pNext = new CBucket;//����Ͱ���������
			pCurrentB = pCurrentB->pNext;
			pCurrentB->ScanLine = y;
			pCurrentB->pET = NULL;
			pCurrentB->pNext = NULL;
		}
	}
}

void CFill::CreateEdge()//�����߱�
{
	for (int i = 0; i < PNum; i++)
	{
		pCurrentB = pHeadB;
		int j = (i + 1) % PNum;//�ߵĵ�2�����㣬P[i]��P[j]��Թ��ɱ�
		if (P[i].y < P[j].y)//�ߵ��յ������
		{
			pEdge = new CAET;
			pEdge->x = P[i].x;//����ET���ֵ
			pEdge->yMax = P[j].y;
			pEdge->k = (P[j].x - P[i].x) / (P[j].y - P[i].y);//����1/k
			pEdge->ps = P[i];//�󶨶������ɫ
			pEdge->pe = P[j];
			pEdge->pNext = NULL;
			while (pCurrentB->ScanLine != P[i].y)//��Ͱ��Ѱ�ҵ�ǰ�ߵ�yMin
			{
				pCurrentB = pCurrentB->pNext;//�Ƶ�yMin���ڵ�Ͱ���
			}
		}
		if (P[j].y < P[i].y)//�ߵ��յ������
		{
			pEdge = new CAET;
			pEdge->x = P[j].x;
			pEdge->yMax = P[i].y;
			pEdge->k = (P[i].x - P[j].x) / (P[i].y - P[j].y);
			pEdge->ps = P[i];
			pEdge->pe = P[j];
			pEdge->pNext = NULL;
			while (pCurrentB->ScanLine != P[j].y)
			{
				pCurrentB = pCurrentB->pNext;
			}
		}
		if (P[i].y != P[j].y)
		{
			pCurrentE = pCurrentB->pET;
			if (pCurrentE == NULL)
			{
				pCurrentE = pEdge;
				pCurrentB->pET = pCurrentE;
			}
			else
			{
				while (pCurrentE->pNext != NULL)
				{
					pCurrentE = pCurrentE->pNext;
				}
				pCurrentE->pNext = pEdge;
			}
		}
	}
}

void CFill::Gouraud(CDC* pDC)//�������
{
	CAET* pT1 = NULL, * pT2 = NULL;
	pHeadE = NULL;
	for (pCurrentB = pHeadB; pCurrentB != NULL; pCurrentB = pCurrentB->pNext)
	{
		for (pCurrentE = pCurrentB->pET; pCurrentE != NULL; pCurrentE = pCurrentE->pNext)
		{
			pEdge = new CAET;
			pEdge->x = pCurrentE->x;
			pEdge->yMax = pCurrentE->yMax;
			pEdge->k = pCurrentE->k;
			pEdge->ps = pCurrentE->ps;
			pEdge->pe = pCurrentE->pe;
			pEdge->pNext = NULL;
			AddEt(pEdge);
		}
		EtOrder();
		pT1 = pHeadE;
		if (pT1 == NULL)
		{
			return;
		}
		while (pCurrentB->ScanLine >= pT1->yMax)//�±��Ͽ�
		{
			CAET* pAETTEmp = pT1;
			pT1 = pT1->pNext;
			delete pAETTEmp;
			pHeadE = pT1;
			if (pHeadE == NULL)
				return;
		}
		if (pT1->pNext != NULL)
		{
			pT2 = pT1;
			pT1 = pT2->pNext;
		}
		while (pT1 != NULL)
		{
			if (pCurrentB->ScanLine >= pT1->yMax)//�±��Ͽ�
			{
				CAET* pAETTemp = pT1;
				pT2->pNext = pT1->pNext;
				pT1 = pT2->pNext;
				delete pAETTemp;
			}
			else
			{
				pT2 = pT1;
				pT1 = pT2->pNext;
			}
		}
		CRGB Ca, Cb, Cf;//Ca��Cb���������������ɫ��Cf����������������ɫ
		Ca = Interpolation(pCurrentB->ScanLine, pHeadE->ps.y, pHeadE->pe.y, pHeadE->ps.c, pHeadE->pe.c);
		Cb = Interpolation(pCurrentB->ScanLine, pHeadE->pNext->ps.y, pHeadE->pNext->pe.y, pHeadE->pNext->ps.c, pHeadE->pNext->pe.c);
		BOOL Flag = FALSE;
		double xb, xe;//ɨ���ߺ���Ч���ཻ����������յ�����
		for (pT1 = pHeadE; pT1 != NULL; pT1 = pT1->pNext)
		{
			if (Flag == FALSE)
			{
				xb = pT1->x;
				Flag = TRUE;
			}
			else
			{
				xe = pT1->x;
				for (double x = xb; x < xe; x++)//����ҿ�
				{
					Cf = Interpolation(x, xb, xe, Ca, Cb);
					pDC->SetPixel(ROUND(x), pCurrentB->ScanLine, RGB(Cf.red * 255, Cf.green * 255, Cf.blue * 255));
				}
				Flag = FALSE;
			}
		}
		for (pT1 = pHeadE; pT1 != NULL; pT1 = pT1->pNext)//�ߵ�������
		{
			pT1->x = pT1->x + pT1->k;
		}
	}
}

void CFill::AddEt(CAET* pNewEdge)//�ϲ�ET��
{
	CAET* pCE = pHeadE;
	if (pCE == NULL)
	{
		pHeadE = pNewEdge;
		pCE = pHeadE;
	}
	else
	{
		while (pCE->pNext != NULL)
		{
			pCE = pCE->pNext;
		}
		pCE->pNext = pNewEdge;
	}
}
void CFill::EtOrder()//�߱��ð�������㷨
{
	CAET* pT1 = NULL, * pT2 = NULL;
	int Count = 1;
	pT1 = pHeadE;
	if (NULL == pT1)
	{
		return;
	}
	if (NULL == pT1->pNext)//�����ET��û������ET��
	{
		return;//Ͱ���ֻ��һ���ߣ�����Ҫ����
	}
	while (NULL != pT1->pNext)//ͳ�ƽ��ĸ���
	{
		Count++;
		pT1 = pT1->pNext;
	}
	for (int i = 1; i < Count; i++)//ð������
	{
		pT1 = pHeadE;
		if (pT1->x > pT1->pNext->x)//��x��С��������
		{
			pT2 = pT1->pNext;
			pT1->pNext = pT1->pNext->pNext;
			pT2->pNext = pT1;
			pHeadE = pT2;
		}
		else
		{
			if (pT1->x == pT1->pNext->x)
			{
				if (pT1->k > pT1->pNext->k)//��б����С��������
				{
					pT2 = pT1->pNext;
					pT1->pNext = pT1->pNext->pNext;
					pT2->pNext = pT1;
					pHeadE = pT2;
				}
			}
		}
		pT1 = pHeadE;
		while (pT1->pNext->pNext != NULL)
		{
			pT2 = pT1;
			pT1 = pT1->pNext;
			if (pT1->x > pT1->pNext->x)//��x��С��������
			{
				pT2->pNext = pT1->pNext;
				pT1->pNext = pT1->pNext->pNext;
				pT2->pNext->pNext = pT1;
				pT1 = pT2->pNext;
			}
			else
			{
				if (pT1->x == pT1->pNext->x)
				{
					if (pT1->k > pT1->pNext->k)//��б����С��������
					{
						pT2->pNext = pT1->pNext;
						pT1->pNext = pT1->pNext->pNext;
						pT2->pNext->pNext = pT1;
						pT1 = pT2->pNext;
					}
				}
			}
		}
	}
}

CRGB CFill::Interpolation(double t, double t1, double t2, CRGB c1, CRGB c2)//���Բ�ֵ
{
	CRGB c;
	c = (t - t2) / (t1 - t2) * c1 + (t - t1) / (t2 - t1) * c2;
	return c;
}

void CFill::ClearMemory()//��ȫɾ������Ͱ��Ͱ����ı�
{
	DeleteAETChain(pHeadE);
	CBucket* pBucket = pHeadB;
	while (pBucket != NULL)// ���ÿһ��Ͱ
	{
		CBucket* pBucketTemp = pBucket->pNext;
		DeleteAETChain(pBucket->pET);
		delete pBucket;
		pBucket = pBucketTemp;
	}
	pHeadB = NULL;
	pHeadE = NULL;
}

void CFill::DeleteAETChain(CAET* pAET)
{
	while (pAET != NULL)
	{
		CAET* pAETTemp = pAET->pNext;
		delete pAET;
		pAET = pAETTemp;
	}
}