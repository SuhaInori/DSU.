#pragma once
#include "libH.h"


//gameInitFile类   游戏配置文件读取
class gameInitFile {
public:
	char userName[10];
	int windowWidth;
	int windowHeight;
	int difficulty;
	int lv;
	int exp;
	void addExp(int exp);
	//读取配置文件
	gameInitFile();
	//imageLib图片库类
	~gameInitFile();
};


