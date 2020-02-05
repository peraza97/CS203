#ifndef __BHT_H_
#define __BHT_H_

#include <stdio.h>
#include <iostream>
#include <map>
#include "util.h"
using namespace std;

class BHT{
    private:
        GlobalBranchHistoryTables globalTables;
        unsigned char (*NBitFunction)(unsigned char,bool); //n-bit predictor function updates state with bool
        unsigned char (*prediction)(unsigned char); //converting states to 0 or 1 prediction
        string (*strConversion)(unsigned char); //converting states to 0 or 1 prediction
        bool debug;
        
    public:
        BHT(unsigned char, bool); //short is history length, char is nbit
        bool predictBranch(unsigned short, unsigned short,bool);
        unsigned long numEntries();
};

#endif 
