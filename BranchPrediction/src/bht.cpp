#include "bht.h"

BHT::BHT(unsigned char historyLength, unsigned char nbit, bool debug){
    this->historyBits = historyLength;
    this->history = 0;
    this->debug = debug;
    if(nbit == 1){
        this->NBitFunction = &oneBitSM;
        this->prediction = &oneBitPrediction;
        this->strConversion = &oneBitStr;
    }
    else if(nbit == 2){
        this->NBitFunction = &twoBitSM;
        this->prediction = &twoBitPrediction;
        this->strConversion = &twoBitStr;
    }
    printf("-----------------------------\n");
    printf("BHT Information\n");
    printf("Bits used for history: %u\n", this->historyBits);
    printf("History starts at: %u\n", this->history);
    printf("N-bit predictor: %u\n", nbit);
    printf("debug mode: %u\n", this->debug);
    printf("------------------------------\n");
}

void BHT::updateHistory(bool expected){
    history = history << 1;
    history = history | expected;
    history = history << (16 - this->historyBits);
    history = history >> (16 - this->historyBits);
}

bool BHT::predictBranch(unsigned short address, bool expected){
    unsigned short oldHistory = this->history;
    unsigned char predicted = this->globalTables[this->history][address];
    unsigned char newPredicted = this->NBitFunction(predicted,expected);
    this->globalTables[this->history][address] = newPredicted;
    updateHistory(expected);
    if(this->debug){       
        printf("history: %u\n", oldHistory);
        printf("globaltables[%u][%u] = %s\n", oldHistory, address, strConversion(predicted).c_str());
        printf("prediction: %u\n", prediction(predicted));    
        printf("updated:: globaltables[%u][%u] = %s\n", oldHistory, address, strConversion(newPredicted).c_str());       
        printf("updated:: history: %u\n", this->history);
    }

    return prediction(predicted) == expected;
}
