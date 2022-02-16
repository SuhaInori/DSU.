#pragma once
/*
*------------------------头文件包含&宏定义--------------------------------------------
* @auther:NULL
* @version:1.0
* 
* 用于库包含
* 
* 
*/

#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <math.h>
#include <windows.h>
#include <graphics.h>			  //EasyX图形库
#include <thread>				  //多线程并发		
#include <conio.h>                //按键输入输出检测库
#include <ctime>				  //系统时间
#include <fstream>                //文件操作头文件
#include <mmsystem.h>             //多媒体头文件
#include <io.h>                   //文件操作
#pragma comment(lib,"Winmm.lib")  //导入系统api接口
//mciSendstring(“open  音乐文件名（加文件类型，例：.mp3） alias  music”, NULL, NULL, NULL)；//将音乐文件放在与源文件同一目录下，alias  music的意思就是将这个音乐文件重新命名为music
//mciSendstring(“play music repeat”, NULL, NULL, NULL)；//播放音乐，play意为播放，同样可换做pause:暂停，stop:停止，close:关闭，Resume:继续。Repeat意为重复播放。
//mciSendstring(“stop music repeat”, NULL, NULL, NULL)；//暂停播放音乐。
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)   //鼠标点击检测宏定义点击返回1否则返回0
#define	STD 0
#define MANIA 1
#define	CATCH 2
#define TAIKO 3
#define BACK 4
//std模式
#define EX_STD 60
#define GR_STD 125
#define BD_STD 185
#define MS_STD 255
//缩圈速度
#define AR 1200

//MANIA模式
#define EX_MANIA 15
#define	PF_MANAI 34
#define	GR_MANIA 65
#define GD_MANIA 95
#define	BD_MANIA 125
#define	MS_MANIA  155
#define	DOWN_SPEED  2

//CARCH模式
#define JUDGE_MODE_1(x)	 x>= 0
#define JUDGE_MODE_2(x)  x<= 1040
#define OPERATION_RULE_1  -1
#define OPERATION_RULE_2  1
#define MODE_LEFT 0
#define MODE_RIGHT 1
#define MOVE_SPEED	0.9
#define MOVE_SPEED_UP 1.8

//taiko模式
#define DRUM_SPEED 1
#define TAIKO_LIANG 45
#define TAIKO_KE  95
#define TAIKO_MS  150
using namespace std;

struct modeAndSongChoice {
	string dir;
	int mode;
};
/*
* -----------------------------双缓冲绘图--------------------------------------------------
* 	BeginBatchDraw();
*	FlushBatchDraw();
*	EndBatchDraw();
*   //返回虚拟键值
*	VkKeyScan('`')
* -----------------------------------------------------------------------------------------
*/
//时间获取

