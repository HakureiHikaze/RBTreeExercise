//
// Created by guoyao.wan on 2023/7/26.
//

#include "MT19937.h"
#include <stdlib.h>
int int_(unsigned long x) {
    return (int)(0xffffffff & x);
}
void twist_(MT19937* mt){
    for( int i = 0; i<624; i++){
        int  y = int_(mt->mtArray[i]&0x80000000 + (mt->mtArray[(i+1)%624] & 0x7fffffff));
        mt->mtArray[i] = (y>>1) ^ mt->mtArray[(i+397)%624];
        if(y% 2 != 0){
            mt->mtArray[i] = mt->mtArray[i] ^ 0x9908b0df;
        }
    }
}
MT19937* InitRandMT(unsigned long seed){
    MT19937* mt = (MT19937*) calloc(1,sizeof (MT19937));
    mt->mti = 0;
    mt->mtArray[0] = seed;
    for(int i =1; i<624; i++){
        mt->mtArray[i] = int_(1812433253 * (mt->mtArray[i-1] ^ mt->mtArray[i-1] >> 30) + i);
    }
    return mt;
}

int ExtractRandMT(MT19937* mt){
    if(!mt->mti){
        twist_(mt);
    }
    unsigned long y = mt->mtArray[mt->mti];
    y = y ^ y >> 11;
    y = y ^ y << 7 & 2636928640;
    y = y ^ y << 15 & 4022730752;
    y = y ^ y >> 18;
    mt->mti = (mt->mti+1) % 624;
    return int_(y);
}

void MT19937Release(MT19937* mt){
    if(mt)free(mt);
}