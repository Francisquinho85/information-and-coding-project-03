#include "fcm.hpp"
#include <iostream>

using namespace std;

int main(int argc, char** argv){
    int k =  atoi(argv[1]);
    int a = atoi(argv[2]);
    char * path = argv[3];
    char * file = argv[4];
    fcm test(k,a);
    test.readFile(path);
    test.writeMapToFile(file);
    test.printMap();
    return 0;
}
