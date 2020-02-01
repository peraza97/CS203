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
    printf("BHT Information\n");
    printf("Bits used for history: %u\n", this->historyBits);
    printf("History starts at: %u\n", this->history);
    printf("N-bit predictor: %u\n", nbit);
    printf("BHT debug mode: %u\n\n", this->debug);
}

void BHT::updateHistory(bool expected){
    history = history << 1;
    history = history | expected;
    history = history << (16 - this->historyBits);
    history = history >> (16 - this->historyBits);
}

bool BHT::predictBranch(unsigned short address, bool expected){
    unsigned short oldHistory = this->history; //keep record of history for debugging
    unsigned char prevState = this->globalTables[this->history][address]; //get the last state
    unsigned char predictedValue = prediction(prevState); //convert this into a prediction
    unsigned char newState = this->NBitFunction(prevState,expected); //assign a new state, based on expected and old state
    this->globalTables[this->history][address] = newState; //update with state
    updateHistory(expected);

    if(this->debug){       
        printf("history: %s\n", getBinary(oldHistory,this->historyBits,1).c_str());
        printf("globaltables[%u][%u] = %s\n", oldHistory, address, strConversion(prevState).c_str());
        printf("%s prediction: %u\n", strConversion(prevState).c_str(), predictedValue);    
        printf("updated globaltables[%u][%u]:: %s\n", oldHistory, address, strConversion(newState).c_str());       
        printf("updated history:: %s\n", getBinary(this->history, this->historyBits,1).c_str());
    }

    return predictedValue == expected;
}
