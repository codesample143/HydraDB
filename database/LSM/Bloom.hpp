#pragma once

#ifndef BLOOM_H
#define BLOOM_H
using namespace std;

#include <iostream>
#include <cstdint>
#include <cmath>
#include <array>
#include <vector>

#include "MurmurHash.hpp"

template<class K>
class BloomFilter{
    BloomFilter(uint64_t n, double fp){
        double denom = 0.480453013918201;
        double size = -1 * (double) n * (log(fp) / denom);
        m_bits = vector<bool>((int) size);
        double ln2 = 0.693147180559945;
        m_numHashes = (int) ceil( (size / n) * ln2);  // ln(2)
    };
    
};

#endif