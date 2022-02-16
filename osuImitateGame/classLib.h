/*
*------------------------------------mode父类--------------------------------------------
*/
#include "libH.h"
//用于读取的dsz文件数据存储
struct dszPark {
	//时间轴
	int offset;
	//std 坐标
	int x;
	int y;
	//mania 轨道
	int key;  //0-3
	//catch x的轴坐标
	int addX;
	//taiko 红蓝鼓
	bool drum;
};

//gameMode类
class gameMode {
protected:
	//时间轴
	int time;
	//歌曲长度
	int length;
	//物量数
	int objectNub;
	//分数
	int score;
	//连击数
	int combo;
	//最大连击数
	int maxcombo;
	//初始时间
	int beginTm;
	//准度
	double acc;
	//平均偏移量
	double avg;
	//游戏终止
	bool gameStop;
	//判定  //std		mania		taiko		catch/ms
	int ex; //0-55		 0-15		0-45		√
	int pf; //无		15-34		45-100		无
	int gr; //55-115	34-65		无			无
	int gd; //无		65-95		无			无
	int bd; //115-165	95-125		无			无
	int ms;	//165-255	125-155		100-150		×
	//物体运动速度0-40；
	int speed;
	string songName;
	IMAGE Ranking;
	dszPark *dszP;


	//定时器
	void timer();
	//dsz文件读取
	void DszLoad(string dszName);
public:
	//是否重新开始
	bool remake;
	//构造函数、初始化变量
	gameMode():score(0),combo(0),maxcombo(0), acc(0.0), avg(0.0), ex(0), pf(0), gr(0), gd(0), bd(0), ms(0),remake(true),gameStop(true) {};
	//播放音乐
	void musicStart();
	//结算
	virtual void endGame()=0;
	//程序入口
	virtual void gameStart()=0;


	~gameMode();

};

/*
*------------------------------------mode子类--------------------------------------------
*/
//std相关
struct circleP {
	//圆圈在窗口中的位置
	int addx, addy;
	//圆圈完美击中的坐标
	int offset;
	//圆圈是否正在刷新
	bool existence;
};

class mode_std :public gameMode {


public:

	mode_std(string dszName);
	//std模式程序启动入口
	void gameStart();
	//~mode_std();
private:
	struct circleP cc[10];
	IMAGE clc;

	//图像开始绘制
	void gameIn();
	//重置note
	void ccRefresh(int& quantity, int& index);
	//事件反馈
	int event_Feedback(int& quantity, int& rtvalue);
	//绘制打击动画
	void drawStrike(int rtvalue, int& drawvalue_bg, int& drawvalue, int& stX, int& stY, int& stP, int stN);
	//播放音乐
	//void musicStart();
	//游戏结算
	void endGame();
};


//mania相关
struct noteP {
	//note 所在轨道
	int key;
	//note 时间位置
	int offset;
	//notr 是否在画面刷新
	bool existence;
};

struct Distribution {//误差记录
	int error;
	int time;
};

class mode_mania :public gameMode {
public:
	mode_mania(string dszName);
	// mania程序入口
	void gameStart();
	~mode_mania();

private:
	struct noteP np[50];
	IMAGE note;
	IMAGE track;
	int rtTim;
	Distribution* error;		   //误差记录
	int errorIndex;	   //误差记录下标
	bool rtSet[2];     //退出和重开按键状态
	bool KeyState[4];  //按键状态
	//重置note
	void npRefresh(int& quantity, int& index);
	void gameIn();
	void endGame();
	void testOutPut(double delayed);
	int event_Feedback(int& quantity);
	void judge(int key, int& quantity);
	void DistributionMap();
};

//catch相关
struct Fruits {
	//Fruits 所在x位置
	int addx;
	//Fruits 时间位置
	int offset;
	//Fruits 是否正在刷新
	int existence;
};

class mode_catch :public gameMode {
public:
	mode_catch(string dszName);
	// mania程序入口
	void gameStart();
	//~mode_catch();
private:
	int PlayerX;
	int StartPosition, StartTime;
	//按键状态
	bool KeyState[2],ShiftStateu[2],ShiftStated[2];
	IMAGE Player;
	IMAGE Fruit;
	struct Fruits ft[30];

	void gameIn();
	void FruitsRefresh(int& quantity, int& index);
	int	event_Feedback();
	void DrawPlayer();
	void KeyDownJudge(int key,bool keyMode,bool judge, int Operation);
	void testOutPut(double delayed);
	void endGame();
};

//taiko
struct Drum {
	// 红蓝鼓 true：红 反之
	bool drumColor;
	//drum 时间位置
	int offset;
	//drum 是否正在刷新
	bool existence;
};

class mode_taiko :public gameMode{
public :
	mode_taiko(string dszName);
	void gameStart();
private:
	IMAGE drum[2];
	IMAGE Kdown[3];
	IMAGE bg;
	Drum dm[30];
	int rtTim;
	bool rtSet[2];     //退出和重开按键状态
	bool KeyState[4];  //按键状态
	void gameIn();
	void DrumRefresh(int& quantity, int& index);
	int	event_Feedback(int& quantity);
	void testOutPut(double delayed);
	void judge(int& quantity, bool color);
	void endGame();
};