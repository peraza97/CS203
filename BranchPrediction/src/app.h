#ifndef __APP_H_
#define __APP_H_

#include <iostream>
#include <fstream>
#include <vector>

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
        bool done(){return this->count >= this->addresses.size();};

};

#endif