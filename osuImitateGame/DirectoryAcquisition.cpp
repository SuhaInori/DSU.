#include "DirectoryAcquisition.h"

//获取目录下的dsz文件
char dir[20] = "./file/dszFil/";
DirectoryAcquisition::DirectoryAcquisition() {
   
	strcat(dir, "*.dsz*");
	listFiles(dir);
}

void DirectoryAcquisition ::listFiles(const char* dir){
    intptr_t handle;
    _finddata_t findData;
    dirNub = 0;
    int index = 0;
    handle = _findfirst(dir, &findData);    // 查找目录中的第一个文件
    if (handle == -1){
        cout << "Failed to find first file!\n";
        return;
    }
    do
    {
        dirNub++;
    } while (_findnext(handle, &findData) == 0);    // 查找目录中的下一个文件
    DirectoryName = new string[dirNub];
    handle = _findfirst(dir, &findData);
    do
    {
        char* name = NULL;
            name = findData.name;
        this->DirectoryName[index] =name;
        index++;

    } while (_findnext(handle, &findData) == 0);    // 查找目录中的下一个文件
    _findclose(handle);    // 关闭搜索句柄
}
DirectoryAcquisition::~DirectoryAcquisition() {
    if (DirectoryName != NULL) {
        delete[] DirectoryName;
        DirectoryName = NULL;
    }
}

//void DirectoryAcquisition::listFilesN(const char* dir) {
//    int i = 0;
//    int filesize = 0;
//    DIR* dir = NULL;
//    struct dirent* entry;
//
//    if ((dir = opendir(FilePath)) == NULL)
//    {
//        printf("opendir failed!");
//        return -1;
//    }
//    else
//    {
//        while (entry = readdir(dir))
//        {
//            i++;
//            printf("filename%d = %s", i, entry->d_name);  //输出文件或者目录的名称
//            printf("filetype = %d\n", entry->d_type);  //输出文件类型   
//        }
//
//        closedir(dir);
//    }
//
//}