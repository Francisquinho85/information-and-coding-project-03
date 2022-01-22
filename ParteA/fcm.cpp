#include <iostream>
#include <fstream>
#include "fcm.hpp"
#include <map>
#include <set>
#include <vector>
#include <algorithm>

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
        char c;
        ifs.get(c);

        if(!alphabet.count(c)){
            alphabet.insert(c);
            updateMapAlphabet(c);
        }

        kDone++;
        if(this->k < kDone){
            for(int i = 0; i < k; i++) {
                context += this->ctx.at(i);
            }
            
            if(mapOfMaps.find(context) != mapOfMaps.end()) {
                map<char,int> tmp1 = mapOfMaps[context];
                int charElem = tmp1[c];
                tmp1[c] = charElem + 1;
                mapOfMaps[context] = tmp1;
            } else {

                map<char,int> tmp;

                for(set<char>::iterator setIt = alphabet.begin(); setIt != alphabet.end(); setIt++) {
                    tmp.insert(pair<char,int>(*setIt,0));
                }

                tmp[c] = 1;
                mapOfMaps.insert(pair<string,map<char,int>>(context,tmp));
            }

            //Next context
            this->ctx.erase(this->ctx.cbegin());
            this->ctx.push_back(c);

        } else {
            this->ctx.push_back(c);
        }
    }
}

void fcm::printMap() {
    map<string,map<char,int>>::iterator it;

    for (it = mapOfMaps.begin(); it != mapOfMaps.end(); it++) {
        cout << it->first << "\t";
        map<char,int> internalMap = it->second;
        map<char,int>::iterator it2;
        for(it2 = internalMap.begin(); it2 != internalMap.end(); it2++){
            cout << it2->first << "->" << it2->second << "\t";
        }
        cout << endl;
    }
}

void fcm::updateMapAlphabet(char c) {
    map<string,map<char,int>>::iterator it;

    for (it = mapOfMaps.begin(); it != mapOfMaps.end(); it++) {

        map<char,int> internalMap = it->second;
        map<char,int>::iterator it2;
        for(it2 = internalMap.begin(); it2 != internalMap.end(); it2++){
            internalMap.insert(pair<char,int>(c,0));
            mapOfMaps[it->first] = internalMap;
        }
    }
}
