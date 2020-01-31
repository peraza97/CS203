#ifndef __BHT_H_
#define __BHT_H_

#include <iostream>
#include <map>
using namespace std;

typedef map<unsigned short, unsigned char> table;
typedef map<unsigned short, table> branchHistoryTable;

class BHT{
    private:
        branchHistoryTable globalTables;
        unsigned short history;
        unsigned char nbit;

    public:
        BHT();
        BHT(unsigned short, unsigned char); //short is history, char is nbit


};

#endif 

/*void TwoBit::SM(bool input){
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
*/