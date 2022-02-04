#include "fcm.hpp"
#include <iostream>
#include <set>
#include <string.h>
#include <dirent.h>

using namespace std;

int main(int argc, char** argv){
       
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