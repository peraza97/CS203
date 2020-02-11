#include "predictor.h"
#include <sstream>
#include <iomanip>

Predictor::Predictor(unsigned char m, unsigned char n, unsigned char addrLength, bool debug): branchHistoryTable(n,debug){
    this->historyBits = m;
    this->history = 0;
    this->addrBits = addrLength > 16 ? 16 : addrLength;
    this->debug = debug;
    this->correct = 0;
    this->total = 0;
    printf("Address length: %u\n", this->addrBits);
    printf("History length: %u\n", this->historyBits);
    printf("Debug mode: %u\n", this->debug);
};

void Predictor::printRates(){ 
    printf("------------------------------------------\n"); 
    if(total == 0){
        printf("Error, Cannot get rate \n");
    }
    else{
        printf("Misclassification rate: %.2f%%\n", 100.00 * (1 - (double)(this->correct)/this->total));
    } 
    if(this->debug){
    printf("correct: %d\n", this->correct);
    printf("total: %d\n",this->total);
    }
    printf("BHT used %lu entries\n",this->branchHistoryTable.numEntries());  
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
        /*
        printf("%s => %u\n", input.c_str(), address);
        printf("%u truncated to 16 bits: %s\n", address, getBinary(address,this->addrBits,0).c_str());
        printf("left shifted: %s\n", getBinary(leftShift ,16,0).c_str());  
        printf("right shifted: %s\n", getBinary(result,this->addrBits,1).c_str()); 
        */
        printf("using %u bits of address, index is %u\n", this->addrBits, result);             
    }
    return result;
}

void Predictor::updateHistory(bool expected){
    history = history << 1;
    history = history | expected;
    history = history << (16 - this->historyBits);
    history = history >> (16 - this->historyBits);
}

void Predictor::makePrediction(string input, bool expected){
    if(this->debug){
        printf("------------------------------------------\n");  
        printf("Address: 0x%s,  expected: %d\n", input.c_str(), expected);
    }
    unsigned short prevHistory = this->history;
    unsigned short address = convertAddress(input); //convert address
    bool match = this->branchHistoryTable.predictBranch(prevHistory, address, expected); //pass it into BHT, return if prediction is correct
    updateHistory(expected);

    if(match){
        this->correct++;
    }
    this->total++;

    if(this->debug){ 
        printf("Previous History: %s\n", getBinary(prevHistory,this->historyBits,1).c_str());
        printf("New History     : %s\n", getBinary(this->history, this->historyBits,1).c_str());
    }
}