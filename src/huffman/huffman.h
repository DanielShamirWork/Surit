#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "../defs.h"
#include "huffman_tree.h"

HuffmanNode *build_tree(const symbol * const str);

symbol *compress(const symbol * const str);
symbol *decompress(const symbol * const str);

#endif