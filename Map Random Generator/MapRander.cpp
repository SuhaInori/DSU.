#include "MapRanderMania--.h"


int MapRander::MrMain() {
	mode=0;
	bool flag=true;
	while (flag){
		system("cls");
		std::cout << "-----------谱面随机生成器------------" << std::endl;
		std::cout << "选择生成的键型" << std::endl;
		std::cout << "0.全随机" << std::endl;
		std::cout << "1.jack" << std::endl;
		std::cout << "2.tech" << std::endl;
		std::cout << "3.stream" << std::endl;
		std::cout << "4.speed" << std::endl;
		std::cin >> mode;
		std::cout << "谱面开始时间" << std::endl;
		std::cin >> times;
		std::cout << "谱面结束时间" << std::endl;
		std::cin >> timee;
		std::cout << "谱面bpm" << std::endl;
		std::cin >> bpm;
		std::cout << "谱面节拍细分" << std::endl;
		std::cin >> subdivision;
		timsd = 60000 / bpm;
		if (mode == 0) {
			std::cout << "准备就绪......" << std::endl;
			system("pause");
			system("cls");
			RandKey();
		}
		else if (mode == 1) {
			std::cout << "叠键型：0.叠常规 1.大叠" << std::endl;
			std::cin >> Dsr;
			std::cout << "准备就绪......" << std::endl;
			system("pause");
			system("cls");
			Jack();
		}
		else if (mode == 2) {
			std::cout << "准备就绪......" << std::endl;
			system("pause");
			system("cls");
			Tech();
		}
		else if (mode == 3) {
			std::cout << "切键型：0.切常规 1.中切 2 强切" << std::endl;
			std::cin >> Dsr;
			std::cout << "准备就绪......" << std::endl;
			system("pause");
			system("cls");
			Stream();
		}
		else if (mode == 4) {
			std::cout << "乱键型：0.乱常规 1.大乱" << std::endl;
			std::cin >> Dsr;
			std::cout << "准备就绪......" << std::endl;
			system("pause");
			system("cls");
			Speed();
		}
		system("pause");
		system("cls");
		std::cout << "是否继续？ 0 or 1 " << std::endl;
		std::cin >> flag;
	}
	return 1;
}
//a为随机数范围（0~a-1);b为起始点
int MapRander::Rd(int Range, int MixVal){	//返回整形随机数
	srand((unsigned)time(NULL) + (unsigned)rand() - (unsigned)rand() % 3);
	int temp = 0;
	temp = rand() % Range + MixVal;
	return temp;
}
void  MapRander::KeyOut(){//一维键型库 及调用 调用规则（0000 出1为对应键型输出；如:1000 输出1号轨道）
	int t;
	t = offset;
	int b = 0;
	if (key == 0b1000){//a 为一维键型的表示方式  
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
	float tim_ss;//每小拍时间间隔
	tim_ss = timsd / subdivision;
	for (offset = times; offset <= timee; offset += tim_ss)
	{
		key = Rd(15, 1);
		KeyOut();
	}
}
//4k 叠型输出
void MapRander::Jack(){
	float tim_ss;
	int mmni = 0;
	int kback = 0b1111;
	tim_ss = timsd / subdivision; //计算节拍间隔
	for (offset = times; offset <= timee; offset += tim_ss) {
	back:key = Rd(15, 1);                                       //随机下一节拍的键型
		if ((key & kback)==0){                                                  //判断是否为叠
			goto back;
		}
		else
		{
			if (0 != mmni % subdivision && 15 == key){                //判断四压是否在1/1拍上
				goto back;
			}
			else
			{
				if (Dsr == 1){                                 //判断是否输出大叠
					if (key == 0b1000 || key == 0b0100 || key == 0b0010 || key == 0b0001){//删除单键
						goto back;
					}
					else{
						 KeyOut();
						 kback = key;
					}
				}
				else{                                          //随机输出叠键型
					 KeyOut();
					kback = key;
				}
			}
		}
		mmni = mmni + 1;                                  //节拍计数
	}

}
//tech输出
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
		if ((key & kback)==0){                               //判断键型
			time = time - tim_ss / 2;
			 KeyOut();
			kback = key;
		}
		else{
			rd1 = Rd(3, 0);                         //进行随机
			if (rd1 == 0){							//类叠键型有1/4几率保留
				KeyOut();
				kback = key;
			}
			else{
				goto back;
			}
		}
	}
}
//切型输出
void MapRander::Stream(){
	float tim_ss;
	int mmni = 0;
	int rd1 = 0;
	int kback = 0b0000;
	tim_ss = timsd / subdivision;
	for (offset = times; offset <= timee; offset += tim_ss){
	back:key = Rd(15, 1);
		if ((key & kback) == 0 && (key & kback) != 15){                 //筛选键型
			rd1 = Rd(3, 0);
			if (Dsr == 0){                                //切综合输出
				if (rd1 == 1 && (key == 0b1110 || key == 0b1011 || key == 0b1101 || key == 0b1110)){ //减少3压输出
					KeyOut();
					kback = key;
				}
				else{
					KeyOut();
					kback = key;
				}
			}
			else if (Dsr == 1){                               //中切输出
				if (1 != mmni % 2 && (key == 0b1000 || key == 0b0100 || key == 0b0010 || key == 0b0001))  {//确保单压不会在1/1；1/2拍上
				}
				else if (0 != mmni % subdivision && (key == 0b1110 || key == 0b1011 || key == 0b1101 || key == 0b1110)){//确保3压在1/1拍上
					goto back;
				}
				else{
					 KeyOut();
					 kback = key;
				}
			}
			else {                                      //强切输出
				if ((key == 0b1000 || key == 0b0100 || key == 0b0010 || key == 0b0001) && 1 != mmni % 2){  //确保单压不会在1/1；1/2拍上
					goto back;
				}
				else if ((key == 0b1000 || key == 0b0100 || key == 0b0010 || key == 0b0001) && 0 == rd1){   //减少单压输出
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
//乱型输出
void MapRander::Speed(){
	float tim_ss;
	int mmni = 0;
	int rd1 = 0, rd2 = 0;
	int kback = 0b0000, kback1 = 0b0000, kback2 = 0b0000;                                    //用于后面判断121键型的临时值
	tim_ss = timsd / subdivision;
	for (offset = times; offset <= timee; offset += tim_ss){
		kback2 = kback1;
		kback1 = kback;
	back:key = Rd(14, 1);    //排除四压
		rd1 = Rd(3, 0);
		if ((key & kback) == 0) {          //消除叠类或连点
			if (Dsr == 0) {        //乱常规
				if (key == 0b0111 || key == 0b1011 || key == 0b1101 || key == 0b1110) {  //完全排除3压
					goto back;
				}
				else if (rd1 == 1 && (key != 0b1000 || key != 0b0100 || key != 0b0010 || key != 0b0001) && mmni % subdivision == 0){//控制双压输出
					KeyOut();
					kback = key;
				}
				else if (key == 0b1000 || key == 0b0100 || key == 0b0010 || key == 0b0001){    //单压输出
					if (kback2 == key && rd1 == 0) {                   //减少121型输出
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
			else {           //大乱
				if (key == 0b0111 || key == 0b1011 || key == 0b1101 || key == 0b1110){     //完全排除3压
					goto back;
				}
				else if (rd1 == 1 && (key != 0b1000 || key != 0b0100 || key != 0b0010 || key != 0b0001) && (mmni % (subdivision / 2) == 0 || mmni % subdivision == 0)){//控制双压输出
					KeyOut();
					kback = key;
				}
				else if (key == 0b1000 || key == 0b0100 || key == 0b0010 || key == 0b0001){        //单压输出
					if (kback2 == key){             //删除121型输出
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
