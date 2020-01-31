#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <iostream>
#include "app.h"
#include "predictor.h"

using namespace std;

int main(int argc, char ** argv){
	int opt;
	int m = 0;
    int n = 0;
	string fileName = "text/gcc-10K.txt";
	while ((opt = getopt(argc,argv,"f:m:n:")) != EOF){
        switch(opt){
            case 'f': fileName.assign(optarg); break;
            case 'm': atoi(optarg); break;
            case 'n': atoi(optarg); break;
            case '?': cout << "usuage is \n -f fileName : to run input file fileName \n -p : predictor type (1. 1 bit predictor, 2. 2 bit predictor, 3. Correlating predictor) " << endl;
            default: exit(1);
        }
    }
    Application app(fileName);
    app.InitApplication();
    
    string addr = "";
    bool result = 0;

    while(!app.done()){
        app.getBranch(addr, result);
    }

    Predictor pred(m,n);
    pred.printRates();

    return 0;
}