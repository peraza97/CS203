#ifndef __ONEBIT_H_
#define __ONEBIT_H_

#include "predictor.h"

class OneBit : public Predictor{
    private:
        bool prediction;

    public:
        OneBit();
        void makePrediction(string, bool);
};

#endif