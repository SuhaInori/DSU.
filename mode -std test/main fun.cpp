/*
* �η�������stdģʽ����
*/


#include "D:/vc++/data/osuImitateGame/osuImitateGame/classLib.h"


int main() {
	initgraph(1280, 720, 1);

	gameMode *gameMdoe_1 = new mode_std("ϼ��.dsz");
	
	gameMdoe_1->gameStart();
	system("pause");
	closegraph();
}