/*                      fileInitLib类函数定义
*																				---------------inori
* initfile
* loadbg
* loadkanbanNiang
* loadstart
* loadmenu
* loadoptions
* loadgamebg
* loadmode
*/

#include "fileInitLib.h"
void fileInitLib::initfile(int w, int h) {
	loadstart();
	loadkanbanNiang();
	loadbg(w, h);
	loadmenu();
	loadoptions(w, h);
	loadgamebg(w, h);
	loadmode();
	loadSongBG();
	loadback();
	loadhead_portrait();
	loadframe();
	loadinori();
}
void fileInitLib::loadbg(int w, int h) {
	loadimage(&bg[0], "./file/image/bg.png", w, h, false);
	loadimage(&bg[1], "./file/image/bg0.png", w, h, false);
	loadimage(&bg[2], "./file/image/bg1.png", w, h, false);
}
void fileInitLib::loadkanbanNiang() {
	loadimage(&kanbanNiang, "./file/image/kanbanliang.png");
}
void fileInitLib::loadstart() {
	for (int round = 0; round < 50; round++) {
		loadimage(&start[round], "./file/image/start.png", 500 - 10 * round, 500 - 10 * round, false);
	}
}
void fileInitLib::loadmenu() {
	loadimage(&menu, "./file/image/menu.png");
	for (int round1 = 0; round1 < 3; round1++) {
		for (int round2 = 0; round2 < 2; round2++) {
			SetWorkingImage(&menu);
			getimage(&menuP[round1][round2], round2 * 300, round1 * 100, 300, 100);
		}
	}
	SetWorkingImage();
}
void fileInitLib::loadoptions(int w, int h) {
	loadimage(&options, "./file/image/options.png", (400 / 720) * w, h, false);
}
void fileInitLib::loadgamebg(int w, int h) {
	loadimage(&gameBg, "./file/image/gmbg.png", w, h, false);
}
void fileInitLib::loadmode() {
	loadimage(&mode[0], "./file/image/gamemodSTD.png");
	loadimage(&mode[1], "./file/image/gamemodMANIA.png");
	loadimage(&mode[2], "./file/image/gamemodCATCH.png");
	loadimage(&mode[3], "./file/image/gamemodTAIKO.png");
}

void fileInitLib::loadSongBG(){
	loadimage(&SongBG, "./file/image/sbg.png");
}
void fileInitLib::loadback() {
	loadimage(&back, "./file/image/back.png");
}
void fileInitLib::loadhead_portrait() {
	loadimage(&head_portrait, "./file/user/head_portrait.png",100,100,false);
}
void fileInitLib::loadframe() {
	loadimage(&frame, "./file/image/frame.png",110,110,false);
}
void fileInitLib::loadinori() {
	loadimage(&inori, "./file/image/inori.png", 240, 400, false);
}
fileInitLib::~fileInitLib() {
}