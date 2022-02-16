/*
*------------------------------------mode����--------------------------------------------
*/
#include "libH.h"
//���ڶ�ȡ��dsz�ļ����ݴ洢
struct dszPark {
	//ʱ����
	int offset;
	//std ����
	int x;
	int y;
	//mania ���
	int key;  //0-3
	//catch x��������
	int addX;
	//taiko ������
	bool drum;
};

//gameMode��
class gameMode {
protected:
	//ʱ����
	int time;
	//��������
	int length;
	//������
	int objectNub;
	//����
	int score;
	//������
	int combo;
	//���������
	int maxcombo;
	//��ʼʱ��
	int beginTm;
	//׼��
	double acc;
	//ƽ��ƫ����
	double avg;
	//��Ϸ��ֹ
	bool gameStop;
	//�ж�  //std		mania		taiko		catch/ms
	int ex; //0-55		 0-15		0-45		��
	int pf; //��		15-34		45-100		��
	int gr; //55-115	34-65		��			��
	int gd; //��		65-95		��			��
	int bd; //115-165	95-125		��			��
	int ms;	//165-255	125-155		100-150		��
	//�����˶��ٶ�0-40��
	int speed;
	string songName;
	IMAGE Ranking;
	dszPark *dszP;


	//��ʱ��
	void timer();
	//dsz�ļ���ȡ
	void DszLoad(string dszName);
public:
	//�Ƿ����¿�ʼ
	bool remake;
	//���캯������ʼ������
	gameMode():score(0),combo(0),maxcombo(0), acc(0.0), avg(0.0), ex(0), pf(0), gr(0), gd(0), bd(0), ms(0),remake(true),gameStop(true) {};
	//��������
	void musicStart();
	//����
	virtual void endGame()=0;
	//�������
	virtual void gameStart()=0;


	~gameMode();

};

/*
*------------------------------------mode����--------------------------------------------
*/
//std���
struct circleP {
	//ԲȦ�ڴ����е�λ��
	int addx, addy;
	//ԲȦ�������е�����
	int offset;
	//ԲȦ�Ƿ�����ˢ��
	bool existence;
};

class mode_std :public gameMode {


public:

	mode_std(string dszName);
	//stdģʽ�����������
	void gameStart();
	//~mode_std();
private:
	struct circleP cc[10];
	IMAGE clc;

	//ͼ��ʼ����
	void gameIn();
	//����note
	void ccRefresh(int& quantity, int& index);
	//�¼�����
	int event_Feedback(int& quantity, int& rtvalue);
	//���ƴ������
	void drawStrike(int rtvalue, int& drawvalue_bg, int& drawvalue, int& stX, int& stY, int& stP, int stN);
	//��������
	//void musicStart();
	//��Ϸ����
	void endGame();
};


//mania���
struct noteP {
	//note ���ڹ��
	int key;
	//note ʱ��λ��
	int offset;
	//notr �Ƿ��ڻ���ˢ��
	bool existence;
};

struct Distribution {//����¼
	int error;
	int time;
};

class mode_mania :public gameMode {
public:
	mode_mania(string dszName);
	// mania�������
	void gameStart();
	~mode_mania();

private:
	struct noteP np[50];
	IMAGE note;
	IMAGE track;
	int rtTim;
	Distribution* error;		   //����¼
	int errorIndex;	   //����¼�±�
	bool rtSet[2];     //�˳����ؿ�����״̬
	bool KeyState[4];  //����״̬
	//����note
	void npRefresh(int& quantity, int& index);
	void gameIn();
	void endGame();
	void testOutPut(double delayed);
	int event_Feedback(int& quantity);
	void judge(int key, int& quantity);
	void DistributionMap();
};

//catch���
struct Fruits {
	//Fruits ����xλ��
	int addx;
	//Fruits ʱ��λ��
	int offset;
	//Fruits �Ƿ�����ˢ��
	int existence;
};

class mode_catch :public gameMode {
public:
	mode_catch(string dszName);
	// mania�������
	void gameStart();
	//~mode_catch();
private:
	int PlayerX;
	int StartPosition, StartTime;
	//����״̬
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
	// ������ true���� ��֮
	bool drumColor;
	//drum ʱ��λ��
	int offset;
	//drum �Ƿ�����ˢ��
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
	bool rtSet[2];     //�˳����ؿ�����״̬
	bool KeyState[4];  //����״̬
	void gameIn();
	void DrumRefresh(int& quantity, int& index);
	int	event_Feedback(int& quantity);
	void testOutPut(double delayed);
	void judge(int& quantity, bool color);
	void endGame();
};