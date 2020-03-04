#ifndef __CACHELINE_H__
#define __CACHELINE_H__

#include <iostream>
#include <sstream>
#include <map>
#include <list>
#include <unordered_map>

using namespace std;

typedef list<uint32_t> tagList;
typedef tagList::iterator tagIter;

class CacheLine{
    private:
        int maxSize;
        unordered_map<uint32_t,tagIter > tagMap;
        tagList line;
    public:
        CacheLine();
        CacheLine(int);
        int getCapacity();
        void setCapacity(int);
        int access(uint32_t);
        string str();
};

#endif