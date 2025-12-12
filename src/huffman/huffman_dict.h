#ifndef HUFFMAN_DICT_H
#define HUFFMAN_DICT_H

#include "../defs.h"
#include <unordered_map>
#include <vector>

using namespace std;

// since we want 0 to be the null terminator of the code array, we need to
// offset the stored code bytes by 254
// 0 -> 254
// 1 -> 255
#define BIT_TO_CODE(x) ((x) + 254) // convert bit (0 or 1) to stored code byte
#define CODE_TO_BIT(x) ((x) - 254) // convert stored code byte to bit (0 or 1)

class HuffmanDict {
public:
    HuffmanDict();
    ~HuffmanDict();

    void allocate_symbol(symbol sym, const vector<uint8_t> &code);
    const vector<symbol> get_symbols() const;
    const uint8_t * const get_code(symbol sym) const;

private:
    unordered_map<symbol, const uint8_t * const> map;
    vector<symbol> symbols;
};

inline size_t get_code_length(const uint8_t* code) {
    size_t len = 0;
    while (code[len] != 0) {
        len++;
    }
    return len;
}

#endif // HUFFMAN_DICT_H