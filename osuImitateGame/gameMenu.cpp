/*						 menu&ui库
*																			------------------inori
*	1.界面实现
*	2.菜单选择
*	3.基本设定
*	4.退出游戏
*/
#include "libH.h"
#include "DirectoryAcquisition.h"
void draw_image(IMAGE& image, int x, int y, int w = -1, int h = -1);
string songNameLoad(string fN);
void choiceD(int choice,int point, string* name);
void rollF(int line, int point, IMAGE* gamebg, IMAGE* sb, IMAGE* mode, IMAGE* inori, IMAGE* back, IMAGE* frame, IMAGE* hp, DirectoryAcquisition* dszF, string* name, int windH);
extern HWND window;
extern RECT rectangleW;
extern POINT mouP;



//开始界面
void startUi(IMAGE *kanbanNiang,IMAGE *startImage,IMAGE *bg,int windowsW,int windowsH) {
	int w, h,p=1,r=0,g=0,b=0, mouseX=0, mouseY=0, textw, texth,text=0;
	bool pic=true,poc=false;
	while (r <= 255) {
		settextstyle(text, 0, "Segoe Print");
		settextcolor(RGB(r, g, b));
		textw = textwidth("welcome");
		texth = textheight("welcome");
		if (r >= 127) {
			setbkcolor(RGB(r - 127, g - 127, b - 127));
			cleardevice();
		}
		outtextxy((windowsW - textw) / 2, (windowsH - texth) / 2, "welcome");
		r+=2; g+=2; b+=2; text++;
		Sleep(1);
	}
	mciSendString("play ./file/sound/start.wma repeat", NULL, 0, NULL);
	Sleep(240);
	setbkcolor(RGB(254, 216, 185));
	BeginBatchDraw();
	for (int x = 49; x >0; x--){
		w = 500 - 10 * x; h = 500 - 10 * x;
		cleardevice();
		putimage(0, 0, &bg[1]);
		draw_image(startImage[x], (windowsW - w) / 2, (windowsH - h) / 2);
		FlushBatchDraw();
		Sleep(13);
	}
	EndBatchDraw();
	BeginBatchDraw();
	Sleep(210);
	while (!(KEY_DOWN(VK_LBUTTON)&&(mouseX>((windowsW-500)/2)&& mouseX< ((windowsW - 500) / 2)+500)&& (mouseY > ((windowsH - 500) / 2) && mouseY < ((windowsH - 500) / 2) + 500))) {
		GetWindowRect(window, &rectangleW);
		GetCursorPos(&mouP);
		mouseX = mouP.x - rectangleW.left - 11;
		mouseY = mouP.y - rectangleW.top - 31;
		cleardevice();
		w = 500 - 10 * p; h = 500 - 10 * p;
		putimage(0, 0, &bg[poc +1]);
		draw_image(startImage[p], (windowsW - w) / 2, (windowsH - h) / 2);
		if (p == 25) {
			pic = false;
			poc = !poc;
		}
		else if (p == 0) {
			pic = true;
		}
		if (pic) {
			p++;
		}
		else {
			p--;
		}
		FlushBatchDraw();
		Sleep(7);
	}
	EndBatchDraw();
	mciSendString("stop ./file/sound/start.wma", NULL, 0, NULL);
	BeginBatchDraw();
	for (int x = p; x >=0; x--) {
		w = 500 - 10 * x; h = 500 - 10 * x;
		putimage(0, 0, &bg[0]);
		draw_image(startImage[x], (windowsW - w) / 2, (windowsH - h) / 2);
		FlushBatchDraw();
		Sleep(5);
		cleardevice();
	}
	EndBatchDraw();
	
}

