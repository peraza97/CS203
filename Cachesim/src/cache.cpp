#include "cache.h"

Cache::Cache(int cacheSize, int blockSize, int nWays, bool debug){
    this->cacheSize = cacheSize;
    this->blockSize = blockSize;
    this->nWays = nWays;
    this->misses = 0;
    this->totalAccesses = 0;
    this->debug = debug;

    //calculate offset bits
    this->offsetBits = log2(blockSize);

    //fully associative
    if(nWays == 0){
        this->indexbits = 0;
    }
    else{
        int cacheBits = log2(cacheSize);
        int tempWays = log2(nWays);
        this->indexbits = cacheBits - this->offsetBits - tempWays;
    }

    this->sets = pow(2,this->indexbits);
    this->tagBits = ADDRESS_LENGTH - this->indexbits - this->offsetBits;

    printf("Cache size: %d\nBlock Size: %d\nSets: %d\nWays: %d\nTag bits: %d\nIndex bits: %d\nOffset bits: %d\n", 
            this->cacheSize, this->blockSize, this->sets, this->nWays, this->tagBits, this->indexbits, this->offsetBits);
}