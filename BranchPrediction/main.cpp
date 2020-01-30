#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <iostream>
#include "app.h"
#include "predictor.h"
#include "oneBit.h"
#include "twoBit.h"

using namespace std;

int main(int argc, char ** argv){
	int opt;
	int option = 1;
	string fileName = "text/gcc-10K.txt";
	while ((opt = getopt(argc,argv,"p:f:")) != EOF){
        switch(opt){
            case 'p': option = atoi(optarg); break;
            case 'f': fileName.assign(optarg); break;
            case '?': cout << "usuage is \n -f fileName : to run input file fileName \n -p : predictor type (1. 1 bit predictor, 2. 2 bit predictor, 3. Correlating predictor) " << endl;
            default: exit(1);
        }
    }

    Predictor * pred;
    switch (option){
        case 1:
            pred = new OneBit();
            cout << "Predictor option: " << "One bit" << endl;
            break;
        case 2:
            pred = new TwoBit();
            cout << "Predictor option: " << "Two bit" << endl;
            break;
        default:
            cout << "Invalid predictor option. Choose\n1. 1 bit predictor\n2. 2 bit predictor\n3. Correlating predictor" << endl;
            exit(1);
            break;
    }

    Application app(fileName);
    app.InitApplication();
    
    string addr = "";
    bool result = 0;

    cout << "Begining branch predictions" << endl;
    while(!app.done()){
        app.getBranch(addr, result);
        pred->makePrediction(addr, result);
    }
    pred->printStats();
    return 0;
}