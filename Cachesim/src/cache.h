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
#include "util.h"

using namespace std;

struct block{
    int validBit;
    int lruBit;
    uint32_t tag;
    int data;
    string str(){
        ostringstream oss;
        oss << "|v: " << validBit << ", lru: " << lruBit << ", tag: " << tag << "|";
        return oss.str();
    }
};

typedef vector<block> cacheLine;
typedef unordered_map<uint32_t, cacheLine> cache_t;


struct bits_t{
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
        int indexbits, tagBits, offsetBits; 
        int hits;
        int totalAccesses;
        cache_t cacheSets;

        bits_t parseAddress(string, int);
        void printCacheLine(cacheLine);
        cacheLine populateLine();
        bool accessCache(uint32_t, uint32_t);

    public:
        Cache(int, int, int,bool);
        void checkCache(string, int);
        void printRates();

};

#endif