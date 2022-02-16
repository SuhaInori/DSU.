#include "classLib.h"
long long timeset();
void draw_image(IMAGE& image, int x, int y, int w = -1, int h = -1);

mode_taiko::mode_taiko(string dszName) {
	DszLoad(dszName);
	loadimage(&drum[0], "./file/image/BlueDrum.png");
	loadimage(&drum[1], "./file/image/RedDrum.png");
	loadimage(&Ranking, "./file/image/ranking.png", 1280, 720);
	loadimage(&bg, "./file/image/taiko-bg.png");
	loadimage(&Kdown[0], "./file/image/keyut.png");
	loadimage(&Kdown[1], "./file/image/keyDRed.png");
	loadimage(&Kdown[2], "./file/image/KeyDBlue.png");
	rtSet[0] = true;
	rtSet[1] = true;
	for (int x = 0; x < 4; x++) {
		KeyState[x] = false;
	}
}

void mode_taiko::gameStart() {
	cleardevice();
	Sleep(2000);
	thread mS(&mode_taiko::musicStart, this);
	thread tm(&mode_taiko::timer, this);
	thread gm(&mode_taiko::gameIn, this);
	tm.join();
	gm.join();
	mS.join();
}

void mode_taiko::gameIn() {
	double delayed = 0.0;
	int index = 0;
	int stN = 0;
	int quantity = 0;
	int timebg, fm = 0;
	for (int x = 0; x < 30; x++) {
		dm[x].existence = false;
		dm[x].drumColor = false;
		dm[x].offset = 0;
	}
	//绘图窗口初始化
	setbkcolor(0);
	cleardevice();
	settextcolor(RGB(255, 255, 255));
	setcolor(RGB(255, 255, 255));
	long long begin = timeset();
	timebg = time;
	BeginBatchDraw();//开始双缓冲绘图
	while (gameStop) {
		cleardevice();
		draw_image(bg, 0, 100);
		DrumRefresh(quantity, index);
		if (stN = event_Feedback(quantity)) {
			break;
		}
		if (combo > maxcombo) {
			maxcombo = combo;
		}
		fm++;
		if (time - timebg >= 50) {
			long long end = timeset();
			delayed = (double)(end - begin) / (10000 * fm);
			begin = timeset();
			timebg = time;
			fm = 0;
		}
		testOutPut(delayed);
		FlushBatchDraw();
	}
	EndBatchDraw();
	if (stN) {
		return;
	}
	avg /= quantity;
	endGame();
}

void mode_taiko::DrumRefresh(int& quantity, int& index) {
	for (int d = 0; d < 30; d++) {
		if (dm[d].existence == false && index < objectNub) {
			dm[d].offset = dszP[index].offset;
			dm[d].drumColor = dszP[index].drum;
			dm[d].existence = true;
			index++;
		}
		else  if (dm[d].existence == true) {
			int cct = dm[d].offset - time+50;
			if (0 < cct && cct < 1280) {
				switch (dm[d].drumColor) {
				case 0:
					draw_image(drum[0], cct / DRUM_SPEED, 136); break;
				case 1:
					draw_image(drum[1], cct / DRUM_SPEED, 136); break;
				default:
					break;
				}
			}
		}
		if (time >= dm[d].offset + TAIKO_KE&&dm[d].existence){
			combo = 0;
			dm[d].existence = false;
			ms++;
			quantity++;
			acc = (double)((ex + pf) + gr * 0.66 + (gd + bd) * 0.33) / quantity;
			avg += time - dm[d].offset;
		}
	}
}

