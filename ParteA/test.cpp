#include "fcm.hpp"
#include <iostream>

using namespace std;

int main(int argc,char** argv){
    int k =  atoi(argv[1]);
    int a = atoi(argv[2]);
    fcm test(k,a);
    //test.readFile("texto.txt");
    //test.printMap();
    //test.writeMapToFile("mapaPortugues.txt");
    test.readMapFromFile("mapaPortugues.txt");
    test.printMap();
    return 0;
}