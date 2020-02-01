#include "predictor.h"
#include <sstream>
#include <iomanip>

Predictor::Predictor(unsigned char m, unsigned char n, unsigned char addrLength, bool debug): branchHistoryTable(m,n,debug){
    this->addrLength = addrLength;
    this->correct = 0;
    this->total = 0;
    this->debug = debug;
    printf("-----------------------------\n");
    printf("Predictor Information\n");
    printf("Bits used for address: %u\n", this->addrLength);
    printf("debug mode: %u\n", this->debug);
    printf("------------------------------\n");
};

unsigned short Predictor::convertAddress(string input){
    istringstream converter(input);
    unsigned int conversion;
    converter >> std::hex >> conversion; //address is 24 bits, so storing into int
    unsigned short address = (unsigned short)(conversion);
    address <<= (16 - this->addrLength); //left shift to clear top bits
    address >>= (16 - this->addrLength); //right shift to place back
    return address;
}

void Predictor::makePrediction(string input, bool expected){
    unsigned short address = convertAddress(input);
    if(this->debug){
        printf("------------------------------------------\n");  
        printf("address: %s, expected: %u\n", input.c_str(), expected);        
        printf("%s => %u\n", input.c_str(), address);
    }

    bool match = this->branchHistoryTable.predictBranch(address, expected);
    if(match){
        this->correct++;
    }
    this->total++;
}

void Predictor::printRates(){
    printf("--------------------------------\n");
    printf("correct: %d\n", this->correct);
    printf("total: %d\n",this->total);
    if(total == 0){
        printf("Error, total = 0\n");
    }
    else{
        printf("Misclassification rate: %.3f\n", 1 - (double)(this->correct)/this->total);
    }
}