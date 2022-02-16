#include "MapRanderMania--.h"
using namespace std;


void main() {
	


	MapRander *mR = new MapRander;
	mR->MrMain();
}






/*int tim;
	int stdx,stdxl, stdy,stdyl;
	int x, xl;
	int key;
	bool drum;
	int p;
	ifstream ifs;
	stdxl = rand() % 1180 + 50;
	stdyl = rand() % 620 + 50;
	xl = rand() % 1180 + 50;
	srand((unsigned)time(NULL)+rand()%50000);
	ifs.open("test.osu",ios::in);
	while (ifs >> tim) {
		do {
			stdx = rand() % 1180 + 50;
			stdy = rand() % 620 + 50;
			p = sqrt((stdx - stdxl) * (stdx - stdxl) + (stdy - stdyl) * (stdy - stdyl));
		} while (!(p<500&&p>50));
		stdxl = stdx;
		stdyl = stdy;
		do {
			x = rand() % 1180 + 50;
			p = (x - xl);
		} while (!(p>20&&p<400));
		xl = x;
		key = rand() % 4;
		drum = rand() % 2;
		printf("%d %d %d %d %d %d\n", tim, stdx, stdy, key, x, drum);
	}
	ifs.close();
	system("pause");

	for (int b = 3500; b < 45000; b += 30) {
		printf("%d 510 160 3 120 1\n", b);

	}

	system("pause");*/