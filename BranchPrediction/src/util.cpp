#include "util.h"

unsigned char oneBitSM(unsigned char state, bool input){
    switch (state)
    {
    case NT_0:
        if(input){
            state = T_1;
        }
        break;
    case T_1:
        if(!input){
            state = NT_0;
        }
        break;
    default:
        break;
    }
    return state;
}

unsigned char twoBitSM(unsigned char state, bool input){
    //transistions
    switch(state){
        case NT_00:
            if(input){
                state = NT_01;
            }
            break;
        case NT_01:
            if(input){
                state = T_11;
            }
            else{
                state = NT_00;
            }
            break;
        case T_11:
            if(!input){
                state = T_10;
            }
            break;
        case T_10:
            if(input){
                state = T_11;
            }
            else{
                state = NT_00;
            }
            break;
        default:
            break;
    }
    return state;
}

unsigned char oneBitPrediction(unsigned char input){
    switch(input){
        case NT_0:
            return 0;
        case T_1:
            return 1;
    }
    return -1;
}

unsigned char twoBitPrediction(unsigned char input){
    switch(input){
        case NT_00:
        case NT_01:
            return 0;
        case T_10:
        case T_11:
            return 1;
    }
    return -1;
}

string oneBitStr(unsigned char input){
    switch(input){
        case NT_0:
            return "NT_0";
        case T_1:
            return "T_1";
    }
    return "ERROR";   
}
string twoBitStr(unsigned char input){
    switch(input){
        case NT_00:
            return "NT_00";
        case NT_01:
            return "NT_01";
        case T_10:
            return "T_10";
        case T_11:
            return "T_11";
    }
    return "ERROR";
}

/*
value: value to be converted
maxBits: puts a place marker after k LSB
start: puts '*' on bits we do not care about
*/
string getBinary(unsigned short value, unsigned char maxBits, unsigned char stars){
    string bin(16,'*');
    unsigned short temp = value;
    int i;
    for(i = 15; i >= 0; --i){
        bin[i] = temp & 0x01 ? '1' : '0';
        temp >>= 1;
    }
    bin.insert((16 - maxBits),1,'|');    
    
    if(stars){
        for(i = 0; bin.at(i)!='|'; ++i){
            bin.at(i) = '*';
        }
    }
    
    return bin;
}