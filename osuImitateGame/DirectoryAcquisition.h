#pragma once
#include "libH.h"

class DirectoryAcquisition {
public:


	string* DirectoryName;//文件名

	int dirNub;            //文件数量


	DirectoryAcquisition();

	void listFiles(const char* dir);
	//void listFilesN(const char* dir);

	~DirectoryAcquisition();
};
