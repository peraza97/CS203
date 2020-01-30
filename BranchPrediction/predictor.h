#ifndef __BRANCH_H_
#define __BRANCH_H_

#include <iostream>
using namespace std;

class Predictor{
    protected:
        int correct;
        int total;

    public:
        Predictor(){
            correct = 0;
            total = 0;
        };
        void printStats(){
            cout <<  "Correct: " << this->correct << endl;
            cout << "Total: " << this->total << endl;
            cout << "Accuracy: " << (total ? (double)(correct)/total : -1) << endl;

        }
        virtual void makePrediction(string, bool) = 0;
};

#endif