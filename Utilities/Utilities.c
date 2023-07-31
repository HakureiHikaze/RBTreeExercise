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

unsigned StrLen(const wchar_t* str){
    size_t i = 0;
    for(i = 0; str[i]!='\0';i++);
    return i;
}

unsigned DigitLen(long n){
    if(n == 0) return 1;
    if(n >= (long)0x3b9aca00) return 10;
    if(n <= (long)0xC4653600) return 11;
    long divisor = 1;
    unsigned power = 0;
    unsigned isMinus = 0;
    if(n < 0) isMinus = 1;
    while(n / divisor){
        divisor *=10;
        power +=1;
    }
    return power+isMinus;
}