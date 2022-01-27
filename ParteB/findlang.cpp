#include <iostream>
#include "lang.hpp"
#include "lang.cpp"
#include "dirent.h"
#include <string.h>

using namespace std;

string findlang(char * targetText, int k) {
    float minEstimatedBits = __FLT_MAX__;
    string foundLang = "";
    char* path = "../maps/";
    DIR *dir;
    struct dirent *ent;
    //for(int k = 1; k < 3; k++){
    string kPath = path;
    kPath += "k" + to_string(k) + "/";
    int n = kPath.length();
    char charPath[n + 1];
    strcpy(charPath, kPath.c_str());
    
    if ((dir = opendir (charPath)) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            if (ent->d_type != DT_DIR) {
                char* mapName = new char[strlen(charPath)+strlen(ent->d_name)+1];
                strcpy(mapName,charPath);
                strcat(mapName,ent->d_name);
                lang l(mapName,targetText,k,1);
                float ebits = l.getEstimatedBits();
                if(ebits < minEstimatedBits) {
                    minEstimatedBits = ebits;
                    foundLang = ent->d_name;
                }
                cout << "Map: " << ent->d_name << "\t";
                cout << "Estimated size: " << (int) ebits << " bits" << endl;
            }
        }
        closedir (dir);
    }
    //}
    printf("Text %s is written in %s and would occupy %0.3f bits\n",targetText,foundLang.c_str(),minEstimatedBits);
    //cout << "Estimated bits: " << minEstimatedBits << endl;
    return foundLang;
}

int main(int argc, char** argv){
    string foundLang = findlang(argv[1],atoi(argv[2]));
    //cout << argv[1] << "'s text language: " << foundLang << endl;
    return 0;
}