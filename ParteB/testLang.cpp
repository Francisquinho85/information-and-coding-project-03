#include "lang.hpp"
#include <iostream>

using namespace std;

int main (int argc,char** argv){
    char * file = argv[1];
    char * map = argv[2];
    int k = atoi(argv[3]);
    int a = atoi(argv[4]);
    lang l(map,file,k,a);
    printf("Estimated bits: %0.2f\n",l.getEstimatedBits());
    return 0;
}