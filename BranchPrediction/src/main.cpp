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
	unsigned char m = 0; //branch history (up to 12)
    unsigned char n = 1; //n-bit predictor ( 1 or 2)
    unsigned char addressBits = 8; //how many bits of address is used (up to 12)
    bool debug = false;
	string fileName = "text/test.txt";
	while ((opt = getopt(argc,argv,"f:m:n:a:d")) != EOF){
        switch(opt){
            case 'f': fileName.assign(optarg); break;
            case 'm': m = atoi(optarg); break;
            case 'n': n = atoi(optarg); break;
            case 'a': addressBits = atoi(optarg); break;
            case 'd': debug = true; break;
            case '?': printf("usuage is \n -f : fileName \n -m : history length\n -n : n-bit\n -a : address length\n");
            default: exit(1);
        }
    }
    Application app(fileName);
    app.InitApplication();
    Predictor pred(m,n, addressBits, debug);

    string address = "";
    bool expected;
    while(!app.done()){
        app.getBranch(address,expected);
        pred.makePrediction(address,expected);
    }
    pred.printRates();
    return 0;
}