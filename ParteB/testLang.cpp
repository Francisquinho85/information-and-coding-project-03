#include "lang.hpp"
#include <iostream>

using namespace std;

int main (int argc,char** argv){

    lang l("../ParteA/mapaPortugues.txt","../ParteA/texto.txt",2,1);
    l.getEstimatedBits();
    return 0;
}