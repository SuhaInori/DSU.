#pragma once
#include "libH.h"

class fileInitLib {
public:
	IMAGE bg[3];
	IMAGE start[50];
	IMAGE menu;
	IMAGE options;
	IMAGE kanbanNiang;
	IMAGE menuP[3][2];
	IMAGE gameBg;
	IMAGE mode[4];
	IMAGE SongBG;
	IMAGE back;
	IMAGE head_portrait;
	IMAGE frame;
	IMAGE inori;
	fileInitLib() {}
	//图片库初始化 
	void initfile(int w, int h );   
	void loadbg(int w, int h);
	void loadkanbanNiang();
	void loadstart();
	void loadmenu();
	void loadoptions(int w, int h);
	void loadgamebg(int w, int h);
	void loadmode(); 
	void loadSongBG();
	void loadback();
	void loadhead_portrait();
	void loadframe();
	void loadinori();
	//析构函数声明
	~fileInitLib();
};
