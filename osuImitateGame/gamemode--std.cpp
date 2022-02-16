#include "classLib.h"
void textDisplay(double& acc, int& combo, int& score, double& delayed);
void draw_image(IMAGE& image, int x, int y, int w = -1, int h = -1);
long long timeset();

mode_std::mode_std(string dszName) {
	DszLoad(dszName);
	loadimage(&clc, "./file/image/circle.png");
	loadimage(&Ranking, "./file/image/ranking.png", 1280, 720);
	speed = 10;
}
//std模式游戏入口
void mode_std::gameIn() {
	int index = 0;
	//击中次数
	int quantity=0;
	//帧延时计数
	double delayed;
	int rtvalue=-1,drawvalue_bg=0,drawvalue;
	int stX, stY,stP,stN=0;
	int timebg,fm=0;
	for (int x = 0; x < 10; x++) {
		cc[x].existence = false;
	}
	setbkcolor(0);
	cleardevice();
	settextcolor(RGB(255, 255, 255));
	setcolor(RGB(255, 255, 255));
	long long begin = timeset();
	timebg = time;
	BeginBatchDraw();
	while (gameStop){
		cleardevice();
		ccRefresh(quantity,index);//重置cc
		if (time < dszP[objectNub-1].offset) {
			stN = event_Feedback(quantity, rtvalue);
		}
		drawStrike(rtvalue,drawvalue_bg,drawvalue,stX,stY,stP,stN);
		rtvalue = -1;
		if (combo > maxcombo) {
			maxcombo = combo;
		}
		fm++;
		if (time - timebg >= 50) {
			long long end = timeset();
			delayed = (double)(end - begin) / (10000*fm);
			begin = timeset();
			timebg = time;
			fm = 0;
		}
		textDisplay(acc, combo, score, delayed);
		FlushBatchDraw();
	}
	EndBatchDraw();
	if (stN == 2) {
		time = length - 200;
		return;
	}
	avg /= quantity;
	endGame();
}

void mode_std::gameStart() {
		cleardevice();
		Sleep(2000);
		thread mS(&mode_std::musicStart, this);
		thread tm(&mode_std::timer, this);
		thread gm(&mode_std::gameIn, this);
		tm.join();
		gm.join();
		mS.join();
}

