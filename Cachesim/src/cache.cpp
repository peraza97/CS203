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
        int cacheBits = log2(cacheSize);
        this->nWays = nWays;
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
    uint32_t conversion32;
    converter >> std::hex >> conversion;

    //add the addressOffset to the address
    conversion += addressOffset;
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
        printf("address - offest: %lu\n",(unsigned long)conversion32);
        printf("%s\n", formatAddress(conversion32,this->tagBits, this->indexbits, this->offsetBits).c_str() );   
        printf("offset: %lu\n",(unsigned long)offset);
        printf("index: %lu\n",(unsigned long)index);
        printf("tag: %lu\n",(unsigned long)tag);   
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

cacheLine Cache::populateLine(){
    cacheLine result;
    for(int i = 0; i < this->nWays; ++i){
        result.push_back({0,0,0,0});
    }
    return result;
}

bool Cache::accessCache(uint32_t tag, uint32_t index){
    if(this->cacheSets[index].size() == 0){
        this->cacheSets[index] = this->populateLine();
    }

    int pos = -1;
    int validPos = -1;
    int maxPos = 0;
    //iterate over the cacheSet
    for(int i = 0; i < this->nWays; ++i){
        if(!this->cacheSets[index][i].validBit){
            validPos = i;
            break;
        }
        else if(this->cacheSets[index][i].validBit && this->cacheSets[index][i].tag == tag){
                pos = i;
        }
        else{
            this->cacheSets[index][i].lruBit+=1; //increment its lru bit
            if(this->cacheSets[index][i].lruBit > this->cacheSets[index][maxPos].lruBit){
                maxPos = i;
            }
        }
    }
    if(pos != -1){
        this->cacheSets[index][pos].lruBit = 0;
    }
    else if(pos == -1 && validPos != -1){
        this->cacheSets[index][validPos].validBit = 1;
        this->cacheSets[index][validPos].tag = tag;
        this->cacheSets[index][validPos].lruBit = 0;    
    }
    else{
        this->cacheSets[index][maxPos].tag = tag;
        this->cacheSets[index][maxPos].lruBit = 0;
    }

    if(this->debug){
        printf("\nCacheLine Update:\n");
        this->printCacheLine(this->cacheSets[index]);
    }
    return pos != -1;
}

void Cache::checkCache(string address, int addressOffset){
    bits_t bits = this->parseAddress(address, addressOffset);
    bool hit = this->accessCache(bits.tag, bits.index);
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
        printf("Misclassification rate: %.2f%%\n", 100.00 * (1 - (double)(this->hits)/this->totalAccesses));
    } 
    if(this->debug){
    printf("Hits: %d\n", this->hits);
    printf("total: %d\n",this->totalAccesses);
    }
}