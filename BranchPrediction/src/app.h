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
        vector<string> addresses;
        vector<bool> results;
        int count;

    public:
        Application(string fileName);
        void InitApplication();
        void getBranch(string &, bool &);
        unsigned long getNumUniqueInstructions();
        bool done(){return this->count >= this->addresses.size();};
};

#endif