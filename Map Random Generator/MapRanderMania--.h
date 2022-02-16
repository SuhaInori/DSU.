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
	//启动函数
	int MrMain();
private:
	float times;           //起始时间
	float timee;           //结束时间
	//float timing;          //节拍间隔
	float offset;		   //当前拍所在时间
	float bpm;             //bpm
	float timsd;		   //每拍时间间隔
	int subdivision;       //节拍细分
	int key;			   //一维键型
	int Dsr, mode, returnout;               //判断叠、切密度;用于确定生成键型;返回用。

	char Creator[100];
	//随机函数
	int Rd(int Range, int MixVal);
	//输出键型
	void KeyOut();
	//全随机键型
	void RandKey();
	//键型型输出
	void Jack();
	void Tech();
	void Stream();
	void Speed();
};