//菜单界面
void menuUi(IMAGE *kanbanNiang,IMAGE (*menu)[2],IMAGE*start,IMAGE*bg ,IMAGE*options,int windowsW, int windowsH) {
	int w,h, mouseX,mouseY;
	bool Refresh=true;
	w = (windowsW - 500) / 2+500;
	h = (windowsH - 500) / 2;
	BeginBatchDraw();
	mciSendString("play ./file/sound/ton/to6.wma", NULL, 0, NULL);
	for (int x = 0; x < w; x+=30) {
		cleardevice();
		putimage(0, 0, &bg[0]);
		draw_image(*kanbanNiang, -430+x/2, (windowsH+1072) - 2*x);
		putimage((windowsW + 370) - x, h+50, &menu[0][0]);
		putimage((windowsW + 420) - x, h+200, &menu[1][0]);
		putimage((windowsW + 370) - x, h+350, &menu[2][0]);
		draw_image(start[0], (windowsW - 500) / 2, h);
		FlushBatchDraw();
		Sleep(7);
	}
	EndBatchDraw();
	BeginBatchDraw();
	while (true) {
		GetWindowRect(window, &rectangleW);
		GetCursorPos(&mouP);
		mouseX = mouP.x - rectangleW.left - 11;
		mouseY = mouP.y - rectangleW.top - 31;
		if((mouseX> (windowsW + 370) - w)&& (mouseX < (windowsW + 670) - w)&&(mouseY>(h+50))&&(mouseY < (h + 150))&& Refresh==true){
			putimage((windowsW + 390) - w, h + 50, &menu[0][1]);
			Refresh = false;
		}
		else if ((mouseX > (windowsW + 420) - w) && (mouseX < (windowsW + 720) - w) && (mouseY > (h + 200)) && (mouseY < (h + 300)) && Refresh == true) {
			putimage((windowsW + 440) - w, h + 200, &menu[1][1]);
			Refresh = false;
		}
		else if ((mouseX > (windowsW + 370) - w) && (mouseX < (windowsW + 670) - w) && (mouseY > (h + 350)) && (mouseY < (h + 450)) && Refresh == true) {
			putimage((windowsW + 390) - w, h + 350, &menu[2][1]);
			Refresh = false;
		}
		else if((!((mouseX >(windowsW + 370) - w) && (mouseX < (windowsW + 670) - w) && (mouseY >(h + 50)) && (mouseY < (h + 150))))
			  &&(!((mouseX > (windowsW + 420) - w) && (mouseX < (windowsW + 720) - w) && (mouseY > (h + 200)) && (mouseY < (h + 300))))
			  &&(!((mouseX > (windowsW + 370) - w) && (mouseX < (windowsW + 670) - w) && (mouseY > (h + 350)) && (mouseY < (h + 450))))
			  &&Refresh == false) {
			putimage((windowsW + 390) - w, h + 50, &menu[0][0]);
			putimage((windowsW + 440) - w, h + 200, &menu[1][0]);
			putimage((windowsW + 390) - w, h + 350, &menu[2][0]);
			Refresh = true;
		}
		//draw_image(*options, windowW - x, 0);
		draw_image(start[0], (windowsW - 500) / 2, h);
		if (KEY_DOWN(VK_LBUTTON)&&((mouseX > (windowsW + 370) - w) && (mouseX < (windowsW + 670) - w) && (mouseY > (h + 50)) && (mouseY < (h + 150)))) {
			return;
		}
		if (KEY_DOWN(VK_LBUTTON)&& ((mouseX > (windowsW + 420) - w) && (mouseX < (windowsW + 720) - w) && (mouseY > (h + 200)) && (mouseY < (h + 300)))) {
			BeginBatchDraw();
			for (int x = 0; x <400; x+=8) {
				cleardevice();
				draw_image(*kanbanNiang, -440 + w / 2, (windowsH + 1112) - 2 * w);
				putimage((windowsW + 390) - w, h + 50, &menu[0][0]);
				putimage((windowsW + 440) - w, h + 200, &menu[1][0]);
				putimage((windowsW + 390) - w, h + 350, &menu[2][0]);
				draw_image(start[0], (windowsW - 500) / 2, h);
				draw_image(*options, windowsW - x, 0);
				FlushBatchDraw();
				Sleep(1);
			}
			EndBatchDraw();
			while (true){
				GetCursorPos(&mouP);
				mouseX = mouP.x - rectangleW.left - 11;
				if (KEY_DOWN(VK_LBUTTON)&& (mouseX< windowsW-400)) {
					BeginBatchDraw();
					for (int x = 0; x < 400; x += 8) {
						cleardevice();
						draw_image(*kanbanNiang, -440 + w / 2, (windowsH + 1112) - 2 * w);
						putimage((windowsW + 390) - w, h + 50, &menu[0][0]);
						putimage((windowsW + 440) - w, h + 200, &menu[1][0]);
						putimage((windowsW + 390) - w, h + 350, &menu[2][0]);
						draw_image(start[0], (windowsW - 500) / 2, h);
						draw_image(*options, windowsW -400+ x, 0);
						FlushBatchDraw();
						Sleep(1);
					}
					EndBatchDraw();
					break;
				}
			}
		}
		else if (KEY_DOWN(VK_LBUTTON) && ((mouseX > (windowsW + 370) - w) && (mouseX < (windowsW + 670) - w) && (mouseY > (h + 350)) && (mouseY < (h + 450)))) {
			closegraph();
			exit(0);
		}
		FlushBatchDraw();
	}
	EndBatchDraw();
}

