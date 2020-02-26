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

    printf("------------------\n");
    printf("Cache size: %d\nBlock Size: %d\nSets: %d\nWays: %d\nTag bits: %d\nIndex bits: %d\nOffset bits: %d\n", 
            this->cacheSize, this->blockSize, this->sets, this->nWays, this->tagBits, this->indexbits, this->offsetBits);
    printf("------------------\n");
}

address_t Cache::parseAddress(string address){
    istringstream converter(address);
    uint64_t conversion;
    uint32_t conversion32;
    converter >> std::hex >> conversion;
    conversion32 = (uint32_t)(conversion);
    /*calculate the offset */ 
    uint64_t offset = conversion32 << (ADDRESS_LENGTH - this->offsetBits); 
    offset = offset >> (ADDRESS_LENGTH - this->offsetBits);

    /*calculate the index */
    uint64_t index = conversion32 << this->tagBits;
    index = index >> (this->tagBits + this->offsetBits);

    /*calculate the tag */
    uint64_t tag = conversion32 >> (this->offsetBits + this->indexbits);

    if(this->debug){
        printf("Address: %s\n",address.c_str());
        printf("%s\n", formatAddress(conversion32,this->tagBits, this->indexbits, this->offsetBits).c_str() );   
        printf("offset: %lu\n",(unsigned long)offset);
        printf("index: %lu\n",(unsigned long)index);
        printf("tag: %lu\n",(unsigned long)tag);   
    }  
    address_t parts = { (uint32_t)tag, (uint32_t)index, (uint32_t)offset} ;
    return parts;
}