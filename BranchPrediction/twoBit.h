#ifndef __TWOBIT_H_
#define __TWOBIT_H_

#include <vector>
#include <iostream>
#include "predictor.h"
enum States { NT_00, NT_01, T_11, T_10};
class TwoBit : public Predictor{
    private:
        States state;
        bool prediction;

    public:
        TwoBit();
        void makePrediction(string, bool);
        void SM(bool);
};

#endif