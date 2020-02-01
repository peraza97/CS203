#ifndef __BRANCH_H_
#define __BRANCH_H_
#include "bht.h"
#include <iostream>
using namespace std;

class Predictor{
    private:

        BHT branchHistoryTable; //keep a record of my branch history table
        unsigned char addrLength; //number of bits of address used to index
        int correct;
        int total;
        bool debug;

        unsigned short convertAddress(string);

    public:
        Predictor(unsigned char, unsigned char, unsigned char, bool);
        void makePrediction(string, bool);
        void printRates();
};

#endif