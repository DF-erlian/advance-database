#ifndef COMMON_H
#define COMMON_H

#include<list>
#include<unordered_map>

using namespace std;

#define FRAMESIZE 4096
struct bFrame
{
    char field [FRAMESIZE ];
};

#define DEFBUFSIZE 1024
bFrame buf[DEFBUFSIZE]; // or the size that the user defined by the input parameter

struct BCB
{
    int page_id;
    int frame_id;
    int latch;
    int count;
    int dirty;
    BCB * next;
    BCB():page_id(-1),frame_id(-1),latch(0),count(0),dirty(0),next(nullptr){}
};

class LRUMgr{
    private:
        list<int> List;
        unordered_map<int,list<int>::iterator> Map;
    public:
        int size(){
            return List.size();
        }
        bool contian(int key){
            auto t = Map.find(key);
            return t != Map.end();
        }
        bool insert(int key){
            List.push_front(key);
            Map[key] = List.begin();

            if(List.size() > DEFBUFSIZE){
                pop();
            }
        }
        int pop(){
            auto t = List.back();
            List.pop_back();
            Map.erase(t);
            return t;
        }

};

#endif