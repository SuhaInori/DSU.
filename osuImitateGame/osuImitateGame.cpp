/*			main
* -------------------------
* |@version |  -1.0		  |
* |@auther  |  inori	  |
* |@date    |  2022.1.25  |
* -------------------------
*/
#pragma once
#include "fileInitLib.h"
#include "gameInitFile.h"
#include "DirectoryAcquisition.h"
#include "classLib.h"
void startUi(IMAGE* kanbanNiang, IMAGE* startImage, IMAGE* bg, int windowsW, int windowsH);
void menuUi(IMAGE* kanbanNiang, IMAGE(*menu)[2], IMAGE* start, IMAGE* bg,  IMAGE* options, int windowsW, int windowsH);
modeAndSongChoice gameStart(IMAGE* gamebg, IMAGE* mode,IMAGE *sb,IMAGE *back,IMAGE *hp, IMAGE* frame, IMAGE* inori, DirectoryAcquisition*  dszF, int windW, int windH);

gameInitFile gifile;
fileInitLib FileLib;
HWND window;
RECT rectangleW;
POINT mouP;
time_t t;
DirectoryAcquisition dszF;
modeAndSongChoice msC;

void gameInit() {
	initgraph(gifile.windowWidth, gifile.windowHeight);
	setbkcolor(RGB(0, 0, 0));
	cleardevice();
	window = FindWindow(NULL, _T("osuImitateGame"));
	FileLib.initfile(gifile.windowWidth, gifile.windowHeight);
}

int main() {
	bool remake=true;
	t = time(NULL);
	gameInit();
	gameMode* gameInto = NULL;
	startUi(&FileLib.kanbanNiang,FileLib.start,FileLib.bg ,gifile.windowWidth, gifile.windowHeight);
	back:while (true){
		//主菜单界面
		menuUi(&FileLib.kanbanNiang, FileLib.menuP, FileLib.start, FileLib.bg, &FileLib.options, gifile.windowWidth, gifile.windowHeight);
		while (true) {
			//选歌界面
			msC = gameStart(&FileLib.gameBg, FileLib.mode, &FileLib.SongBG, &FileLib.back, &FileLib.head_portrait, &FileLib.frame, &FileLib.inori, &dszF, gifile.windowWidth, gifile.windowHeight);
			remake = true;
			while (remake){
				setbkcolor(0);
				//创建模式1：std
				if (msC.mode == 0) {
					gameInto = new mode_std(msC.dir);
					gameInto->gameStart();
				}
				//创建模式2：mania
				else if (msC.mode == 1) {
					gameInto = new mode_mania(msC.dir);
					gameInto->gameStart();
				}
				//创建模式3：catch
				else if (msC.mode == 2) {
					gameInto = new mode_catch(msC.dir);
					gameInto->gameStart();
				}
				//创建模式4：taiko
				else if (msC.mode == 3) {
					gameInto = new mode_taiko(msC.dir);
					gameInto->gameStart();
				}
				//返回主菜单
				else if (msC.mode == 4) {
					goto back;
				}
				if (msC.mode !=4) {
					if (gameInto != NULL) {
						remake = gameInto->remake;
						delete gameInto;
					}
					//delete gameInto;
					gameInto = NULL;
				}
			}
			setbkcolor(RGB(254, 216, 185));
		}
	}
	closegraph();
}