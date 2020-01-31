#ifndef __BRANCH_H_
#define __BRANCH_H_

#include <iostream>
using namespace std;

class Predictor{
    private:
        int m; //m bits of history
        int n; //1 bit or 2 bit branch predictor
        int addrLength; //number of bits of address used to index

        int correct;
        int total;


    public:
        Predictor();
        Predictor(int, int, int = 8);
        void printRates();
};

#endif