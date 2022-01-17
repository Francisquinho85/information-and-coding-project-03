#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector

using namespace std;

class fcm {
    private:
        int k;
        int a;
        map<string,map<char,int>> mapOfMaps;
        set<char> alphabet;
        vector<char> ctx;
    public:
        fcm(int k, int a);
        fcm();
        void readFile(char * fileName);
}