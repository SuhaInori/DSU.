#pragma once
/*
*------------------------ͷ�ļ�����&�궨��--------------------------------------------
* @auther:NULL
* @version:1.0
* 
* ���ڿ����
* 
* 
*/

#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <math.h>
#include <windows.h>
#include <graphics.h>			  //EasyXͼ�ο�
#include <thread>				  //���̲߳���		
#include <conio.h>                //���������������
#include <ctime>				  //ϵͳʱ��
#include <fstream>                //�ļ�����ͷ�ļ�
#include <mmsystem.h>             //��ý��ͷ�ļ�
#include <io.h>                   //�ļ�����
#pragma comment(lib,"Winmm.lib")  //����ϵͳapi�ӿ�
//mciSendstring(��open  �����ļ��������ļ����ͣ�����.mp3�� alias  music��, NULL, NULL, NULL)��//�������ļ�������Դ�ļ�ͬһĿ¼�£�alias  music����˼���ǽ���������ļ���������Ϊmusic
//mciSendstring(��play music repeat��, NULL, NULL, NULL)��//�������֣�play��Ϊ���ţ�ͬ���ɻ���pause:��ͣ��stop:ֹͣ��close:�رգ�Resume:������Repeat��Ϊ�ظ����š�
//mciSendstring(��stop music repeat��, NULL, NULL, NULL)��//��ͣ�������֡�
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)   //��������궨��������1���򷵻�0
#define	STD 0
#define MANIA 1
#define	CATCH 2
#define TAIKO 3
#define BACK 4
//stdģʽ
#define EX_STD 60
#define GR_STD 125
#define BD_STD 185
#define MS_STD 255
//��Ȧ�ٶ�
#define AR 1200

//MANIAģʽ
#define EX_MANIA 15
#define	PF_MANAI 34
#define	GR_MANIA 65
#define GD_MANIA 95
#define	BD_MANIA 125
#define	MS_MANIA  155
#define	DOWN_SPEED  2

//CARCHģʽ
#define JUDGE_MODE_1(x)	 x>= 0
#define JUDGE_MODE_2(x)  x<= 1040
#define OPERATION_RULE_1  -1
#define OPERATION_RULE_2  1
#define MODE_LEFT 0
#define MODE_RIGHT 1
#define MOVE_SPEED	0.9
#define MOVE_SPEED_UP 1.8

//taikoģʽ
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
* -----------------------------˫�����ͼ--------------------------------------------------
* 	BeginBatchDraw();
*	FlushBatchDraw();
*	EndBatchDraw();
*   //���������ֵ
*	VkKeyScan('`')
* -----------------------------------------------------------------------------------------
*/
//ʱ���ȡ

