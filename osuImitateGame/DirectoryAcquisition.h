#pragma once
#include "libH.h"

class DirectoryAcquisition {
public:


	string* DirectoryName;//�ļ���

	int dirNub;            //�ļ�����


	DirectoryAcquisition();

	void listFiles(const char* dir);
	//void listFilesN(const char* dir);

	~DirectoryAcquisition();
};
