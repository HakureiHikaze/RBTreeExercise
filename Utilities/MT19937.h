//
// Created by guoyao.wan on 2023/7/26.
//

#pragma once
typedef struct MT19937_{
    unsigned long mtArray[624];
    unsigned long mti;
}MT19937;
typedef MT19937 RandMT;
extern MT19937* InitRandMT(unsigned long);
extern int ExtractRandMT(MT19937*);
