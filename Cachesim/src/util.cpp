#include "util.h"

string getBinary(uint32_t value){
    string bin(ADDRESS_LENGTH,'*');
    uint32_t temp = value;
    int i;
    for(i = ADDRESS_LENGTH - 1; i >= 0; --i){
        bin[i] = temp & 0x01 ? '1' : '0';
        temp >>= 1;
    }
    return bin;
}