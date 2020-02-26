#ifndef __CACHE__H__
#define __CACHE__H__

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <cmath>
#include <sstream>
#include "util.h"

using namespace std;

struct address_t{
    uint32_t tag;
    uint32_t index;
    uint32_t offset;
};

class Cache{
    private:
        int cacheSize;
        int blockSize;
        int sets;
        int nWays; //1: direct, 0: fully associative
        bool debug;
        int indexbits, tagBits, offsetBits, LRUBits; 
        int misses;
        int totalAccesses;
    public:
        Cache(int, int, int,bool);
        address_t parseAddress(string);

};

#endif