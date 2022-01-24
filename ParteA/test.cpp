#include "fcm.hpp"
#include <iostream>

using namespace std;

int main(int argc,char** argv){
    int k =  atoi(argv[1]);
    int a = atoi(argv[2]);
    fcm test(k,a);
    test.readFile("texto.txt");
    test.printMap();
    //test.writeMapToFile("mapaPortugues.txt");
    //test.readMapFromFile("mapaPortugues.txt");
    cout << "get_total context(ii) "<<test.get_total_context("ii")<< "\n";
    cout << "get_entropy_context(ii) " << test.get_entropy_context("ii")<< "\n";
    cout << "get_total_map() "<<test.get_total_map()<< "\n";
    cout << "get_entropy_map() " << test.get_entropy_map()<< "\n";
    //test.printMap();
    return 0;
}