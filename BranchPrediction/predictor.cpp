#include "predictor.h"

Predictor::Predictor(){
    this->m = 0;
    this->n = 0;
    this->addrLength = 0;
    this->correct = 0;
    this->total = 0;
};

Predictor::Predictor(int m, int n, int addrLength){
    this->m = m;
    this->n = n;
    this->addrLength = addrLength;
    this->correct = 0;
    this->total = 0;
};

void Predictor::printRates(){
    cout << "correct: " << this->correct << endl;
    cout << "total: " << this->total << endl;
    if(total == 0){
        cout << "Error, total = 0" << endl;
    }
    else{
        cout << "Misclassification rate: " << 1 - (double)(this->correct)/this->total << endl;
    }
}