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
        map<string,map<string,int>> mapOfMaps;
        vector<string> ctx;
    public:
        fcm(int k, int a);
        fcm();
        void readFile(char * fileName);
        void printMap();
        void updateMapAlphabet(char c);
        void writeMapToFile(char * fileToWrite);
        void readMapFromFile(char * fileToRead);
        int get_total_context(string s);
        double get_entropy_context(string s);
        int get_total_map();
        double get_entropy_map();
        set<string> alphabet;
        void print_alphabet();
};