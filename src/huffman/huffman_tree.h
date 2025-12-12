#ifndef HUFFMAN_NODE_H
#define HUFFMAN_NODE_H

#include "../defs.h"

class HuffmanNode {
public:
    symbol sym;
    uint64_t frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(symbol sym, uint64_t frequency, HuffmanNode* left, HuffmanNode* right)
        : sym(sym), frequency(frequency), left(left), right(right) {}

    HuffmanNode(symbol sym, uint64_t frequency)
        : sym(sym), frequency(frequency), left(nullptr), right(nullptr) {}

    ~HuffmanNode() {
        if (left != nullptr) {
            delete left;
            left = nullptr;
        }
        if (right != nullptr) {
            delete right;
            right = nullptr;
        }
    }
};

struct CompareHuffmanNode {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return l->frequency > r->frequency;
    }
};

#endif // HUFFMAN_NODE_H