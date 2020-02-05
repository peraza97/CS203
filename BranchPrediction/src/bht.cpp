#include "bht.h"

BHT::BHT(unsigned char nbit, bool debug){
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
    printf("BHT: %u-bit\n", nbit);
}

bool BHT::predictBranch(unsigned short history, unsigned short address, bool expected){
    unsigned char prevState = this->globalTables[history][address]; //get the last state
    unsigned char predictedValue = prediction(prevState); //convert this into a prediction
    unsigned char newState = this->NBitFunction(prevState,expected); //assign a new state, based on expected and old state
    this->globalTables[history][address] = newState; //update with state

    if(this->debug){   
        printf("globaltables[%u][%u] = %s\n", history, address, strConversion(prevState).c_str());
        printf("%s prediction: %u => %s\n", strConversion(prevState).c_str(), predictedValue,(predictedValue == expected ? "Correct": "Wrong") );    
        printf("updated globaltables[%u][%u] = %s\n", history, address, strConversion(newState).c_str());       
    }

    return predictedValue == expected;
}

unsigned long BHT::numEntries(){
    unsigned long count = 0;
    for (GlobalBranchHistoryTables::iterator it = this->globalTables.begin(); it != this->globalTables.end(); it++ ){
        count += it->second.size();
    }
    return count;
}
