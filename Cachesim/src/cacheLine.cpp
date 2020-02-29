#include "cacheLine.h"
CacheLine::CacheLine(){
    this->maxSize = 0;
}
CacheLine::CacheLine(int capacity){
    this->maxSize = capacity;
}

void CacheLine::setCapacity(int capacity){
    this->maxSize = capacity;  
}

int CacheLine::getSize(){
    return this->maxSize;
}

int CacheLine::get(uint32_t key) {
    if(hash.find(key) == hash.end()) {
        return -1;
    }
    tagIter tag = hash[key];
    line.erase(tag);
    hash.erase(key);
    line.push_front(key);
    hash[key] = line.begin();
    return 1;
}

void CacheLine::put(uint32_t key){
    if(hash.find(key) == hash.end()) {
        if(line.size() < maxSize){ //remove end and add to front
            line.push_front(key);
            hash[key] = line.begin();
        }
        else{
            tagIter tag = line.end();
            tag--;
            hash.erase(*tag);
            line.pop_back();
            line.push_front(key);
            hash[key] = line.begin();
        }
    }
    else{
        tagIter tag = hash[key];
        line.erase(tag);
        hash.erase(key);
        line.push_front(key);
        hash[key] = line.begin();  
    }
}

string CacheLine::str(){
    ostringstream os;
    for(tagIter it = line.begin(); it != line.end(); ++it){
        os << *it << " ";
    }
    return os.str();
}