#include "fcm.hpp"
#include <iostream>

using namespace std;

int main(int argc,char** argv){
    int k =  atoi(argv[1]);
    int a = atoi(argv[2]);
    fcm test(k,a);
    test.readFile("texto.txt");
    int s = test.alphabet.size();
    cout << "SIZE " << s << '\n';
    test.printMap();
    return 0;
}