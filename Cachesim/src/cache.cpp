#include "cache.h"

Cache::Cache(uint32_t cacheSize, uint32_t blockSize, int nWays, bool debug){
    this->cacheSize = cacheSize;
    this->blockSize = blockSize;
    this->hits = 0;
    this->totalAccesses = 0;
    this->debug = debug;

    //calculate offset bits
    this->offsetBits = log2(blockSize);

    //fully associative
    if(nWays == 0){
        this->indexbits = 0;
        this->nWays = this->cacheSize/this->blockSize;
    } 
    //direct or n-sets
    else{
        this->nWays = nWays;
        int cacheBits = log2(cacheSize);
        int waysBits = log2(nWays);
        this->indexbits = cacheBits - this->offsetBits - waysBits;
    }

    this->sets = pow(2,this->indexbits);
    this->tagBits = ADDRESS_LENGTH - this->indexbits - this->offsetBits;

    printf("------------------------------\n");
    printf("Cache size: %" PRIu32 " Byte(s)\nBlock Size: %" PRIu32 " Byte(s)\nSets: %d\nWays: %d\nTag bits: %d\nIndex bits: %d\nOffset bits: %d\n", 
            this->cacheSize, this->blockSize, this->sets, this->nWays, this->tagBits, this->indexbits, this->offsetBits);
    printf("------------------------------\n");
}

bits_t Cache::parseAddress(string address, int addressOffset){
    istringstream converter(address);
    uint64_t conversion;
    converter >> std::hex >> conversion;

    //add the addressOffset to the address
    conversion += addressOffset;

    uint32_t conversion32;
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
        printf("Offset: %d\n",addressOffset);
        printf("address + offest: %lu\n",(unsigned long)conversion32);
        printf("%s\n", formatAddress(conversion32,this->tagBits, this->indexbits, this->offsetBits).c_str() );   
        printf("tag: %" PRIu32 "\n",(uint32_t)tag);
        printf("index: %" PRIu32 "\n",(uint32_t)index);   
        printf("offset: %" PRIu32 "\n",(uint32_t)offset);

    }  
    bits_t parts = { (uint32_t)tag, (uint32_t)index, (uint32_t)offset} ;
    return parts;
}

void Cache::printRates(){ 
    if(this->totalAccesses == 0){
        printf("Error, Cannot get rate \n");
    }
    else{
        printf("Hit rate: %.2f%%\n", 100.00 * (double)(this->hits)/this->totalAccesses);
        printf("Miss rate: %.2f%%\n", 100.00 * (1 - (double)(this->hits)/this->totalAccesses));
    } 
    printf("Hits: %d\n", this->hits);
    printf("total: %d\n",this->totalAccesses);
    printf("------------------------------\n\n"); 
}

bool Cache::accessCacheLine(uint32_t index, uint32_t tag){
    bool hit;
    if(this->cacheSets[index].getCapacity() == 0){
        this->cacheSets[index].setCapacity(this->nWays);
    }
    hit = this->cacheSets[index].access(tag);
    return hit;
}

void Cache::checkCache(string address, int addressOffset){
    bits_t bits = this->parseAddress(address, addressOffset);
    bool hit = this->accessCacheLine(bits.index, bits.tag);
    if(hit){
        this->hits += 1;
    }
    this->totalAccesses += 1;
    if(this->debug){
        printf("\n%s\n", (hit ? "Hit" : "Miss"));
        printf("------------------------------\n");
    }
}