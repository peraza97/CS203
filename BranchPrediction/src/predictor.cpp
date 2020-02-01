#include "predictor.h"
#include <sstream>
#include <iomanip>

Predictor::Predictor(unsigned char m, unsigned char n, unsigned char addrLength, bool debug): branchHistoryTable(m,n,debug){
    this->addrBits = addrLength;
    this->correct = 0;
    this->total = 0;
    this->debug = debug;
    printf("Predictor Information\n");
    printf("Bits used for address: %u\n", this->addrBits);
    printf("Predictor debug mode: %u\n", this->debug);
    printf("------------------------------\n");
};

void Predictor::printRates(){
    printf("------------------------------------------\n");  
    printf("correct: %d\n", this->correct);
    printf("total: %d\n",this->total);
    if(total == 0){
        printf("Error, total = 0\n");
    }
    else{
        printf("Misclassification rate: %.3f%%\n", 100.00 * (1 - (double)(this->correct)/this->total));
    }
}

unsigned short Predictor::convertAddress(string input){
    istringstream converter(input);
    unsigned int conversion;
    unsigned short address, leftShift, result;
    converter >> std::hex >> conversion; //address is 24 bits, so storing into int
    address = (unsigned short)(conversion); //truncate to 16 bits
    leftShift = address << (16 - this->addrBits); //left shift to clear top bits
    result = leftShift >> (16 - this->addrBits); //right shift to place back

    if(this->debug){
        printf("%s => %u\n", input.c_str(), address);
        printf("%u truncated to 16 bits: %s\n", address, getBinary(address,this->addrBits,0).c_str());
        printf("left shifted: %s\n", getBinary(leftShift ,16,0).c_str());  
        printf("right shifted: %s\n", getBinary(result,this->addrBits,1).c_str()); 
        printf("using %u bits, index is %u\n", this->addrBits, result);             
    }
    return result;
}

void Predictor::makePrediction(string input, bool expected){
    if(this->debug){
        printf("------------------------------------------\n");  
        printf("Address: 0x%s,  expected: %d\n", input.c_str(), expected);
    }

    unsigned short address = convertAddress(input); //convert address
    bool match = this->branchHistoryTable.predictBranch(address, expected); //pass it into BHT, return if prediction is correct
    if(match){
        this->correct++;
    }
    this->total++;
}