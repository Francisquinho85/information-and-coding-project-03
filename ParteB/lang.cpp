#include <iostream>
#include <fstream>
#include "lang.hpp"
#include "../ParteA/fcm.hpp"
#include "../ParteA/fcm.cpp"
#include <math.h>
#include <map>

using namespace std;

lang::lang(char * rT, char * aT, int k, int a){
    reprText = rT;
    analysisText = aT;
    this->k = k;
    alpha = (double)a/100;
    estimatedBits = 0;
    kDone = 0;
}

float lang::getEstimatedBits() {
    fcm f(k,alpha);
    f.readMapFromFile(reprText),
    this->rTMap = f.getMapOfMaps();
    
    ifstream ifs(analysisText);
    kDone = 0;
    char c;
    string s;
    string ctx;
    while(ifs.get(c)) {

        if(c<0 || c >127){
            s = "";
            s += c;
            ifs.get(c);
            s += c;
        }
        else{
            s = c;
        }

        if(c == '\n' || c == '\t' || c == '\r'){
            continue;
        }

        kDone++;
        if(k < kDone){
            if(rTMap.find(ctx) != rTMap.end()) {
                map<string,int> tmp1 = rTMap[ctx];
                int charElem = tmp1[s];
                
                if (charElem != 0) {
                    estimatedBits += -(log2((float) f.getSymbolProb(ctx,s)));
                } else {
                    estimatedBits += -(log2((float) alpha / (float) (f.get_total_context(ctx) + (alpha * f.getAlphabetSize()) )));
                }

            } else {
                estimatedBits += -(log2( 1 / (float) f.getAlphabetSize()));
            }

            //Next context
            if(ctx[0] < 0 || ctx[0] > 127) ctx.erase(ctx.cbegin());
            ctx.erase(ctx.cbegin());  
            ctx += s;
        } else {
            ctx += s;
        }
    }
    ifs.close();    
    return estimatedBits;
    //printf("Estimated bits: %0.2f\n",estimatedBits);
}

int lang::get_kDone(){
    return kDone;
}