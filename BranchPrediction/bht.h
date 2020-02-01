#ifndef __BHT_H_
#define __BHT_H_

#include <stdio.h>
#include <iostream>
#include <map>
using namespace std;

typedef map<unsigned short, unsigned char> branchHistoryTable;
typedef map<unsigned short, branchHistoryTable> GlobalBranchHistoryTables;

enum singleBit: unsigned char {NT_0, T_1};
enum twoBit: unsigned char{NT_00,NT_01, T_11, T_10};

class BHT{
    private:
        GlobalBranchHistoryTables globalTables;
        unsigned char historyBits;
        unsigned char (*NBitFunction)(unsigned char,bool); //n-bit predictor function updates state with bool
        unsigned char (*prediction)(unsigned char); //converting states to 0 or 1 prediction
        string (*strConversion)(unsigned char); //converting states to 0 or 1 prediction
        
        unsigned short history;
        bool debug;
        void updateHistory(bool); //updat the history

    public:
        BHT(unsigned char, unsigned char, bool); //short is history length, char is nbit
        bool predictBranch(unsigned short,bool);
};

#endif 
