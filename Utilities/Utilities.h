//
// Created by guoyao.wan on 2023/7/25.
//
#pragma once
/// DJB2 algorithm implementation
/// \param s NULL terminated string to hash
/// \return 64-bit hash result
extern uint64_t GetDJB2Hash(const char* s);