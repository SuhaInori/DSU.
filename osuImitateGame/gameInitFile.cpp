#include "gameInitFile.h"

//��ȡ�����ļ�
gameInitFile::gameInitFile() {
	std::ifstream pac("./file/configurationfile.cfg", std::ios::in | std::ios::binary);
	pac.read((char*)this, sizeof(*this));
	pac.close();
}


void gameInitFile::addExp(int exp) {
	this->exp = this->exp + exp;
	if (this->exp >= lv * 2000 + 1000) {
		this->exp = this->exp - lv * 2000 + 1000;
		lv++;
	}
}


//imageLibͼƬ����
gameInitFile::~gameInitFile() {
	ofstream ejz("./file/configurationfile.cfg", ios::out | ios::binary);//ejz.open("person.classGrop", ios::out|ios::binary);
	ejz.write((const char*)this, sizeof(*this));
	ejz.close();
}
