#include "bht.h"

unsigned char oneBitSM(unsigned char state, bool input){
    switch (state)
    {
    case NT_0:
        if(input){
            state = T_1;
        }
        break;
    case T_1:
        if(!input){
            state = NT_0;
        }
        break;
    default:
        break;
    }
    return state;
}

unsigned char twoBitSM(unsigned char state, bool input){
    //transistions
    switch(state){
        case NT_00:
            if(input){
                state = NT_01;
            }
            break;
        case NT_01:
            if(input){
                state = T_11;
            }
            else{
                state = NT_00;
            }
            break;
        case T_11:
            if(!input){
                state = T_10;
            }
            break;
        case T_10:
            if(input){
                state = T_11;
            }
            else{
                state = NT_00;
            }
            break;
        default:
            break;
    }
    return state;
}

unsigned char oneBitPrediction(unsigned char input){
    switch(input){
        case NT_0:
            return 0;
        case T_1:
            return 1;
    }
    return -1;
}

unsigned char twoBitPrediction(unsigned char input){
    switch(input){
        case NT_00:
        case NT_01:
            return 0;
        case T_10:
        case T_11:
            return 1;
    }
    return -1;
}

string oneBitStr(unsigned char input){
    switch(input){
        case NT_0:
            return "NT_0";
        case T_1:
            return "T_1";
    }
    return "ERROR";   
}
string twoBitStr(unsigned char input){
    switch(input){
        case NT_00:
            return "NT_00";
        case NT_01:
            return "NT_01";
        case T_10:
            return "T_10";
        case T_11:
            return "T_11";
    }
    return "ERROR";
}

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
