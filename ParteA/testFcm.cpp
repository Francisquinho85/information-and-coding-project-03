#include "fcm.hpp"
#include <iostream>
#include <set>
#include <string.h>
#include <dirent.h>

using namespace std;

int main(int argc, char** argv){
    //int k =  atoi(argv[1]);
    //int a = atoi(argv[2]);
    //fcm test(k,a);
    //test.readFile("../txt/europarl-v7.bg-en.bg");
    //test.printMap();
    //test.writeMapToFile("ma.txt");
    //test.readMapFromFile("mapaPortugues.txt");
    // cout << "get_total context(ii) "<<test.get_total_context("ii")<< "\n";
    // cout << "get_entropy_context(ii) " << test.get_entropy_context("ii")<< "\n";
    // cout << "get_total_map() "<<test.get_total_map()<< "\n";
    // cout << "get_entropy_map() " << test.get_entropy_map()<< "\n";
    //test.printMap();
    //test.print_alphabet();
    //cout << test.getSymbolProb("ii","s") << endl;
    // for(int k=1; k<=5; k++){
    //     fcm test(k,1);
    //     test.readFile(argv[1]);
    //     string writeString = "../maps/k";
    //     writeString.append(to_string(k));
    //     writeString += '/'; 
    //     string fileName = argv[1];
        
    //     std::size_t found = fileName.find_last_of("/\\");
    //     fileName = fileName.substr(found+1);

    //     writeString.append(fileName);
    //     //cout << writeString << endl; 
    //     char *charString = new char[writeString.length() + 1]; 
    //     strcpy(charString, writeString.c_str());
    //     test.writeMapToFile(charString);
    // }
    
    DIR *dir;
    struct dirent *ent;
    char * path = argv[1];
    if ((dir = opendir (path)) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            
            //printf ("%s\n", ent->d_name);
            char* toRead = new char[strlen(path)+strlen(ent->d_name)+1];
            strcpy(toRead,path);
            strcat(toRead,ent->d_name);
            if(ent->d_name[0]!='.'){
                for(int k=1; k<=5; k++){
                    fcm test(k,1);

                    test.readFile(toRead);
                    string writeString = "../maps/k";
                    writeString.append(to_string(k));
                    writeString += '/'; 
                    string fileName = ent->d_name;
                    
                    std::size_t found = fileName.find_last_of("/\\");
                    fileName = fileName.substr(found+1);

                    writeString.append(fileName);
                    cout << writeString << endl; 
                    char *charString = new char[writeString.length() + 1]; 
                    strcpy(charString, writeString.c_str());
                    test.writeMapToFile(charString);
                }
                //cout << toRead << endl;
            }
            
        }
        closedir (dir);
    } else {
    /* could not open directory */
        perror ("");
    return EXIT_FAILURE;
    }
    return 0;
}