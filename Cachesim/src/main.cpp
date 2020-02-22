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
    bool debug = false;
    int cacheSize = 65536;
    int blockSize = 16;
    int nWays = 2;
	while ((opt = getopt(argc,argv,"f:c:b:w:d")) != EOF){
        switch(opt){
            case 'f': fileName.assign(optarg); break;
            case 'c': cacheSize = atoi(optarg); break;
            case 'b': blockSize = atoi(optarg); break;
            case 'w': nWays = atoi(optarg); break;
            case 'd': debug = true; break;
            case '?': printf("usuage is \n -f : fileName \n -c : cache size\n -b : block size\n -w : N-ways\n");
            default: exit(1);
        }
    }
    Application app(fileName);
    app.InitApplication();

    unsigned char memType;
    int offset;
    string address = "";
    Cache myCache(cacheSize, blockSize, nWays, debug);
    /*
    while(app.getMemoryAccess(memType, offset, address)){
        printf("%u %d %s\n", memType, offset, address.c_str());
    }
    */

    return 0;
}