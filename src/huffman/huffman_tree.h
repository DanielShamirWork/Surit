#include "../defs.h"

class HuffmanNode {
public:
    symbol sym;
    uint16_t frequency;
    HuffmanNode* left;
    HuffmanNode* right;
};