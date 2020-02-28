#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <iostream>
#include "app.h"
#include "cache.h"

using namespace std;

int main(int argc, char ** argv){
	int opt;

	string fileName = "files/test.txt";
    string cacheString = "4KB";
    string blockString = "16B";
    int nWays = 1;
    bool debug = false;

	while ((opt = getopt(argc,argv,"f:c:b:w:d")) != EOF){
        switch(opt){
            case 'f': fileName.assign(optarg); break;
            case 'c': cacheString.assign(optarg); break;
            case 'b': blockString.assign(optarg); break;
            case 'w': nWays = atoi(optarg); break;
            case 'd': debug = true; break;
            case '?': printf("usuage is \n -f : fileName \n -c : cache size\n -b : block size\n -w : N-ways\n");
            default: exit(1);
        }
    }

    int cacheSize = convertSizeInput(cacheString);
    int blockSize = convertSizeInput(blockString);
    if(cacheSize == 0 || blockSize == 0 || (cacheSize < blockSize)){
        printf("Error assigning cacheSize or block size\n");
        return -1;
    }

    Application app(fileName);
    app.InitApplication();

    unsigned char memType;
    int offset;
    string address = "";
    Cache myCache(cacheSize, blockSize, nWays, debug);
    while(app.getMemoryAccess(memType, offset, address)){
       myCache.checkCache(address, offset);
    }
    myCache.printRates();

    return 0;
}