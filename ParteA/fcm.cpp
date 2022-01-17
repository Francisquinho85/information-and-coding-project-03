#include <iostream>
#include <fstream>
#include "fcm.hpp"
#include <map>
#include <set>
#include <vector>

using namespace std;

fcm::fcm(int k, int a){
    this->k = k;
    this->a = a;
}

void fcm::readFile(char * readFile) {

    ifstream ifs(readFile);
    int kDone = 0;
    
    while(ifs.good()) {
        string context = "";
        ifs.get(c);
        char c;
        alphabet.insert(c);
        kDone++;
        if(this->k < kDone){
            for(int i = 0; i < k; i++) {
                context += this->ctx.at(i);
            }
            
            if(find(this->mapOfMaps.begin(), mapOfMaps.end(), context) != mapOfMaps.end()) {
                
            } else {

            }

            //Next context
            this->ctx.erase(this->ctx.cbegin());
            this->ctx.push_back(c);

        } else {
            this->ctx.push_back(c);
        }
    }
}