//游戏选择界面
modeAndSongChoice gameStart(IMAGE* gamebg,IMAGE* mode,IMAGE *sb, IMAGE* back,IMAGE *hp,IMAGE *frame,IMAGE *inori, DirectoryAcquisition * dszF, int windW, int windH) {
	modeAndSongChoice msC;
	int modec=0;
	int point = 0;
	int choice = -1;
	BeginBatchDraw();
	for (int x = 720; x >= 0; x-=2) {
		putimage(0, x, gamebg);
		draw_image(mode[0], (980 + (x / 2)), 420);
		FlushBatchDraw();
	}	
	EndBatchDraw();
	setbkmode(TRANSPARENT);
	settextstyle(50,0, "隶书");
	setcolor(RGB(255, 215, 185));
	draw_image(mode[0], 970, 420);
	string* name = new string[dszF->dirNub];
	for (int c = 0; c < dszF->dirNub; c++) {
		name[c] = songNameLoad(dszF->DirectoryName[c]);
	}
	BeginBatchDraw();
	for (int p = 1280; p > 800;p-=2) {
		cleardevice();
		putimage(0, 0, gamebg);
		for (int x = point; x < point+7; x++) {
			draw_image(*sb, p - 40-15*x, x * 100);
			if (x >= dszF->dirNub) {
			}
			else {
				outtextxy(p-15*x, x * 100+20, name[x].c_str());
			}
		}
		draw_image(mode[0], 980, 420);
		draw_image(*inori, 0, windH - 400);
		draw_image(*back, 0, windH-75);
		draw_image(*frame, 5, 5);
		putimage(10, 10, hp);
		FlushBatchDraw();
	}
	EndBatchDraw();
	int mouseX,mouseY;
	while (true) {
		GetWindowRect(window, &rectangleW);
		GetCursorPos(&mouP);
		mouseX = mouP.x - rectangleW.left - 11;
		mouseY = mouP.y - rectangleW.top - 31;
		if (point == dszF->dirNub) {
			point = 0;
		}
		if(KEY_DOWN(VK_LBUTTON)){
			if ((mouseX > 760)&&(mouseX < 1280) && (mouseY > 0) && (mouseY < 100)&&(choice!=0)) {//1
				choiceD(choice,point, name);
				setcolor(GREEN);
				if (point >= dszF->dirNub) {
					outtextxy(802, 20, name[(point% dszF->dirNub)].c_str());
				}
				else {
					outtextxy(802, 20, name[point].c_str());
				}	
				mciSendString("play ./file/sound/click.wma", NULL, 0, NULL);
				choice = 0;
			}
			else if((mouseX>760)&& (mouseX < 1280)&&(mouseY>100)&&(mouseY<200)&&(choice!=1)){//2
				choiceD(choice, point, name);
				setcolor(GREEN);
				if (point+1>= dszF->dirNub) {
					outtextxy(787, 120, name[((point+1)% dszF->dirNub)].c_str());
				}
				else {
					outtextxy(787, 120, name[point+1].c_str());
				}
				mciSendString("play ./file/sound/click.wma", NULL, 0, NULL);
				choice = 1;
			}
			else if ((mouseX > 760) && (mouseX < 1280) && (mouseY > 200) && (mouseY < 300) && (choice != 2)) {//2
				choiceD(choice, point, name);
				setcolor(GREEN);
				if (point + 2>= dszF->dirNub) {
					outtextxy(772, 220, name[((point + 2) % dszF->dirNub)].c_str());
				}
				else {
					outtextxy(772, 220, name[point + 2].c_str());
				}
				mciSendString("play ./file/sound/click.wma", NULL, 0, NULL);
				choice = 2;
			}
			else if ((mouseX > 760) && (mouseX < 1280) && (mouseY > 300) && (mouseY < 400) && (choice != 3)) {//4
				choiceD(choice, point, name);
				setcolor(GREEN);
				if (point + 3 >= dszF->dirNub) {
					outtextxy(757, 320, name[((point + 3) % dszF->dirNub)].c_str());
				}
				else {
					outtextxy(757, 320, name[point + 3].c_str());
				}
				mciSendString("play ./file/sound/click.wma", NULL, 0, NULL);
				choice = 3;
			}
			else if ((mouseX > 760) && (mouseX < 980) && (mouseY > 400) && (mouseY < 500) && (choice != 4)) {//5
				rollF(1, point, gamebg, sb, mode, inori, back, frame, hp, dszF, name, windH);
				point++;
				setcolor(GREEN);
				if (point + 3 >= dszF->dirNub) {
					outtextxy(757, 320, name[((point + 3) % dszF->dirNub)].c_str());
				}
				else {
					outtextxy(757, 320, name[point + 3].c_str());
				}
				mciSendString("play ./file/sound/click.wma", NULL, 0, NULL);
				choice = 3;
			}
			else if ((mouseX > 760) && (mouseX < 980) && (mouseY > 500) && (mouseY < 600) && (choice != 5)) {//6
				rollF(2, point, gamebg, sb, mode, inori, back, frame, hp, dszF, name, windH);
				point += 2;
				setcolor(GREEN);
				if (point + 3 >= dszF->dirNub) {
					outtextxy(757, 320, name[((point + 3) % dszF->dirNub)].c_str());
				}
				else {
					outtextxy(757, 320, name[point + 3].c_str());
				}
				mciSendString("play ./file/sound/click.wma", NULL, 0, NULL);
				choice = 3;
			}
			else if ((mouseX > 760) && (mouseX < 980) && (mouseY > 600) && (mouseY < 700) && (choice != 6)) {//7
				rollF(3, point, gamebg, sb, mode, inori, back, frame, hp, dszF, name, windH);
				point += 3;
				setcolor(GREEN);
				if (point + 1 > dszF->dirNub) {
					outtextxy(757, 320, name[((point + 3) % dszF->dirNub)].c_str());
				}
				else {
					outtextxy(757, 320, name[point + 3].c_str());
				}
				mciSendString("play ./file/sound/click.wma", NULL, 0, NULL);
				choice = 3;
			}
			else if ((mouseX > 1190) && (mouseY > 420 )&& (mouseX < 1280 )&&( mouseY < 530)) {//1190.420.1280.530
				modec = 0;
				draw_image(mode[0], 980, 420);
			}
			else if ((mouseX > 1085) && (mouseY > 450) && (mouseX < 1190) &&( mouseY < 545)) {//1085.450.1190,545
				modec = 1;
				draw_image(mode[1], 980, 420);
			}
			else if((mouseX > 1000 )&&( mouseY > 545 )&&( mouseX < 1120) &&( mouseY < 630)){//1000 .545.1120,630
				modec = 2;
				draw_image(mode[2], 980, 420);
			}
			else if ((mouseX > 980 )&&( mouseY > 630) && (mouseX < 1090) && (mouseY < 720)) {//980.630.1090,720
				modec = 3;
				draw_image(mode[3], 980, 420);
			}
			else if ((mouseX > 1150 )&&( mouseY > 580) &&( mouseX < 1280) && (mouseY < 720)) {
				if ((choice + point) < 0)continue;
				msC.mode = modec;
				msC.dir = dszF->DirectoryName[(choice + point) % dszF->dirNub];
				return msC;
			}
			else if ((mouseX > 0) && (mouseX < 200) && (mouseY > 550) && (mouseY < 720)) {
				msC.mode = 4;
				return msC;
			}
		}
	}
	
	system("pause");
}

