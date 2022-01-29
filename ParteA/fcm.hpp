#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>

using namespace std;

/// A class with the aim of collecting statistical information about texts, using finite-context models.

/// ### Example
/// ~~~~~~~~~~~~~~~~~~~~~~.cpp
/// int k =  atoi(argv[1]);
/// int a = atoi(argv[2]);
/// fcm test(k,a);
/// ~~~~~~~~~~~~~~~~~~~~~~
class fcm {
    private:
        /// The order of the model.
        int k;
        /// Smoothing parameter.
        int a;
        /// The map with all the contents concerning the number of times each letter appeared after a certain context.
        map<string,map<string,int>> mapOfMaps;
        /// Vector with all the contexts.
        vector<string> ctx;
        /// Set with all the letters of the specific alphabet.
        set<string> alphabet;
    public:
        /// Constructor of fcm class
        /// @param k The order of the model.
        /// @param a Smoothing parameter.
        fcm(int k, int a);
        /// Constructor of fcm class
        fcm();
        /// Reading a particular file for analysis.
        /// @param fileName File to be read.
        void readFile(char * fileName);
        /// Print the map.
        void printMap();
        /// Update the alphabet with a new character.
        /// @param c Character to be added on the map.
        void updateMapAlphabet(char c);
        /// Write the map in a file.
        /// @param fileToWrite File for writing the map.
        void writeMapToFile(char * fileToWrite);
        /// Read the map from a file.
        /// @param fileToRead File for reading a map.
        void readMapFromFile(char * fileToRead);
        /// Get the total of number of times letters appear after a given context.
        /// @param s String with the given context.
        /// @return The number of times letters appear after a given context.
        int get_total_context(string s);
        /// Get the entropy of a given context.
        /// @param s String with the given context.
        /// @return Entropy of a given context.
        double get_entropy_context(string s);
        /// Get the total of number of times the letters appeared in all map.
        /// @return The number of times the letters appeared in all map.
        int get_total_map();
        /// Get the entropy of all map.
        /// @return Entropy of all map.
        double get_entropy_map();
        /// Print all the letters of the specific alphabet.
        void print_alphabet();
        /// Get the MapOfMaps content
        /// @return description of the return value
        map<string,map<string,int>> getMapOfMaps();
        /// Get the specific alphabet size.
        /// @return Size of alphabet.
        int getAlphabetSize();
        /// Get the probability of a symbol.
        /// @param context String with the given context.
        /// @param symbol String with the given symbol.
        /// @return Probability of a symbol.
        float getSymbolProb(string context, string symbol);
};
