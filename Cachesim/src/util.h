#ifndef __UTIL_H__
#define __UTIL_H__

#include <iostream>
#include <stdio.h>
#include <cmath>

using namespace std;

#define ADDRESS_LENGTH 32

uint32_t convertSizeInput(string);
string formatAddress(uint32_t,int,int,int);
#endif