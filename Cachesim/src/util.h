#ifndef __UTIL_H__
#define __UTIL_H__

#include <iostream>
#include <stdio.h>
using namespace std;


#define ADDRESS_LENGTH 32

string getBinary(uint32_t);
string formatAddress(uint32_t,int,int,int);
#endif