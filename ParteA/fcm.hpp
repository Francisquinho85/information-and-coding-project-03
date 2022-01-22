#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>

using namespace std;

class fcm {
    private:
        int k;
        int a;
        map<string,map<char,int>> mapOfMaps;
        vector<char> ctx;
    public:
        fcm(int k, int a);
        fcm();
        void readFile(char * fileName);
        void printMap();
        void updateMapAlphabet(char c);
        void writeMapToFile(char * fileToWrite);
        void readMapFromFile(char * fileToRead);
        set<char> alphabet;
};