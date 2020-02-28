#include "cache.h"

Cache::Cache(int cacheSize, int blockSize, int nWays, bool debug){
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
    printf("Cache size: %d\nBlock Size: %d\nSets: %d\nWays: %d\nTag bits: %d\nIndex bits: %d\nOffset bits: %d\n", 
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

void Cache::printCacheLine(cacheLine c){
    for(int i = 0; i < c.size(); ++i){
        printf("%s\t", c[i].str().c_str());
    }
    printf("\n"); 
}

bool Cache::accessCache(uint32_t index, uint32_t tag){
    int pos = -1;
    int maxPos = 0;

    for(int i = 0; i < this->cacheSets[index].size(); ++i){
        if(this->cacheSets[index][i].tag == tag){
                if(pos == -1){
                pos = i;
                }
                else{
                    exit(1); //errrorreoroeoroeroeoroeoeooeor
                }
        }
        else{
            this->cacheSets[index][i].lru+=1; //increment its lru bit
            if(this->cacheSets[index][i].lru > this->cacheSets[index][maxPos].lru){
                maxPos = i;
            }
        }
    }
    if(pos != -1){
        this->cacheSets[index][pos].lru = 0;
    }
    else{
        if(this->cacheSets[index].size() < this->nWays ){
           this->cacheSets[index].push_back({0,tag,0}); 
        }
        else{
            this->cacheSets[index][maxPos].tag = tag;
            this->cacheSets[index][maxPos].lru = 0;
        }
    }
    return pos != -1;
}

void Cache::checkCache(string address, int addressOffset){
    bits_t bits = this->parseAddress(address, addressOffset);
    bool hit = this->accessCache(bits.index, bits.tag);
    if(hit){
        this->hits += 1;
    }
    this->totalAccesses += 1;
    if(this->debug){
        printf("\n%s\n", (hit ? "Hit" : "Miss"));
        printf("------------------------------\n");
    }
}

void Cache::printRates(){ 
    printf("------------------------------\n"); 
    if(this->totalAccesses == 0){
        printf("Error, Cannot get rate \n");
    }
    else{
        printf("Hit rate: %.2f%%\n", 100.00 * (double)(this->hits)/this->totalAccesses);
        printf("Miss rate: %.2f%%\n", 100.00 * (1 - (double)(this->hits)/this->totalAccesses));
    } 
    printf("Hits: %d\n", this->hits);
    printf("total: %d\n",this->totalAccesses);
}