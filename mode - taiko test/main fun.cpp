#include "D:/vc++/data/osuImitateGame/osuImitateGame/classLib.h"
void draw_image(IMAGE& image, int x, int y, int w = -1, int h = -1);

int main() {
	mode_taiko *mc = new mode_taiko("test.dsz");
	initgraph(1280, 720,1);
	mc->gameStart();
	/*draw_image(mc->bg,0,100);
	draw_image(mc->Kdown[0], 44, 130);*/
}