#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <math.h>
#include <fstream>
#include <windows.h>	
class MapRander {
public:
	MapRander():key(0) {}
	//��������
	int MrMain();
private:
	float times;           //��ʼʱ��
	float timee;           //����ʱ��
	//float timing;          //���ļ��
	float offset;		   //��ǰ������ʱ��
	float bpm;             //bpm
	float timsd;		   //ÿ��ʱ����
	int subdivision;       //����ϸ��
	int key;			   //һά����
	int Dsr, mode, returnout;               //�жϵ������ܶ�;����ȷ�����ɼ���;�����á�

	char Creator[100];
	//�������
	int Rd(int Range, int MixVal);
	//�������
	void KeyOut();
	//ȫ�������
	void RandKey();
	//���������
	void Jack();
	void Tech();
	void Stream();
	void Speed();
};
