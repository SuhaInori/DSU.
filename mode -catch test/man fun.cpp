#include "D:/vc++/data/osuImitateGame/osuImitateGame/classLib.h"


int main() {
	initgraph(1280, 720, 1);
	gameMode *md = new mode_catch("test.dsz");
	md->gameStart();
	system("pause");
}