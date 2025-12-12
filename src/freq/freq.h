#ifndef FREQ_H
#define FREQ_H

#include "../defs.h"
#include <unordered_map>

using namespace std;

const unordered_map<symbol, uint64_t> frequencies(const symbol * const str);

#endif // FREQ_H