string songNameLoad(string fN) {
	string filedir="./file/dszFil/";
	filedir += fN;
	string songname;
	ifstream ifs;
	ifs.open(filedir, ios::in);
	ifs >> songname;
	ifs.close();
	return songname;
}

void choiceD(int choice,int point,string *name) {
	if (choice >=0 && choice < 8) {
		if (choice <= 3) {
			setcolor(RGB(255, 215, 185));
			outtextxy(802 - 15 * choice, 20 + choice * 100, name[choice+point].c_str());
		}
		else {
			setcolor(RGB(255, 215, 185));
			outtextxy(802 - 15 * (7 - choice), 20 + choice * 100, name[choice+point].c_str());
		}
	}
}

void rollF(int line,int point,IMAGE *gamebg,IMAGE*sb, IMAGE* mode,IMAGE *inori,IMAGE*back,IMAGE *frame,IMAGE *hp, DirectoryAcquisition* dszF,string *name,int windH) {
	int c=0;
	BeginBatchDraw();
	for (int p = 0; p <=5 * line; p ++) {
		cleardevice();
		putimage(0, 0, gamebg);
		for (int x = point; x < point + 10; x++) {
			setcolor(RGB(255, 215, 185));
			draw_image(*sb, 760 - 15 * (x - point) + 3 * p, (x - point) * 100 - 20 * p);
		}
		for (int x = point; x < point + 10; x++){
			if (x >= dszF->dirNub) {
				outtextxy(800 - 15 * (x - point) +3 * p-2, (x - point) * 100 - 20 * p+20, name[x - dszF->dirNub].c_str());
			}
			else {
				outtextxy(800 - 15 * (x - point) + 3 * p+2, (x - point) * 100 - 20 * p+20, name[x].c_str());
			}
		}
		draw_image(mode[0], 980, 420);
		draw_image(*inori, 0, windH - 400);
		draw_image(*back, 0, windH - 75);
		draw_image(*frame, 5, 5);
		putimage(10, 10, hp);
		FlushBatchDraw();
		Sleep(1);
	}
	EndBatchDraw();
}