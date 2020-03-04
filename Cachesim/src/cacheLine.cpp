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

int CacheLine::getCapacity(){
    return this->maxSize;
}

int CacheLine::access(uint32_t key){
    int hit;
    if(tagMap.find(key) == tagMap.end()){ //not in, need to insert
        if(line.size() == maxSize){ //full, remove last element
            tagMap.erase(*(--line.end()));
            line.pop_back();
        }
        hit = 0; 
    }
    else{ //in the map, remove the iterator
        tagIter tag = tagMap[key];
        tagMap.erase(key);
        line.erase(tag);
        hit = 1;
    }
    line.push_front(key); //update list
    tagMap[key] = line.begin();
    return hit;
}

string CacheLine::str(){
    ostringstream os;
    for(tagIter it = line.begin(); it != line.end(); ++it){
        os << *it << " ";
    }
    return os.str();
}