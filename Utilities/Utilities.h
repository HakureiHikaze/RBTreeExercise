//
// Created by guoyao.wan on 2023/7/25.
//
#pragma once
#include "MT19937.h"
#include <stdint.h>
#include<stdlib.h>
#include "SinglyLinkedList.h"
typedef struct nonRedundantRNG_{
    MT19937* mt;
    SLList* list;
    size_t seed;
    unsigned length;
    int startAt;
    unsigned remain;
}NonRedundantRNG;
/// DJB2 algorithm implementation
/// \param s NULL terminated string to hash
/// \return 64-bit hash result
extern uint64_t GetDJB2Hash(const char* s);
extern NonRedundantRNG* NonRedundantRNGInit(size_t seed, int startAt, unsigned length);
extern int NRRNGExtract(NonRedundantRNG* rng);
extern void NRRNGRelease(NonRedundantRNG* rng);
extern unsigned StrLen(const wchar_t* str);
extern unsigned DigitLen(long n);