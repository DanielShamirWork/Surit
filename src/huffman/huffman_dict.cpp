#include "huffman_dict.h"

HuffmanDict::HuffmanDict() 
   : map() {
}

HuffmanDict::~HuffmanDict() {
    for (auto it = map.begin(); it != map.end(); it++) {
        if (it->second != nullptr) {
            delete[] it->second;
        }
    }
}

void HuffmanDict::allocate_symbol(symbol sym, const vector<uint8_t> &code) {
    uint8_t *new_code = new uint8_t[code.size() + 1];
    copy(code.begin(), code.end(), new_code);
    new_code[code.size()] = NULL_CODE_BYTE; // null-terminate the code
    map.insert({sym, new_code});
    symbols.push_back(sym);
}

const vector<symbol> HuffmanDict::get_symbols() const {
    return symbols;
}

const uint8_t * const HuffmanDict::get_code(symbol sym) const {
    return map.at(sym);
}