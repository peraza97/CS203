#ifndef __CACHE__H__
#define __CACHE__H__

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <inttypes.h>
#include "util.h"
#include "cacheLine.h"

using namespace std;

typedef unordered_map<uint32_t, CacheLine> cache_t;

struct bits_t{
    uint32_t tag;
    uint32_t index;
    uint32_t offset;
};

class Cache{
    private:
        uint32_t cacheSize;
        uint32_t blockSize;
        int sets;
        int nWays; //1: direct, 0: fully associative
        bool debug;
        int indexbits, tagBits, offsetBits; //bit assignment
        int hits;
        int totalAccesses;
        cache_t cacheSets;

        bits_t parseAddress(string, int);
        bool accessCacheLine(uint32_t, uint32_t);

    public:
        Cache(uint32_t, uint32_t, int, bool);
        void checkCache(string, int);
        void printRates();

};

#endif