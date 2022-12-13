#ifndef BUFFER_MANAGER_H
#define BUFFER_MANAGER_H

#include "common.h"
#include "DSMgr.h"

struct Page{
    int page_id;
    int frame_id;

    Page():page_id(-1),frame_id(-1){}
    Page(int _page_id,int _frame_id):page_id(_page_id),frame_id(_frame_id){}
};
class BMgr{
    public:
        BMgr();
        // Interface functions
        
        int FixPage(int page_id, int protection);
        // 该函数返回一个frame_id。
        // 文件与访问管理器将会传递一个page_id来调用相关page，此处的page_id与记录中的record_id相对应。
        // 该函数查看所需page是否已经在buffer中，若存在返回它对应的frame_id。
        // 若该页不在内存，该函数选择一个victim page，并且若有需要加载所需page。

        Page FixNewPage();
        // 它返回一个page_id和frame_id。
        // 当产生插入，目录分割或创建对象等操作时，该函数被调用，用来产生一个新的page。
        // 该函数的返回值是与record_id或元数据相对应的page_id。这个函数将会寻找一个空页面，供给文件与访问管理器存放数据。

        int UnfixPage(int page_id);
        // 它返回一个frame_id。该函数是与FixPage或FixNewPage配合使用。
        // 这个函数每次将frame上的fix count减一。 
        // 当数量为0时，对page的占用就被解除，若被选中frame可以被移除。
        // page_id可以被转化成frame_id并且它可以被解除占用。当一个页面上的count等于0时，该页面可以被选为victim page。
       
        int NumFreeFrames();
        // NumFreeFrame查看buffer返回空闲可用的buffer page数量。
        // 该函数在使用N-路排序中非常有用。
        // 该函数的原型是 NumFreeFrames()，返回值为一个整数，范围为 0 -BUFFERSIZE-1(1023).

    private:
        // Hash Table
        int ftop[DEFBUFSIZE];//frame_id --> page_id
        BCB* ptof[DEFBUFSIZE];//page_id --> frame_BCB,以链表形式组织

        DSMgr Disk_Manager;
        LRUMgr LRU;

        // Internal Functions
        int SelectVictim();
        int Hash(int page_id);
        void RemoveBCB(BCB * ptr, int page_id);
        void RemoveLRUEle(int frame_id);
        void SetDirty(int frame_id);
        void UnsetDirty(int frame_id);
        void WriteDirtys();
        void PrintFrame(int frame_id);
};
#endif