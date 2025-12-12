#ifndef HUFFMAN_DICT_H
#define HUFFMAN_DICT_H

#include "../defs.h"
#include <unordered_map>
#include <vector>

using namespace std;

#define NULL_CODE_BYTE 255 // since 0 is a valid code bit, we use 255 to indicate code termination

class HuffmanDict {
private:
    unordered_map<symbol, const uint8_t * const> map;
    vector<symbol> symbols;

public:
    HuffmanDict();
    ~HuffmanDict();

    void allocate_symbol(symbol sym, const vector<uint8_t> &code);
    const vector<symbol> get_symbols() const;
    const uint8_t * const get_code(symbol sym) const;
};

#endif // HUFFMAN_DICT_H