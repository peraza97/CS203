#include "app.h"

Application::Application(string fileName){
    this->fileName = fileName;
    this->count = 0;
}

void Application::InitApplication(){
    this->inputStream.open(this->fileName.c_str());
    if(!this->inputStream.is_open()){
        cout << "error opening file: " << this->fileName << endl;
        exit(1);
    }   
    string input1, input2;
    while(this->inputStream >> input1 >> input2){
        this->addresses.push_back(input1);
        if(input2 == "T"){
            this->results.push_back(1);
        }
        else if(input2 == "N"){
            this->results.push_back(0);
        }
        else{
            printf("ERROR unexpected value: %s\n",input2.c_str());
            exit(1);
        }
    }
    this->inputStream.close();

}

void Application::getBranch(string &addr, bool& result){
    addr = this->addresses.at(this->count);
    result = this->results.at(this->count);
    this->count += 1;
}

unsigned long Application::getNumUniqueInstructions(){
    set<string> unique(this->addresses.begin(),this->addresses.end());
    return unique.size();
}