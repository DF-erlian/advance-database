#include "BMgr.h"

BMgr::BMgr(){
    memset(ftop,-1,sizeof(ftop));
    for(int i = 0; i < DEFBUFSIZE; i++){
        ptof[i] = nullptr;
    }
}

int BMgr::FixPage(int page_id, int protection){
    BCB* iterator = ptof[page_id % DEFBUFSIZE];
    //在buffer中
    while(iterator != nullptr){
        if(iterator->page_id == page_id){
            return iterator->frame_id;
        }
    }
    //不在buffer中
    int vicFrame = SelectVictim();

}

Page BMgr::FixNewPage(){

}

int BMgr::UnfixPage(int page_id){

}

int BMgr::NumFreeFrames(){
    return DEFBUFSIZE - LRU.size();
}

int BMgr::SelectVictim(){
    //buffer 未满
    if(LRU.size() < DEFBUFSIZE){
        return LRU.size();
    }
    //buffer 已满
    return LRU.pop();

}

int BMgr::Hash(int page_id){

}

void BMgr::RemoveBCB(BCB* ptr, int page_id){

}

void BMgr::RemoveLRUEle(int frame_id){

}

void BMgr::SetDirty(int frame_id){

}

void BMgr::UnsetDirty(int frame_id){

}
void BMgr::WriteDirtys(){

}
void BMgr::PrintFrame(int fram_id){

}
