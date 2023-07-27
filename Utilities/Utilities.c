//
// Created by guoyao.wan on 2023/7/25.
//

#include <stdint.h>
#include "Utilities.h"

uint64_t GetDJB2Hash(const char* s)
{
    uint64_t hash = 5381; /* init value */
    size_t i = 0;
    while (s[i] != '\0')
    {
        hash = ((hash << 5) + hash) + s[i];
        i++;
    }
    return hash;
}

NonRedundantRNG* NonRedundantRNGInit(size_t seed, int startAt, unsigned length){
    if(length < 1) exit(-100);
    if(length > 2147483647) exit(-101);
    NonRedundantRNG* rng = (NonRedundantRNG*) calloc(1,sizeof (NonRedundantRNG));
    rng->mt = InitRandMT(seed);
    rng->list = SLListInit();
    rng->length =length;
    rng->startAt = startAt;
    rng->seed = seed;
    rng->remain = length;
    for(int i = 0;i<(int)length;i++){
        SLListAppend(rng->list,startAt + i);
    }
    return rng;
}
int NRRNGExtract(NonRedundantRNG* rng){
    int temp = 0;
    if(rng->remain) temp = SLListDelete(rng->list, ExtractRandMT(rng->mt)%rng->list->length);
    rng->remain -=1;
    return temp;
}
void NRRNGRelease(NonRedundantRNG* rng){
    if(rng){
        MT19937Release(rng->mt);
        SLListRelease(rng->list);
        free(rng);
    }
}