#ifndef __APP_H_
#define __APP_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
using namespace std;

class Application{
    private:
        string fileName;
        ifstream inputStream;

    public:
        Application(string fileName);
        void InitApplication();
        bool getBranch(string &, bool &);
};

#endif