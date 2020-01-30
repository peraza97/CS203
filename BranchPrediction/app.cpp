#include "app.h"

Application::Application(string fileName){
    this->fileName = fileName;
    this->count = 0;
}

void Application::InitApplication(){
    cout << "Opening file: " << this->fileName << endl;
    this->inputStream.open(this->fileName.c_str());
    if(!this->inputStream.is_open()){
        cout << "error opening file: " << this->fileName << endl;
        exit(1);
    }   
    string input1, input2;
    while(this->inputStream >> input1 >> input2){
        this->addresses.push_back(input1);
        this->results.push_back((input2 == "T" ? 1 : 0));
    }
    this->inputStream.close();

}

void Application::getBranch(string &addr, bool& result){
    addr = this->addresses.at(this->count);
    result = this->results.at(this->count);
    this->count += 1;
}