#ifndef DATA_STORAGE_MANAGER_H
#define DATA_STORAGE_MANAGER_H

#include<iostream>
#include<string>
#include "common.h"

using namespace std;

#define MAXPAGES 50000
class DSMgr
{
    public:
        DSMgr();
        int OpenFile(string filename);
        int CloseFile();
        bFrame ReadPage(int page_id);
        int WritePage(int page_id, bFrame frm);
        int Seek(int offset, int pos);
        FILE * GetFile();
        void IncNumPages();
        int GetNumPages();
        void SetUse(int index, int use_bit);
        int GetUse(int index);
    private:
        FILE *currFile;
        int numPages;//位于文件头部的首位
        int pages[MAXPAGES+1];//文件目录,存放于文件的头部。值为-1表示页不存在。
};

/*文件的格式如下：
使用pages[0-(MAXPAGES-1)]当作文件目录,pages[MAXPAGES]用于存放numpages
pages[0-49,999]表示0-49,999号页
---------------------
头部：numPages,[pages]
实体：真正文件的存放处
---------------------
*/
#endif