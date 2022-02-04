#include "fcm.hpp"
#include <iostream>

using namespace std;

int main(int argc, char** argv){
    int k =  atoi(argv[1]);
    int a = atoi(argv[2]);
    char * file = argv[3];
    string context = argv[4];
    string symbol = argv[5];
    fcm test(k,a);
    test.readMapFromFile(file);
    cout << "Context total hits: "<< context << " -> " << test.get_total_context(context)<< "\n";
    cout << "Context entropy: "<< context << " -> "<< test.get_entropy_context(context)<< "\n";
    cout << "Map total hits "<<test.get_total_map()<< "\n";
    cout << "Map entropy " << test.get_entropy_map()<< "\n";
    cout << "Symbol after context probability: "<< context << " - " << symbol << " -> " << test.getSymbolProb(context, symbol) << endl;
    cout << "Alphabet: " << endl;
    test.print_alphabet();
    return 0;
}