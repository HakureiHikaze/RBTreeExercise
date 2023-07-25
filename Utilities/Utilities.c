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