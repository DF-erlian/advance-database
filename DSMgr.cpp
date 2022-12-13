#include "DSMgr.h"
#include<string>
using namespace std;

//打开文件并初始化pages[],numPages
DSMgr::DSMgr(){
    OpenFile("data.dbf");    
    if(currFile != nullptr){
        Seek(0,0);
        fread(pages,sizeof(pages),1,currFile);
        numPages = pages[MAXPAGES];
    }
}

DSMgr::~DSMgr(){
    CloseFile();
}

//如果文件存在，直接打开，否则先创建文件再打开。
int DSMgr::OpenFile(string filename){
    currFile = fopen(filename.c_str(),"rb+");
    if(currFile == nullptr){
        currFile = fopen(filename.c_str(),"wb+");
        numPages = 0;
        memset(pages,-1,sizeof(pages));
        pages[MAXPAGES] = numPages;
        Seek(0,0);
        fwrite(pages,sizeof(pages),1,currFile);
    }
    return currFile != nullptr;
}

//将pages[]存回文件并关闭文件
int DSMgr::CloseFile(){
    if(currFile != nullptr){
        Seek(0,0);
        pages[MAXPAGES] = numPages;
        fwrite(pages,sizeof(pages),1,currFile);
        fclose(currFile);
    }
    currFile = nullptr;
    return 1;
}

bFrame DSMgr::ReadPage(int page_id){
    bFrame newFrame;
    Seek(pages[page_id]*FRAMESIZE*sizeof(char),sizeof(pages));
    fread(newFrame.field,sizeof(newFrame.field),1,currFile);
    return newFrame;
}

int DSMgr::WritePage(int page_id, bFrame frm){
    if(pages[page_id] == -1){
        pages[page_id] = numPages;
        numPages += 1;
    }
    Seek(pages[page_id]*FRAMESIZE*sizeof(char),sizeof(pages));
    fwrite(frm.field,sizeof(frm.field),1,currFile);
}

int DSMgr::Seek(int offset, int pos){
    return fseek(currFile,offset+pos,SEEK_SET);
}
FILE* DSMgr::GetFile(){
    Seek(0,0);
    return currFile;
}
void DSMgr::IncNumPages(){
    numPages += 1;
}
int DSMgr::GetNumPages(){
    return numPages;
}
void DSMgr::SetUse(int index, int use_bit){    
    pages[index] = use_bit;
}
int DSMgr::GetUse(int index){
    return pages[index];
}
