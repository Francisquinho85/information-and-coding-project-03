#include <iostream>
#include <fstream>
#include "fcm.hpp"
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <cstring>
#include <math.h>

using namespace std;

fcm::fcm(int k, int a){
    this->k = k;
    this->a = a;
}

void fcm::readFile(char * readFile) {

    ifstream ifs(readFile);
    int kDone = 0;
    char c;

    while(ifs.get(c)) {
        string context = "";

        if(c == '\n' || c == '\t' || c == '\r'){
            continue;
        }

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
    ifs.close();
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

void fcm::writeMapToFile(char * fileName){
    
    map<string,map<char,int>>::iterator it;
    ofstream ofs;
    ofs.open(fileName, std::ofstream::out | std::ofstream::trunc);

    for(it = mapOfMaps.begin(); it != mapOfMaps.end(); it++) {
        ofs << it->first << "\t";
        map<char,int> internalMap = it->second;
        map<char,int>::iterator it2;

        for(it2 = internalMap.begin(); it2 != internalMap.end(); it2++){
            ofs << it2->first << "->" << it2->second << "\t";
        }
        ofs << endl;
    }

    ofs.close();
}

void fcm::readMapFromFile(char * fileName) {

    ifstream ifs(fileName);
    string line;
    string delimiter = "\t";

    while(getline(ifs,line)){
        size_t pos = line.find(delimiter);
        string firstToken = line.substr(0, pos);
        line.erase(0, pos + delimiter.length());
        map<char,int> tmp;

        while ((pos = line.find(delimiter)) != std::string::npos) {
            string token = line.substr(0, pos);
            string c = token.substr(0,token.find("->"));
            string numberOfHitsStr = token.substr(token.find(">"));
            numberOfHitsStr.erase(0,1);
            line.erase(0, pos + delimiter.length());

            int n = c.length();
            char char_array[n + 1];
            strcpy(char_array, c.c_str());
            int numberOfHits = stoi(numberOfHitsStr);

            tmp.insert(pair<char,int>(char_array[0],numberOfHits));
        }
        mapOfMaps.insert(pair<string,map<char,int>>(firstToken,tmp));
    }
}

int fcm::get_total_context(string s){
    int counter = 0;
    
    if(mapOfMaps.find(s)!=mapOfMaps.end()){
        map<char,int> tmp;
        tmp = mapOfMaps[s];
        map<char,int>::iterator it2;
        for(it2 = tmp.begin(); it2 != tmp.end(); it2++){
            counter += it2->second;
        }

    }
    return counter;    
}
double fcm::get_entropy_context(string s){
    double entropy;
    double prob;
    if(mapOfMaps.find(s)!=mapOfMaps.end()){
        map<char,int> tmp;
        tmp = mapOfMaps[s];
        map<char,int>::iterator it2;
        for(it2 = tmp.begin(); it2 != tmp.end(); it2++){
            prob = (it2->second+(double)this->a) / (get_total_context(s)+((double)this->a*3));
            entropy += prob * log(prob);
        }
    } 
    return -entropy;
}

int fcm::get_total_map(){
    int counter = 0;
    
    map<string,map<char,int>>::iterator it;

    for(it = mapOfMaps.begin(); it != mapOfMaps.end(); it++) {
        map<char,int> internalMap = it->second;
        map<char,int>::iterator it2;

        for(it2 = internalMap.begin(); it2 != internalMap.end(); it2++){
            counter += it2->first;
        }
    }
    return counter;    
}

double fcm::get_entropy_map(){
    double total_entropy;
    map<string,map<char,int>>::iterator it;

    for(it = mapOfMaps.begin(); it != mapOfMaps.end(); it++) {
        string s = it->first;
        total_entropy += get_entropy_context(s) * get_total_context(s);
    } 
    return total_entropy/get_total_map();
}


        
    



