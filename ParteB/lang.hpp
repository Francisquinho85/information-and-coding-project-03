#pragma once
#include "../ParteA/fcm.hpp"
#include <map>

/// A class that accepts two files: one, with a text representing the class ri (for example, representing a certain language); the other, with the text under analysis, t.

/// ### Example
/// ~~~~~~~~~~~~~~~~~~~~~~.cpp
/// lang l("../ParteA/mapaPortugues.txt","../ParteA/texto.txt",2,1);
/// cout<<l.getEstimatedBits();
/// ~~~~~~~~~~~~~~~~~~~~~~
class lang {
    private:
        /// File text representing the class ri.
        char * reprText;
        /// File text under analysis, t.
        char * analysisText;
        /// The map with all the contents concerning the number of times each letter appeared after a certain context related to the representing class ri.
        map<string,map<string,int>> rTMap;
        /// The estimated number of bits required to compress t, using the model computed from ri.
        float estimatedBits;
        /// The order of the model.
        int k;
        /// Smoothing parameter.
        double alpha;
    public:
        /// Constructor of lang class
        /// @param reprText File text representing the class ri.
        /// @param analysisText File text under analysis, t.
        /// @param k The order of the model.
        /// @param a Smoothing parameter.
        lang(char * reprText, char * analysisText, int k, int a);
        /// Constructor of lang class
        lang();
        /// Get the estimated number of bits required to compress t, using the model computed from ri.
        /// @return The estimated number of bits required to compress t, using the model computed from ri.
        float getEstimatedBits();
};
