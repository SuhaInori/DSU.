#pragma once
#include "libH.h"


//gameInitFile��   ��Ϸ�����ļ���ȡ
class gameInitFile {
public:
	char userName[10];
	int windowWidth;
	int windowHeight;
	int difficulty;
	int lv;
	int exp;
	void addExp(int exp);
	//��ȡ�����ļ�
	gameInitFile();
	//imageLibͼƬ����
	~gameInitFile();
};


