#include "classLib.h"


//
//gameMode::gameMode() {
//
//}

/*
* 文件规则
* 歌曲名
* 歌曲文件名
* 歌曲长度
* 时间轴  std:x坐标 y坐标  mania：键位坐标轨道 catch：x位置 taiko：红蓝鼓 
*/

//gameMode::gameMode(string dszName) {
//	string dirAdd = "./file/dszFil/";
//	dirAdd += dszName;
//	objectNub = 0;
//	int index=0;
//	int a, b, c, d, e;
//	bool f;
//	ifstream ifs;
//
//	ifs.open(dirAdd, ios::in);
//	ifs >> songName;
//	ifs >> songName;
//	ifs >> length;
//	while (ifs >> a && ifs >> b && ifs >> c && ifs >> d && ifs >> e && ifs >> f) {
//		objectNub++;
//	}
//	ifs.close();
//	dszP = new  dszPark[objectNub];
//	ifs.open(dirAdd, ios::in);
//	ifs >> songName;
//	ifs >> songName;
//	ifs >> length;
//	while(ifs>> dszP ->offset&&ifs >> dszP->x&&ifs>> dszP->y&& ifs >> dszP ->key&& ifs >> dszP ->addX&& ifs >> dszP ->drum){
//		index++;
//	}
//	ifs.close();
//
//}
//thread mS(&mode_mania::musicStart, this);
		/*if (time >= 0 && !musicSt) {
			mS.join();
			musicSt = true;
		}*/
void gameMode::timer( ){
	beginTm = clock()+1000;
	while(time!= length+125&& gameStop){
		time = clock() - beginTm;
	}
	gameStop = false;
	char sn[50];
	sprintf(sn, "stop ./file/song/%s", songName.c_str());
	mciSendString(sn, NULL, 0, NULL);
}

void gameMode::DszLoad(string dszName) {
	string dirAdd = "./file/dszFil/";
	dirAdd += dszName;
	objectNub = 0;
	int index = 0;
	int a, b, c, d, e;
	bool f;
	ifstream ifs;
	ifs.open(dirAdd, ios::in);

	ifs >> songName;
	ifs >> songName;
	ifs >> length;
	while (ifs >> a && ifs >> b && ifs >> c && ifs >> d && ifs >> e && ifs >> f) {
		objectNub++;
	}
	ifs.close();
	dszP = new  dszPark[objectNub];
	ifs.open(dirAdd, ios::in);
	ifs >> songName;
	ifs >> songName;
	ifs >> length;
	while (index != objectNub) {
		ifs >> dszP[index].offset;
		ifs >> dszP[index].x;
		ifs >> dszP[index].y;
		ifs >> dszP[index].key;
		ifs >> dszP[index].addX;
		ifs >> dszP[index].drum;
		index++;
	}
	ifs.close();
}

gameMode::~gameMode() {

	if (!dszP) {
		delete[]dszP;
		dszP == NULL;
	}
}

void gameMode::musicStart() { 
	char sn[50];
	bool musS=true;
	sprintf(sn, "play ./file/song/%s", songName.c_str());
	while (musS){
		if (time >=-100) {
			 mciSendString(sn, NULL, 0, NULL);
			 beginTm = clock();
			musS = false;
		}
		cout << time << endl;
	}
	
}

long long timeset() {
	FILETIME fileTime;
	long long now_long;
	GetSystemTimeAsFileTime(&fileTime);
	now_long = (long long(fileTime.dwHighDateTime) << 32) + fileTime.dwLowDateTime;
	return now_long;
}
