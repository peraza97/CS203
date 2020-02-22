#ifndef __CACHE__H__
#define __CACHE__H__

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <cmath>

#include "util.h"

using namespace std;

class Cache{
    private:
        int cacheSize;
        int blockSize;
        int sets;
        int nWays; //1: direct, 0: fully associative
        int indexbits, tagBits, offsetBits, LRUBits; 
        int misses;
        int totalAccesses;
        bool debug;
    public:
        Cache(int, int, int, bool);

};

#endif