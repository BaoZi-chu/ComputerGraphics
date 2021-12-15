#include "pch.h"
#include "CHexagon.h"
#include "math.h"//������ѧͷ�ļ�
#define  PI 3.1415926//PI�ĺ궨��
#define Round(d) int(floor(d+0.5))//��������궨��

CHexagon::CHexagon()
{
	n = 9;
}

CHexagon::~CHexagon()
{
}

void CHexagon::ReadPoint()//���
{
	int r = 300;
	double w = PI / 180;
	int theta = 40;
	double bata = 0;
	for (int i = 0; i < 9; i++) {
		bata = (i - 0.5) * theta  *w;
		P[i].x = round(r * cos(bata));
		P[i].y = round(r * sin(bata));
	}
	P[0].c = CRGB(1.0, 0.0, 0.0);
	P[1].c = CRGB(1.0, 1.0, 0.0);
	P[2].c = CRGB(0.0, 1.0, 0.0);
	P[3].c = CRGB(0.0, 1.0, 1.0);
	P[4].c = CRGB(0.0, 0.0, 1.0);
	P[5].c = CRGB(1.0, 0.0, 1.0);
	P[6].c = CRGB(1.0, 1.0, 1.0);
	P[7].c = CRGB(0.0, 0.0, 0.0);
	P[8].c = CRGB(1.0, 1.0, 0.0);
}

void CHexagon::DrawPolygon(CDC* pDC)//���ƶ���α߽�
{
	CLine* line = new CLine;
	CP2 t;
	for (int i = 0; i <n ; i++)//���ƶ����
	{
		if (i == 0)
		{
			line->MoveTo(pDC, P[i]);
			t = P[i];
		}
		else
		{
			line->LineTo(pDC, P[i]);
		}
	}
	line->LineTo(pDC, t);//�պ϶����
	delete line;
}

void CHexagon::FillPolygon(CDC* pDC)//�������
{
	for (int i = 0; i < n; i++)
	{
		P0[i].x = P[i].x;
		P0[i].y = Round(P[i].y);
		P0[i].c = P[i].c;
	}
	CFill* fill = new CFill;      //��̬�����ڴ� 
	fill->SetPoint(P0, n);       //��ʼ��Fill����
	fill->CreateBucket();       //����Ͱ��
	fill->CreateEdge();         //�����߱�
	fill->Gouraud(pDC);         //�������
	delete fill;                //�����ڴ�
}
