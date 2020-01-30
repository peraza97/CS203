#include "twoBit.h"

vector<string> myNames = {"00", "01", "11", "10"};

TwoBit::TwoBit(){
    this->prediction = 0;
    this->state = NT_00;
}

void TwoBit::SM(bool input){
    //transistions
    switch(this->state){
        case NT_00:
            if(input){
                this->state = NT_01;
            }
            break;
        case NT_01:
            if(input){
                this->state = T_11;
            }
            else{
                this->state = NT_00;
            }
            break;
        case T_11:
            if(!input){
                this->state = T_10;
            }
            break;
        case T_10:
            if(input){
                this->state = T_11;
            }
            else{
                this->state = NT_00;
            }
            break;
        default:
            break;
    }
    //actions
    switch(this->state){
        case NT_00:
        case NT_01:
            this->prediction = 0;
            break;
        case T_10:
        case T_11:
            this->prediction = 1;
            break;
        default:
            break;
    }
}

void TwoBit::makePrediction(string addr, bool actualValue){
    if(this->prediction == actualValue){
        this->correct += 1;
    }
    this->total += 1;
}