void mode_std::endGame() {
	char tr[50];
	cleardevice();
	putimage(0, 0, &Ranking);
	settextstyle(70, 0, "Segoe Script");
	setcolor(RGB(255, 174, 201));
	sprintf(tr, "EX: %d", ex);
	outtextxy(50,100, tr);
	sprintf(tr, "GR: %d", gr);
	outtextxy(250, 100, tr);
	sprintf(tr, "BD: %d", bd);
	outtextxy(50, 250, tr);
	sprintf(tr, "MS: %d", ms);
	outtextxy(250, 250, tr);
	sprintf(tr, "%d", maxcombo);
	outtextxy(60, 430, tr);
	sprintf(tr, "%d", score);
	outtextxy(230, 20, tr);
	sprintf(tr, "%.2lf %%", acc*100);
	outtextxy(260, 430, tr);
	sprintf(tr, "AVG:%.2lf", avg);
	outtextxy(100, 530, tr);
	settextstyle(50, 0, "楷体");
	setcolor(RGB(255, 255, 255));
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

void mode_std::ccRefresh(int& quantity, int &index) {
	for (int p = 0; p < 10; p++) {
		if (cc[p].existence==false&&index< objectNub) {
			cc[p].offset = dszP[index].offset;
			cc[p].addx = dszP[index].x;
			cc[p].addy = dszP[index].y;
			cc[p].existence = true;
			index++;
		}
		else  if (cc[p].existence == true) {
			int cct;
			cct = cc[p].offset - time;
			if (0 < cct && cct < AR) {
				draw_image(clc, cc[p].addx - 64, cc[p].addy - 64);
				circle(cc[p].addx, cc[p].addy, 64 + cct / speed);
			}
		}
		if (time >= cc[p].offset+ BD_STD&&cc[p].existence) {
			combo = 0;
			cc[p].existence = false;
			ms++;
			quantity++;
			avg += time - cc[p].offset;
			acc = (double)(ex + gr * 0.66 + bd * 0.33) / quantity;
		}
	}
}

int mode_std::event_Feedback(int & quantity,int & rtvalue) {
	ExMessage msG;
	int flag=0,tempt=1500;
	peekmessage(&msG,EM_MOUSE);
	if (msG.lbutton|| GetAsyncKeyState(0x58)||GetAsyncKeyState(0x5A)) {
		for (int x = 0; x < 10; x++) {
			if (cc[x].existence == true) {
				int temp = cc[x].offset - time;
				if (temp < tempt) {
					tempt = temp;
					flag = x;
					
				}
			}	
		}
		if (msG.x > (cc[flag].addx - 64) 
			&& msG.x<(cc[flag].addx + 64) 
			&& msG.y>(cc[flag].addy - 64) 
			&& msG.y < (cc[flag].addy + 64)
			&&time<=dszP[objectNub-1].offset) {
			if (abs(cc[flag].offset - time) <= EX_STD) {
				ex++;
				combo++;
				quantity++;
				score += combo * 300;
				rtvalue = flag;
			}
			else if (abs(cc[flag].offset - time) <= GR_STD 
				&& abs(cc[flag].offset - time) >= EX_STD) {
				gr++; 
				combo++;
				quantity++;
				score += combo * 200;
				rtvalue = 10 + flag;
			}
			else if (abs(cc[flag].offset - time) >= GR_STD 
				&& abs(cc[flag].offset - time) <= BD_STD) {
				bd++;
				combo++;
				quantity++;
				score += combo * 50;
				rtvalue = 20 + flag;
			}
			else if (abs(cc[flag].offset - time) >= BD_STD 
				&& abs(cc[flag].offset - time) <= MS_STD) {
				ms++;
				quantity++;
				combo = 0;
				rtvalue = 30 + flag;
			}
			else {
				return -1;
			}
			avg += time - cc[flag].offset;
			acc = (double)(ex + gr * 0.66 + bd * 0.33) / quantity;
			cc[flag].existence = false;
			return 1;
		}
	}
	if (GetAsyncKeyState(VK_ESCAPE)) {
		remake = 0;
		gameStop = false;
		peekmessage(&msG);
		return 2;
	}
	if (GetAsyncKeyState(0x52)) {
		remake = 1;
		gameStop = false;
		peekmessage(&msG);
		return 2;
	}
	return -1;
}

void mode_std::drawStrike(int rtvalue, int& drawvalue_bg, int& drawvalue, int& stX, int& stY, int& stP,int stN) {
	if (stN == 1) {
		drawvalue_bg = time;
		stX = cc[rtvalue % 10].addx;
		stY = cc[rtvalue % 10].addy;
		stP = rtvalue / 10;
	}
	setlinestyle(PS_SOLID, 20);
	drawvalue = time;
	if (drawvalue_bg != 0 && (drawvalue - drawvalue_bg < 100)) {
		if (stP == 0) {
			setcolor(RGB(255, 201, 14));
			setlinestyle(PS_SOLID,20);
			circle(stX, stY, 10);
			setcolor(RGB(255, 255, 255));
		}
		else if (stP == 1) {
			setcolor(RGB(0, 255, 0));
			circle(stX, stY, 10);
			setcolor(RGB(255, 255, 255));
		}
		else if (stP == 2) {
			setcolor(RGB(0, 0, 255));
			circle(stX, stY, 10);
			setcolor(RGB(255, 255, 255));
		}
		else if (stP == 3) {
			setcolor(RGB(255, 0, 0));
			circle(stX, stY, 10);
			setcolor(RGB(255, 255, 255));
		}
	}
	setlinestyle(PS_SOLID, 1);
}

void textDisplay(double &acc,int &combo,int&score, double&delayed) {
	char dl[50];
	settextstyle(50, 0, "楷体");
	sprintf(dl, "%d", combo);
	outtextxy(0, 720 - textheight(dl), dl);
	sprintf(dl, "%d", score);
	outtextxy(1280 - textwidth(dl), 0, dl);
	sprintf(dl, "%.2lf %%", acc * 100);
	outtextxy((1280 - textwidth(dl)) / 2, 0, dl);
	settextstyle(20, 0, "楷体");
	sprintf(dl, "帧延时：%.4lf", delayed);
	outtextxy(0, 0, dl);
}