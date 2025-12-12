#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "../defs.h"
#include "huffman_tree.h"
#include "huffman_dict.h"
#include <unordered_map>
#include <vector>

HuffmanNode *build_tree(const symbol * const str);
const HuffmanDict generate_huffman_dict(const symbol * const str);

#endif // HUFFMAN_H