#ifndef __BRANCH_H_
#define __BRANCH_H_
#include "bht.h"
#include "util.h"

#include <iostream>
using namespace std;

class Predictor{
    private:

        BHT branchHistoryTable; //keep a record of my branch history table
        unsigned char addrBits; //number of bits of address used to index
        unsigned char historyBits; //number of bits used for history
        unsigned short history; //record of global histroy
        int correct;
        int total;
        bool debug;
        unsigned short convertAddress(string);
        void updateHistory(bool); //update the history

    public:
        Predictor(unsigned char, unsigned char, unsigned char, bool);
        void makePrediction(string, bool);
        void printRates();
};

#endif