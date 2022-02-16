/*
* 次方案用于std模式测试
*/


#include "D:/vc++/data/osuImitateGame/osuImitateGame/classLib.h"


int main() {
	initgraph(1280, 720, 1);

	gameMode *gameMdoe_1 = new mode_std("霞光.dsz");
	
	gameMdoe_1->gameStart();
	system("pause");
	closegraph();
}