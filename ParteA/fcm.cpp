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
    this->a = (double)a/100;
}

void fcm::readFile(char * readFile) {

    ifstream ifs(readFile);
    int kDone = 0;
    char c;
    string s;
    while(ifs.get(c) && kDone < 1000000) {
        string context = "";
        if(c<0 || c >127){
            s = "";
            s += c;
            ifs.get(c);
            s += c;
        }
        else{
            s = c;
        }
        if(c == '\n' || c == '\t' || c == '\r'){
            continue;
        }
            
        alphabet.insert(s);
        kDone++;
        if(this->k < kDone){
            for(int i = 0; i < k; i++) {
                context += this->ctx.at(i);
            }
            
            if(mapOfMaps.find(context) != mapOfMaps.end()) {
                map<string,int> tmp1 = mapOfMaps[context];
                int charElem = tmp1[s];
                tmp1[s] = charElem + 1;
                mapOfMaps[context] = tmp1;
            } else {

                map<string,int> tmp;
                tmp.insert(pair<string,int>(s,1));
                mapOfMaps.insert(pair<string,map<string,int>>(context,tmp));
            }

            //Next context
            this->ctx.erase(this->ctx.cbegin());
            this->ctx.push_back(s);

        } else {
            this->ctx.push_back(s);
        }
    }
    ifs.close();
}

void fcm::printMap() {
    map<string,map<string,int>>::iterator it;

    for (it = mapOfMaps.begin(); it != mapOfMaps.end(); it++) {
        cout << it->first << "\t";
        map<string,int> internalMap = it->second;
        map<string,int>::iterator it2;
        for(it2 = internalMap.begin(); it2 != internalMap.end(); it2++){
            cout << it2->first << "->" << it2->second << "\t";
        }
        cout << endl;
    }
}

// void fcm::updateMapAlphabet(char c) {
//     map<string,map<char,int>>::iterator it;

//     for (it = mapOfMaps.begin(); it != mapOfMaps.end(); it++) {

//         map<char,int> internalMap = it->second;
//         map<char,int>::iterator it2;
//         for(it2 = internalMap.begin(); it2 != internalMap.end(); it2++){
//             internalMap.insert(pair<char,int>(c,0));
//             mapOfMaps[it->first] = internalMap;
//         }
//     }
// }

void fcm::writeMapToFile(char * fileName){
    
    map<string,map<string,int>>::iterator it;
    ofstream ofs;
    ofs.open(fileName, std::ofstream::out | std::ofstream::trunc);

    for(it = mapOfMaps.begin(); it != mapOfMaps.end(); it++) {
        ofs << it->first << "\t";
        map<string,int> internalMap = it->second;
        map<string,int>::iterator it2;

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

        int n = firstToken.length();
        char char_array[n + 1];
        strcpy(char_array, firstToken.c_str());
        string b = ""; 
        for(int i=0;i<n;i++){
            if(char_array[i]<0 || char_array[i] >127){
                b = "";
                b += char_array[i];
                i++;
                b += char_array[i];
            }
            else{
                b = char_array[i];
            }
            alphabet.insert(b);
        }

        line.erase(0, pos + delimiter.length());
        map<string,int> tmp;

        while ((pos = line.find(delimiter)) != std::string::npos) {
            string token = line.substr(0, pos);
            //cout << token << endl;
            string c = token.substr(0,token.find("->"));
            string numberOfHitsStr = token.substr(token.find("->"));
            
            numberOfHitsStr.erase(0,2);
            line.erase(0, pos + delimiter.length());
            // int n = c.length();
            // string char_array[n + 1];
            // strcpy(char_array, c.c_str());
            int numberOfHits = stoi(numberOfHitsStr);

            tmp.insert(pair<string,int>(c,numberOfHits));
            alphabet.insert(c);
        }
        mapOfMaps.insert(pair<string,map<string,int>>(firstToken,tmp));
    }
}

int fcm::get_total_context(string s){
    int counter = 0;
    
    if(mapOfMaps.find(s)!=mapOfMaps.end()){
        map<string,int> tmp;
        tmp = mapOfMaps[s];
        map<string,int>::iterator it2;
        for(it2 = tmp.begin(); it2 != tmp.end(); it2++){
            counter += it2->second;
        }
    }
    return counter;    
}
double fcm::get_entropy_context(string s){
    double entropy = 0;
    double prob = 0;
    if(mapOfMaps.find(s)!=mapOfMaps.end()){
        map<string,int> tmp;
        tmp = mapOfMaps[s];
        map<string,int>::iterator it2;
        for(it2 = tmp.begin(); it2 != tmp.end(); it2++){
            prob = (double)(it2->second) / (double)(get_total_context(s));
            entropy += prob * log(prob);
        }
        entropy = -entropy;
    } 
    return entropy;
}

int fcm::get_total_map(){
    int counter = 0;
    
    map<string,map<string,int>>::iterator it;

    for(it = mapOfMaps.begin(); it != mapOfMaps.end(); it++) {
        map<string,int> internalMap = it->second;
        map<string,int>::iterator it2;

        for(it2 = internalMap.begin(); it2 != internalMap.end(); it2++){
            counter += it2->second;
        }
    }
    return counter;    
}

double fcm::get_entropy_map(){
    double total_entropy;
    map<string,map<string,int>>::iterator it;

    for(it = mapOfMaps.begin(); it != mapOfMaps.end(); it++) {
        string s = it->first;
        total_entropy += get_entropy_context(s) * get_total_context(s);
    } 
    return total_entropy/get_total_map();
}

void fcm::print_alphabet(){
    for(set<string>::iterator setIt = alphabet.begin(); setIt != alphabet.end(); setIt++) {
                cout << *setIt << " ";
                //     tmp.insert(pair<char,int>(*setIt,0));
    }
    cout << endl;
}

int fcm::getAlphabetSize() {
    return this->alphabet.size();
}

float fcm::getSymbolProb(string context, string symbol) { 
    float prob = 0;
    if(mapOfMaps.find(context) != mapOfMaps.end()){
        map<string,int> tmp;
        tmp = mapOfMaps[context];
        map<string,int>::iterator it2;
        if(tmp.find(symbol) != tmp.end()) {
            prob = (float) (tmp[symbol] + this->a) / (float) (get_total_context(context) + (this->a * getAlphabetSize()));
        }
    } 
    return prob;
}   

map<string,map<string,int>> fcm::getMapOfMaps() {
    return mapOfMaps;
}

