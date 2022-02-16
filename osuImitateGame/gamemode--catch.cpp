#include "classLib.h"



long long timeset();
void draw_image(IMAGE& image, int x, int y, int w = -1, int h = -1);

mode_catch::mode_catch(string dszName) {
	DszLoad(dszName);
	PlayerX = 575;
	loadimage(&Fruit, "./file/image/fruit.png");
	loadimage(&Player, "./file/image/catch-player.png");
	loadimage(&Ranking, "./file/image/ranking.png", 1280, 720);
	KeyState[0] = false;//按键状态初始化
	KeyState[1] = false;
	ShiftStateu[0] = false;
	ShiftStateu[1] = false;
	ShiftStated[0] = false;
	ShiftStated[1] = false;
}

void mode_catch::gameStart() {
	cleardevice();
	Sleep(2000);
	thread mS(&mode_catch::musicStart, this);
	thread tm(&mode_catch::timer, this);
	thread gm(&mode_catch::gameIn, this);
	tm.join();
	gm.join();
	mS.join();
}

void mode_catch::gameIn() {
	//帧延时计数
	double delayed = 0.0;
	int index = 0;
	int stN=0;
	int timebg,fm=0;
	int quantity = 0;
	int xp;
	for (int x = 0; x < 30; x++) {
		ft[x].addx = 0;
		ft[x].existence = false;
		ft[x].offset = 0;
	}
	setbkcolor(0);
	cleardevice();
	settextcolor(RGB(255, 255, 255));
	setcolor(RGB(255, 255, 255));
	long long begin = timeset();
	timebg = time;
	BeginBatchDraw();
	while (gameStop) {
		cleardevice();
		FruitsRefresh(quantity,index);
		xp = PlayerX;
		if (stN = event_Feedback()) {
			break;
		}
		if (abs(PlayerX - xp) > 50) {
			PlayerX = xp;
		}
		DrawPlayer();
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
	endGame();
}

void mode_catch::FruitsRefresh(int& quantity, int& index) {
	for (int f = 0; f < 30; f++){
		if (ft[f].existence == false && index < objectNub) {
			ft[f].addx = dszP[index].addX;
			ft[f].offset = dszP[index].offset;
			ft[f].existence = true;
			index++;
		}
		else if (ft[f].existence) {
			int cct = ft[f].offset - time;
			if (-150 < cct && cct < 520) {
				draw_image(Fruit,ft[f].addx,520-(ft[f].offset-time));
			}
		}
		if(time>=ft[f].offset&& ft[f].existence){
			if (PlayerX<ft[f].addx&& (PlayerX + 240)>(ft[f].addx+50)&&(time- ft[f].offset)<30) {
				ft[f].existence = false;
				ex++; 
				combo++;
				score += combo * 50;
				quantity++;
				acc = (double)ex / quantity;
			}
			else if (time >= (ft[f].offset + 150) && ft[f].existence) {
				ft[f].existence = false;
				ms++;
				combo = 0;
				quantity++;
				acc = (double)ex / quantity;
			}
		}
	
	}

}

int mode_catch::event_Feedback() {
	KeyDownJudge(VK_LEFT, MODE_LEFT, JUDGE_MODE_1(PlayerX), OPERATION_RULE_1);
	KeyDownJudge(VK_RIGHT, MODE_RIGHT, JUDGE_MODE_2(PlayerX), OPERATION_RULE_2);
	if (GetAsyncKeyState(VK_ESCAPE)) {
		remake = 0;
		gameStop = false;
		return 1;
	}
	if (GetAsyncKeyState(0x52)) {
		remake = 1;
		gameStop = false;
		return 1;
	}
	return 0;
}

void mode_catch::DrawPlayer(){
	if (combo > 0 && combo <= 50) {
		draw_image(Fruit, PlayerX + 70, 540);
	}
	else if (combo > 50 && combo <= 100) {
		draw_image(Fruit, PlayerX + 70, 540);
		draw_image(Fruit, PlayerX + 10, 520);
	}
	else if (combo > 100 && combo <= 200) {
		draw_image(Fruit, PlayerX + 140, 520);
		draw_image(Fruit, PlayerX + 70, 540);
		draw_image(Fruit, PlayerX + 10, 520);
	}
	else if (combo > 200 && combo <= 300) {
		draw_image(Fruit, PlayerX + 50, 470);
		draw_image(Fruit, PlayerX + 140, 520);
		draw_image(Fruit, PlayerX + 70, 540);
		draw_image(Fruit, PlayerX + 10, 520);
	}
	else if (combo > 300) {
		draw_image(Fruit, PlayerX + 90, 440);
		draw_image(Fruit, PlayerX + 120, 470);
		draw_image(Fruit, PlayerX + 50, 470);
		draw_image(Fruit, PlayerX + 140, 520);
		draw_image(Fruit, PlayerX + 70, 540);
		draw_image(Fruit, PlayerX + 10, 520);	
	}
	draw_image(Player, PlayerX, 570);
}

void mode_catch::KeyDownJudge(int key,bool keyMode,bool judge, int Operation) {
	if (GetAsyncKeyState(key) && !KeyState[keyMode]) {
		StartPosition = PlayerX;
		StartTime = time;
		KeyState[keyMode] = true;
	}
	else if (GetAsyncKeyState(key) && (GetAsyncKeyState(VK_LSHIFT) == 0)
		&& KeyState[keyMode] && !ShiftStateu[keyMode]) {
		if (judge) {
			PlayerX = StartPosition + Operation*(time - StartTime) * MOVE_SPEED;
			ShiftStated[keyMode] = true;
		}
	}
	else if (GetAsyncKeyState(key) && (GetAsyncKeyState(VK_LSHIFT) == 0) //shift键松开
		&& KeyState[keyMode] && ShiftStateu[keyMode]) {
		StartPosition = PlayerX;
		StartTime = time;
		if (judge) {
			PlayerX = StartPosition + Operation * (time - StartTime) * MOVE_SPEED;
			ShiftStateu[keyMode] = false;
		}
	}
	else if (GetAsyncKeyState(key) && GetAsyncKeyState(VK_LSHIFT)
		&& KeyState[keyMode] && !ShiftStated[keyMode]) {
		if (judge) {
			PlayerX = StartPosition + Operation * (time - StartTime) * MOVE_SPEED_UP;
			ShiftStateu[keyMode] = true;
			ShiftStated[keyMode] = false;
		}
	}
	else if (GetAsyncKeyState(key) && GetAsyncKeyState(VK_LSHIFT) //shift键按下
		&& KeyState[keyMode] && ShiftStated[keyMode]) {
		StartPosition = PlayerX;
		StartTime = time;
		if (judge) {
			PlayerX = StartPosition + Operation * (time - StartTime) * MOVE_SPEED_UP;
			ShiftStated[keyMode] = false;
		}
	}
	else if (GetAsyncKeyState(key) == 0) {
		KeyState[keyMode] = false;
	}
	
}

void mode_catch::testOutPut(double delayed) {
	setbkmode(TRANSPARENT);
	char dl[50];
	settextstyle(50, 0, "楷体");
	sprintf(dl, "%d", combo);
	outtextxy(PlayerX-(textwidth(dl) / 2)+120, 450, dl);
	sprintf(dl, "%d", score);
	outtextxy(1280 - textwidth(dl), 0, dl);
	sprintf(dl, "%.2lf %%", acc * 100);
	outtextxy((1280 - textwidth(dl)) / 2, 0, dl);
	settextstyle(20, 0, "楷体");
	sprintf(dl, "帧延时：%.4lf", delayed);
	outtextxy(0, 0, dl);
}

void mode_catch::endGame() {
	char tr[50];
	cleardevice();
	putimage(0, 0, &Ranking);
	settextstyle(70, 0, "Segoe Script");
	setcolor(RGB(255, 174, 201));
	sprintf(tr, "EX: %d", ex);
	outtextxy(50, 100, tr);
	sprintf(tr, "MS: %d", ms);
	outtextxy(50, 200, tr);
	sprintf(tr, "%d", maxcombo);
	outtextxy(60, 430, tr);
	sprintf(tr, "%d", score);
	outtextxy(230, 20, tr);
	sprintf(tr, "%.2lf %%", acc * 100);
	outtextxy(260, 430, tr);
	settextstyle(50, 0, "楷体");
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