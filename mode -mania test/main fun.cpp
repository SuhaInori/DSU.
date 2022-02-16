#include "D:/vc++/data/osuImitateGame/osuImitateGame/classLib.h"



int main() {
	initgraph(1280, 720, 1);

	gameMode* gameMdoe_1 = new mode_mania("Ï¼¹â.dsz");

	gameMdoe_1->gameStart();
	Sleep(1000);
	system("pause");
	closegraph();
}