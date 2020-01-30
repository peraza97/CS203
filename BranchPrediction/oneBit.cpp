#include "oneBit.h"

OneBit::OneBit(){
    this->prediction = 0;
}

void OneBit::makePrediction(string addr, bool actualValue){
    if(this->prediction == actualValue){
        this->correct += 1;
    }
    else{
        this->prediction = actualValue;
    }
    this->total += 1;
}