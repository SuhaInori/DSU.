#include "MapRanderMania--.h"


int MapRander::MrMain() {
	mode=0;
	bool flag=true;
	while (flag){
		system("cls");
		std::cout << "-----------�������������------------" << std::endl;
		std::cout << "ѡ�����ɵļ���" << std::endl;
		std::cout << "0.ȫ���" << std::endl;
		std::cout << "1.jack" << std::endl;
		std::cout << "2.tech" << std::endl;
		std::cout << "3.stream" << std::endl;
		std::cout << "4.speed" << std::endl;
		std::cin >> mode;
		std::cout << "���濪ʼʱ��" << std::endl;
		std::cin >> times;
		std::cout << "�������ʱ��" << std::endl;
		std::cin >> timee;
		std::cout << "����bpm" << std::endl;
		std::cin >> bpm;
		std::cout << "�������ϸ��" << std::endl;
		std::cin >> subdivision;
		timsd = 60000 / bpm;
		if (mode == 0) {
			std::cout << "׼������......" << std::endl;
			system("pause");
			system("cls");
			RandKey();
		}
		else if (mode == 1) {
			std::cout << "�����ͣ�0.������ 1.���" << std::endl;
			std::cin >> Dsr;
			std::cout << "׼������......" << std::endl;
			system("pause");
			system("cls");
			Jack();
		}
		else if (mode == 2) {
			std::cout << "׼������......" << std::endl;
			system("pause");
			system("cls");
			Tech();
		}
		else if (mode == 3) {
			std::cout << "�м��ͣ�0.�г��� 1.���� 2 ǿ��" << std::endl;
			std::cin >> Dsr;
			std::cout << "׼������......" << std::endl;
			system("pause");
			system("cls");
			Stream();
		}
		else if (mode == 4) {
			std::cout << "�Ҽ��ͣ�0.�ҳ��� 1.����" << std::endl;
			std::cin >> Dsr;
			std::cout << "׼������......" << std::endl;
			system("pause");
			system("cls");
			Speed();
		}
		system("pause");
		system("cls");
		std::cout << "�Ƿ������ 0 or 1 " << std::endl;
		std::cin >> flag;
	}
	return 1;
}
//aΪ�������Χ��0~a-1);bΪ��ʼ��
int MapRander::Rd(int Range, int MixVal){	//�������������
	srand((unsigned)time(NULL) + (unsigned)rand() - (unsigned)rand() % 3);
	int temp = 0;
	temp = rand() % Range + MixVal;
	return temp;
}
void  MapRander::KeyOut(){//һά���Ϳ� ������ ���ù���0000 ��1Ϊ��Ӧ�����������:1000 ���1�Ź����
	int t;
	t = offset;
	int b = 0;
	if (key == 0b1000){//a Ϊһά���͵ı�ʾ��ʽ  
		std::cout << t << " 1 1 0 1 1" << std::endl;
	}
	else if (key == 0b0100){
		std::cout << t << " 1 1 1 1 1" << std::endl;
	}
	else if (key == 0b0010){
		std::cout << t << " 1 1 2 1 1" << std::endl;
	}
	else if (key == 0b0001){
		std::cout << t << " 1 1 3 1 1" << std::endl;
	}
	else if (key == 0b1100){
		std::cout << t << " 1 1 0 1 1" << std::endl;
		std::cout << t << " 1 1 1 1 1" << std::endl;
	}
	else if (key == 0b1010){
		std::cout << t << " 1 1 0 1 1" << std::endl;
		std::cout << t << " 1 1 2 1 1" << std::endl;
	}
	else if (key == 0b1001){
		std::cout << t << " 1 1 0 1 1" << std::endl;
		std::cout << t << " 1 1 3 1 1" << std::endl;
	}
	else if (key == 0b0110){
		std::cout << t << " 1 1 1 1 1" << std::endl;
		std::cout << t << " 1 1 2 1 1" << std::endl;
	}
	else if (key == 0b0101){
		std::cout << t << " 1 1 1 1 1" << std::endl;
		std::cout << t << " 1 1 3 1 1" << std::endl;
	}
	else if (key == 0b0011){
		std::cout << t << " 1 1 2 1 1" << std::endl;
		std::cout << t << " 1 1 3 1 1" << std::endl;
	}
	else if (key == 0b1110){
		std::cout << t << " 1 1 0 1 1" << std::endl;
		std::cout << t << " 1 1 1 1 1" << std::endl;
		std::cout << t << " 1 1 2 1 1" << std::endl;
	}
	else if (key == 0b1101){
		std::cout << t << " 1 1 0 1 1" << std::endl;
		std::cout << t << " 1 1 1 1 1" << std::endl;
		std::cout << t << " 1 1 3 1 1" << std::endl;
	}
	else if (key == 0b1011){
		std::cout << t << " 1 1 0 1 1" << std::endl;
		std::cout << t << " 1 1 2 1 1" << std::endl;
		std::cout << t << " 1 1 3 1 1" << std::endl;
	}
	else if (key == 0b0111){
		std::cout << t << " 1 1 1 1 1" << std::endl;
		std::cout << t << " 1 1 2 1 1" << std::endl;
		std::cout << t << " 1 1 3 1 1" << std::endl;
	}
	else if (key == 0b1111){
		std::cout << t << " 1 1 0 1 1" << std::endl;
		std::cout << t << " 1 1 1 1 1" << std::endl;
		std::cout << t << " 1 1 2 1 1" << std::endl;
		std::cout << t << " 1 1 3 1 1" << std::endl;
	}
}
void MapRander::RandKey(){
	float tim_ss;//ÿС��ʱ����
	tim_ss = timsd / subdivision;
	for (offset = times; offset <= timee; offset += tim_ss)
	{
		key = Rd(15, 1);
		KeyOut();
	}
}
//4k �������
void MapRander::Jack(){
	float tim_ss;
	int mmni = 0;
	int kback = 0b1111;
	tim_ss = timsd / subdivision; //������ļ��
	for (offset = times; offset <= timee; offset += tim_ss) {
	back:key = Rd(15, 1);                                       //�����һ���ĵļ���
		if ((key & kback)==0){                                                  //�ж��Ƿ�Ϊ��
			goto back;
		}
		else
		{
			if (0 != mmni % subdivision && 15 == key){                //�ж���ѹ�Ƿ���1/1����
				goto back;
			}
			else
			{
				if (Dsr == 1){                                 //�ж��Ƿ�������
					if (key == 0b1000 || key == 0b0100 || key == 0b0010 || key == 0b0001){//ɾ������
						goto back;
					}
					else{
						 KeyOut();
						 kback = key;
					}
				}
				else{                                          //������������
					 KeyOut();
					kback = key;
				}
			}
		}
		mmni = mmni + 1;                                  //���ļ���
	}

}
//tech���
void MapRander::Tech()
{
	float tim_ss;
	float time = 0;
	int rd1 = 0;
	tim_ss = timsd / subdivision;
	int jud = 0;
	int kback = 0b1111;
	for (offset = times; offset <= timee; offset += tim_ss){
	back:key = Rd(15, 1);
		rd1 = Rd(3, 0);
		if ((key & kback)==0){                               //�жϼ���
			time = time - tim_ss / 2;
			 KeyOut();
			kback = key;
		}
		else{
			rd1 = Rd(3, 0);                         //�������
			if (rd1 == 0){							//���������1/4���ʱ���
				KeyOut();
				kback = key;
			}
			else{
				goto back;
			}
		}
	}
}
//�������
void MapRander::Stream(){
	float tim_ss;
	int mmni = 0;
	int rd1 = 0;
	int kback = 0b0000;
	tim_ss = timsd / subdivision;
	for (offset = times; offset <= timee; offset += tim_ss){
	back:key = Rd(15, 1);
		if ((key & kback) == 0 && (key & kback) != 15){                 //ɸѡ����
			rd1 = Rd(3, 0);
			if (Dsr == 0){                                //���ۺ����
				if (rd1 == 1 && (key == 0b1110 || key == 0b1011 || key == 0b1101 || key == 0b1110)){ //����3ѹ���
					KeyOut();
					kback = key;
				}
				else{
					KeyOut();
					kback = key;
				}
			}
			else if (Dsr == 1){                               //�������
				if (1 != mmni % 2 && (key == 0b1000 || key == 0b0100 || key == 0b0010 || key == 0b0001))  {//ȷ����ѹ������1/1��1/2����
				}
				else if (0 != mmni % subdivision && (key == 0b1110 || key == 0b1011 || key == 0b1101 || key == 0b1110)){//ȷ��3ѹ��1/1����
					goto back;
				}
				else{
					 KeyOut();
					 kback = key;
				}
			}
			else {                                      //ǿ�����
				if ((key == 0b1000 || key == 0b0100 || key == 0b0010 || key == 0b0001) && 1 != mmni % 2){  //ȷ����ѹ������1/1��1/2����
					goto back;
				}
				else if ((key == 0b1000 || key == 0b0100 || key == 0b0010 || key == 0b0001) && 0 == rd1){   //���ٵ�ѹ���
					goto back;
				}
				else{
					KeyOut();
					kback = key;
				}
			}
		}
		else{
			goto back;
		}
		mmni = mmni + 1;
	}
}
//�������
void MapRander::Speed(){
	float tim_ss;
	int mmni = 0;
	int rd1 = 0, rd2 = 0;
	int kback = 0b0000, kback1 = 0b0000, kback2 = 0b0000;                                    //���ں����ж�121���͵���ʱֵ
	tim_ss = timsd / subdivision;
	for (offset = times; offset <= timee; offset += tim_ss){
		kback2 = kback1;
		kback1 = kback;
	back:key = Rd(14, 1);    //�ų���ѹ
		rd1 = Rd(3, 0);
		if ((key & kback) == 0) {          //�������������
			if (Dsr == 0) {        //�ҳ���
				if (key == 0b0111 || key == 0b1011 || key == 0b1101 || key == 0b1110) {  //��ȫ�ų�3ѹ
					goto back;
				}
				else if (rd1 == 1 && (key != 0b1000 || key != 0b0100 || key != 0b0010 || key != 0b0001) && mmni % subdivision == 0){//����˫ѹ���
					KeyOut();
					kback = key;
				}
				else if (key == 0b1000 || key == 0b0100 || key == 0b0010 || key == 0b0001){    //��ѹ���
					if (kback2 == key && rd1 == 0) {                   //����121�����
						goto back;
					}
					else{
						KeyOut();
						kback = key;
					}
				}
				else{  
					goto back;
				}
			}
			else {           //����
				if (key == 0b0111 || key == 0b1011 || key == 0b1101 || key == 0b1110){     //��ȫ�ų�3ѹ
					goto back;
				}
				else if (rd1 == 1 && (key != 0b1000 || key != 0b0100 || key != 0b0010 || key != 0b0001) && (mmni % (subdivision / 2) == 0 || mmni % subdivision == 0)){//����˫ѹ���
					KeyOut();
					kback = key;
				}
				else if (key == 0b1000 || key == 0b0100 || key == 0b0010 || key == 0b0001){        //��ѹ���
					if (kback2 == key){             //ɾ��121�����
						goto back;
					}
					else{
						KeyOut();
						kback = key;
					}
				}
				else{
					goto back;
				}
			}
		}
		else{
			goto back;
		}
		mmni = mmni + 1;
	}
}
