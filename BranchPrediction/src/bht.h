#ifndef __BHT_H_
#define __BHT_H_

#include <stdio.h>
#include <iostream>
#include <map>
#include "nBit.h"
using namespace std;

class BHT{
    private:
        GlobalBranchHistoryTables globalTables;
        unsigned char historyBits;
        unsigned char (*NBitFunction)(unsigned char,bool); //n-bit predictor function updates state with bool
        unsigned char (*prediction)(unsigned char); //converting states to 0 or 1 prediction
        string (*strConversion)(unsigned char); //converting states to 0 or 1 prediction
        
        unsigned short history;
        bool debug;
        string getBinary(unsigned short); // get binary rep. of history
        void updateHistory(bool); //update the history

    public:
        BHT(unsigned char, unsigned char, bool); //short is history length, char is nbit
        bool predictBranch(unsigned short,bool);
};

#endif 
