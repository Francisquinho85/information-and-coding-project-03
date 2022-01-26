#pragma once
#include "../ParteA/fcm.hpp"
#include <map>

class lang {
    private:
        char * reprText;
        char * analysisText;
        map<string,map<string,int>> rTMap;
        float estimatedBits;
        int k;
        int alpha;
    public:
        lang(char * reprText, char * analysisText, int k, int a);
        lang();
        void getEstimatedBits();
};
