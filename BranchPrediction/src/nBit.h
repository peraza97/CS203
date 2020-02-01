#ifndef __NBIT_H__
#define __NBIT_H__

#include <iostream>
#include <map>
using namespace std;

typedef map<unsigned short, unsigned char> branchHistoryTable;
typedef map<unsigned short, branchHistoryTable> GlobalBranchHistoryTables;

enum singleBit: unsigned char {NT_0, T_1};
enum twoBit: unsigned char{NT_00,NT_01, T_11, T_10};

unsigned char oneBitSM(unsigned char state, bool input);
unsigned char twoBitSM(unsigned char state, bool input);

unsigned char oneBitPrediction(unsigned char input);
unsigned char twoBitPrediction(unsigned char input);

string oneBitStr(unsigned char input);
string twoBitStr(unsigned char input);

#endif