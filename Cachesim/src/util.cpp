#include "util.h"

uint32_t convertSizeInput(string input){
    uint32_t result = 0;
    int position = 0;
    for(position = 0; position < input.size(); ++position){
        if(!isdigit(input.at(position))){
            break;
        }
    }
    result = atoi(input.substr(0,position).c_str());
    if(ceil(log2(result)) != floor(log2(result))){
        return 0;
    }
    int bits = log2(result);
    string suffix = input.substr(position);
    if(suffix == "" || suffix == "B"){
        bits += 0;
    }
    else if(suffix == "KB"){
        bits += 10;
    }
    else if(suffix == "MB"){
        bits += 20;
    }
    else{
        return 0;
    }
    return pow(2, bits);
}

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

string formatAddress(uint32_t value, int tag, int index, int offset){
    string bin(ADDRESS_LENGTH,'*');
    uint32_t temp = value;
    int i;
    for(i = ADDRESS_LENGTH - 1; i >= 0; --i){
        bin[i] = temp & 0x01 ? '1' : '0';
        temp >>= 1;
    }
    int pos = ADDRESS_LENGTH - offset;
    bin.insert(pos, 1, '|');
    pos -= index;
    bin.insert(pos, 1, '|');
    pos -= tag;
    bin.insert(pos, 1, '|');  
 
    return bin;
}