int	mode_taiko::event_Feedback(int& quantity) {
	if ((GetAsyncKeyState(192) & 0x8000 || GetAsyncKeyState(90) & 0x8000)) {
		if (!KeyState[0]) {
			judge(quantity, false);
		}
		draw_image(Kdown[2], 44, 130);
		KeyState[0] = true;
	}
	else if (!(GetAsyncKeyState(192) & 0x8000 || GetAsyncKeyState(90) & 0x8000)) {
		KeyState[0] = false;
	}
	if ((GetAsyncKeyState(49) & 0x8000 || GetAsyncKeyState(88) & 0x8000)) {
		if (!KeyState[1]) {
			judge(quantity, true);
		}
		draw_image(Kdown[1], 44, 130);
		KeyState[1] = true;
	}
	else if (!(GetAsyncKeyState(49) & 0x8000 || GetAsyncKeyState(88) & 0x8000)) {
		KeyState[1] = false;
	}
	if ((GetAsyncKeyState(106) & 0x8000 || GetAsyncKeyState(190) & 0x8000)) {
		if (!KeyState[2]) {
			judge(quantity, true);
		}
		draw_image(Kdown[1], 44, 130);
		KeyState[2] = true;
	}
	else if (!(GetAsyncKeyState(106) & 0x8000 || GetAsyncKeyState(190) & 0x8000)) {
		KeyState[2] = false;
	}
	if ((GetAsyncKeyState(109) & 0x8000 || GetAsyncKeyState(191) & 0x8000)) {
		if (!KeyState[3]) {
			judge(quantity, false);
		}
		draw_image(Kdown[2], 44, 130);
		KeyState[3] = true;
	}
	else if (!(GetAsyncKeyState(109) & 0x8000 || GetAsyncKeyState(191) & 0x8000)) {
		KeyState[3] = false;
	}
	if (GetAsyncKeyState(VK_ESCAPE)) {
		if (rtSet[0]) {
			rtTim = time;
			rtSet[0] = false;
		}
		if (time - rtTim >= 500) {
			remake = 0;
			gameStop = false;
			return 1;
		}
	}
	if (GetAsyncKeyState(0x52) || GetAsyncKeyState(111)) {
		if (rtSet[1]) {
			rtTim = time;
			rtSet[1] = false;
		}
		if (time - rtTim >= 500) {
			remake = 1;
			gameStop = false;
			return 1;
		}
	}
	return 0;
}

void mode_taiko::judge(int& quantity,bool color) {
	int tempt = 1500;
	int flag = 0;
	for (int x = 0; x < 30; x++) {
		if (dm[x].existence == true&&dm[x].drumColor==color) {
			int temp = dm[x].offset - time;
			if (temp < tempt) {
				tempt = temp;
				flag = x;
			}
		}
	}
	if (abs(dm[flag].offset - time) <= TAIKO_LIANG
		&& dm[flag].existence ) {
		ex++;
		combo++;
		quantity++;
		score += 100 + combo*2;
		dm[flag].existence = false;
		acc = (double)(ex+pf*0.5) / quantity;
	}
	else if (abs(dm[flag].offset - time) > TAIKO_LIANG
		&& abs(dm[flag].offset - time) <= TAIKO_KE
		&& dm[flag].existence ) {
		pf++;
		combo++;
		quantity++;
		score += 50 + combo*2;
		dm[flag].existence = false;
		acc = (double)(ex + pf * 0.5) / quantity;
	}
	else if (abs(dm[flag].offset - time) > TAIKO_KE &&
		abs(dm[flag].offset - time) <= TAIKO_MS
		&& dm[flag].existence ) {
		ms++;
		combo = 0;
		quantity++;
		dm[flag].existence = false;
		acc = (double)(ex + pf * 0.5) / quantity;
	}
	else {
		return;
	}
	avg += time - dm[flag].offset;
}

void mode_taiko::testOutPut(double delayed){
	setbkmode(TRANSPARENT);
	char dl[50];
	settextstyle(50, 0, "楷体");
	sprintf(dl, "%d", combo);
	outtextxy((114 - textwidth(dl)/2), 50, dl);
	sprintf(dl, "%d", score);
	outtextxy(1280 - textwidth(dl), 0, dl);
	sprintf(dl, "%.2lf %%", acc * 100);
	outtextxy((1280 - textwidth(dl)) / 2, 0, dl);
	settextstyle(20, 0, "楷体");
	sprintf(dl, "帧延时：%.4lf", delayed);
	outtextxy(0, 0, dl);
}

void mode_taiko::endGame(){
	char tr[50];
	cleardevice();
	putimage(0, 0, &Ranking);
	settextstyle(70, 0, "Segoe Script");
	setcolor(RGB(255, 174, 201));
	sprintf(tr, "良: %d", ex);
	outtextxy(50, 100, tr);
	sprintf(tr, "可: %d", pf);
	outtextxy(300, 100, tr);
	sprintf(tr, "不可: %d", ms);
	outtextxy(50, 260, tr);
	sprintf(tr, "%d", maxcombo);
	outtextxy(60, 430, tr);
	sprintf(tr, "%d", score);
	outtextxy(230, 20, tr);
	sprintf(tr, "%.2lf %%", acc * 100);
	outtextxy(260, 430, tr);
	sprintf(tr, "AVG:%.2lf", avg);
	outtextxy(100, 530, tr);
	settextstyle(50, 0, "楷体");
	setcolor(RGB(255, 0, 0));
	while (1) {
		if (GetAsyncKeyState(VK_ESCAPE)) {
			remake = 0;
			return;
		}
		if (GetAsyncKeyState(0x52)) {
			remake = 1;
			return;
		}
	}
}