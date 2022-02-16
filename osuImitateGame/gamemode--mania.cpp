#pragma once
#include "classLib.h"
long long timeset();
void draw_image(IMAGE& image, int x, int y, int w = -1, int h = -1);

mode_mania::mode_mania(string dszName) {
	DszLoad(dszName);
	loadimage(&note, "./file/image/note.png");
	loadimage(&Ranking, "./file/image/ranking-Mania.png", 1280, 720);
	loadimage(&track, "./file/image/KEY-.PNG");
	rtSet[0] = true;
	rtSet[1] = true;
	error = new Distribution[objectNub];
	errorIndex = 0;
	for (int x = 0; x < 4; x++) {
		KeyState[x] = false;
	}
}

void mode_mania::gameStart() {
	cleardevice();
	Sleep(2000);
	thread mS(&mode_mania::musicStart, this);
	thread tm(&mode_mania::timer, this);
	thread gm(&mode_mania::gameIn, this);
	tm.join();
	gm.join();
	mS.join();
}

void mode_mania::gameIn() {
	//帧延时计数
	double delayed=0.0;
	int index = 0;
	int stN=0;
	int keyCd[4] = { 0 };
	//击中次数
	int quantity = 0;
	int timebg, fm = 0;
	//note初始化
	for (int x = 0; x < 50; x++) {
		np[x].existence = false;
		np[x].key = 0;
		np[x].offset = 0;
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
		draw_image(track, 420, 0);
		npRefresh(quantity, index);
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

void mode_mania::npRefresh(int& quantity, int& index) {
	for (int p = 0; p < 50; p++) {
		if (np[p].existence == false && index < objectNub) {
			np[p].offset = dszP[index].offset;
			np[p].key = dszP[index].key;
			np[p].existence = true;
			index++;
		}
		else  if (np[p].existence == true) {
			int cct = np[p].offset - time;
			if (0 < cct && cct < 700) {
				draw_image(note, 420+110*np[p].key, 700-abs(time-np[p].offset)* DOWN_SPEED);
			}
		}
		if (time >= np[p].offset + BD_MANIA&& np[p].existence) {
			combo = 0;
			np[p].existence = false;
			ms++;
			quantity++;
			acc = (double)((ex+pf) + gr * 0.66 + (gd+bd) * 0.33) / quantity;
			avg+=error[errorIndex].error = time - np[p].offset;
			error[errorIndex].time = time;
			errorIndex++;
		}
	}
}

int mode_mania::event_Feedback(int& quantity) {
	int flag[4] = { 0 }, tempt[4] = { 1500 };
	if ((GetAsyncKeyState(192)&0x8000 || GetAsyncKeyState(90) & 0x8000)&&KeyState[0]==false) {
		judge(0, quantity);
		KeyState[0] = true;
	}
	else if (!(GetAsyncKeyState(192) & 0x8000 || GetAsyncKeyState(90) & 0x8000)) {
		KeyState[0] = false;
	}
	if ((GetAsyncKeyState(49) & 0x8000 || GetAsyncKeyState(88) & 0x8000)&&KeyState[1] == false) {
		judge(1,  quantity);
		KeyState[1] = true;
	}
	else if(!(GetAsyncKeyState(49) & 0x8000 || GetAsyncKeyState(88) & 0x8000)) {
		KeyState[1] = false;
	}
	if ((GetAsyncKeyState(106) & 0x8000 || GetAsyncKeyState(190) & 0x8000)&&KeyState[2] == false) {
		judge(2, quantity);
		KeyState[2] = true;
	}
	else if(!(GetAsyncKeyState(106) & 0x8000 || GetAsyncKeyState(190) & 0x8000)) {
		KeyState[2] = false;
	}
	if ((GetAsyncKeyState(109) & 0x8000 || GetAsyncKeyState(191) & 0x8000)&&KeyState[3] == false) {
		judge(3, quantity);
		KeyState[3] = true;
	}
	else if(!(GetAsyncKeyState(109) & 0x8000 || GetAsyncKeyState(191) & 0x8000)) {
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
	 if (GetAsyncKeyState(0x52)|| GetAsyncKeyState(111)) {
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

void mode_mania::judge(int key ,int & quantity) {
	int tempt=1500; 
	int flag=0;
	for (int x = 0; x < 50; x++) {
		if (np[x].key == key && np[x].existence == true) {
			int temp = np[x].offset - time;
			if (temp < tempt) {
				tempt = temp;
				flag = x;
			}
		}
	}
	if (abs(np[flag].offset - time) <= EX_MANIA
		&& np[flag].existence) {
		ex++;
		combo++;
		quantity++;
		score += 300+combo;
		np[flag].existence = false;
		acc = (double)((ex + pf) + gr * 0.66 + (gd + bd) * 0.33) / quantity;
	}
	else if (abs(np[flag].offset - time) >= EX_MANIA 
		&&abs(np[flag].offset - time) <= PF_MANAI
		&& np[flag].existence) {
		pf++;
		combo++;
		quantity++;
		score += 200 + combo;
		np[flag].existence = false;
		acc = (double)((ex + pf) + gr * 0.66 + (gd + bd) * 0.33) / quantity;
	}
	else if (abs(np[flag].offset - time) >= PF_MANAI 
		&&abs(np[flag].offset - time) <= GR_MANIA 
		&& np[flag].existence) {
		gr++;
		combo++;
		quantity++;
		score += 100 + combo;
		np[flag].existence = false;
		acc = (double)((ex + pf) + gr * 0.66 + (gd + bd) * 0.33) / quantity;
	}
	else if (abs(np[flag].offset - time) >= GR_MANIA &&
		abs(np[flag].offset - time) <= GD_MANIA 
		&& np[flag].existence) {
		gd++;
		combo++;
		quantity++;
		score += 50 + combo;
		np[flag].existence = false;
		acc = (double)((ex + pf) + gr * 0.66 + (gd + bd) * 0.33) / quantity;
	}
	else if (abs(np[flag].offset - time) >= GD_MANIA &&
		abs(np[flag].offset - time) <= BD_MANIA 
		&& np[flag].existence) {
		bd++;
		combo++;
		quantity++;
		np[flag].existence = false;
		acc = (double)((ex + pf) + gr * 0.66 + (gd + bd) * 0.33) / quantity;
	}
	else if (abs(np[flag].offset - time) >= BD_MANIA &&
		abs(np[flag].offset - time) <= MS_MANIA 
		&& np[flag].existence) {
		ms++;
		combo = 0;
		quantity++;
		np[flag].existence = false;
		acc = (double)((ex + pf) + gr * 0.66 + (gd + bd) * 0.33) / quantity;
	}
	else {
		return;
	}
	avg += error[errorIndex].error = time - np[flag].offset;
	error[errorIndex].time = time;
	errorIndex++;
}

void mode_mania::testOutPut(double delayed) {
	setbkmode(TRANSPARENT);
	char dl[50];
	settextstyle(50, 0, "楷体");
	sprintf(dl, "%d", combo);
	outtextxy((1280 - textwidth(dl))/2, 200, dl);
	sprintf(dl, "%d", score);
	outtextxy(1280 - textwidth(dl), 0, dl);
	sprintf(dl, "%.2lf %%", acc * 100);
	outtextxy((1280 - textwidth(dl)) / 2, 0, dl);
	settextstyle(20, 0, "楷体");
	sprintf(dl, "帧延时：%.4lf", delayed);
	outtextxy(0, 0, dl);
}

void mode_mania::endGame() {
	char tr[50];
	cleardevice();
	putimage(0, 0, &Ranking);
	settextstyle(70, 0, "Segoe Script");
	setcolor(RGB(255, 174, 201));
	sprintf(tr, "EX: %d", ex);
	outtextxy(50, 100, tr);
	sprintf(tr, "PF: %d", pf);
	outtextxy(300, 100, tr);
	sprintf(tr, "GR: %d", gr);
	outtextxy(50, 180, tr);
	sprintf(tr, "GD: %d", gd);
	outtextxy(300, 180, tr);
	sprintf(tr, "BD: %d", bd);
	outtextxy(50, 260, tr);
	sprintf(tr, "MS: %d", ms);
	outtextxy(300, 260, tr);
	sprintf(tr, "%d", maxcombo);
	outtextxy(60, 430, tr);
	sprintf(tr, "%d", score);
	outtextxy(230, 20, tr);
	sprintf(tr, "%.2lf %%", acc * 100);
	outtextxy(260, 430, tr);
	sprintf(tr, "AVG:%.2lf", avg);
	outtextxy(100, 530, tr);
	settextstyle(50, 0, "楷体");
	DistributionMap();
}

void mode_mania::DistributionMap() {
	setcolor(RGB(0, 162, 232));
	line(560, 460, 1280, 460);
	line(560, 490, 1280, 490);
	setcolor(RGB(255, 242, 0));
	line(560, 441, 1280, 441);
	line(560, 509, 1280, 509);
	setcolor(RGB(0, 255, 0));
	line(560, 410, 1280, 410);
	line(560, 540, 1280, 540);
	setcolor(RGB(0, 0, 255));
	line(560, 380, 1280, 380);
	line(560, 570, 1280, 570);
	setcolor(RGB(255, 128, 255));
	line(560, 350, 1280, 350);
	line(560, 600, 1280, 600);
	setcolor(RGB(255, 0, 0));
	line(560, 320, 1280, 320);
	line(560, 630, 1280, 630);
	setcolor(RGB(255, 255, 255));
	settextstyle(20, 0, "楷体");
	outtextxy(560, 320, "过早：-155ms");
	outtextxy(560, 610, "过迟：+155ms");
	for (int x = 0; x < errorIndex; x++) {
		setlinestyle(PS_SOLID, 2);
		if (abs(error[x].error)<= EX_MANIA) {
			setcolor(RGB(0, 162, 232));
			circle(560 + error[x].time * 920 / length, 475 + error[x].error, 1);
		}
		else if (abs(error[x].error) > EX_MANIA && abs(error[x].error) <= PF_MANAI) {
			setcolor(RGB(255, 242, 0));
			circle(560 + error[x].time * 920 / length, 475 + error[x].error, 1);
		}
		else if (abs(error[x].error) > PF_MANAI && abs(error[x].error) <= GR_MANIA) {
			setcolor(RGB(0, 255, 0));
			circle(560 + error[x].time * 920 / length, 475 + error[x].error, 1);
		}
		else if (abs(error[x].error) > GR_MANIA && abs(error[x].error) <= GD_MANIA) {
			setcolor(RGB(0, 0, 255));
			circle(560 + error[x].time * 920 / length, 475 + error[x].error, 1);
		}
		else if (abs(error[x].error) > GD_MANIA && abs(error[x].error) <= BD_MANIA) {
			setcolor(RGB(255, 128, 255));
			circle(560 + error[x].time * 920 / length, 475 + error[x].error, 1);
		}
		else if (abs(error[x].error) > BD_MANIA && abs(error[x].error) <= MS_MANIA) {
			setcolor(RGB(255, 0, 0));
			circle(560 + error[x].time * 920 / length, 475 + error[x].error, 1);
		}
	}
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

mode_mania::~mode_mania() {
	if (!error) {
		delete[] error;
	}
	error = NULL;
}