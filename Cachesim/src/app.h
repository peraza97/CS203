#ifndef __APP_H_
#define __APP_H_

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

enum MEM_TYPE: unsigned char {LOAD, STORE};

class Application{
    private:
        string fileName;
        ifstream inputStream;

    public:
        Application(string fileName);
        void InitApplication();
        bool getMemoryAccess(unsigned char &, int &, string &);
};

#endif