#include "huffman.h"

#include "../freq/freq.h"
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;

HuffmanNode *build_tree(const symbol * const str) {
    unordered_map<symbol, uint64_t> freqs = frequencies(str);
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareHuffmanNode> min_heap;

    // create all leaf nodes and insert them into the minimum heap
    for (auto it = freqs.begin(); it != freqs.end(); it++) {
        HuffmanNode* node = new HuffmanNode(it->first, it->second);
        min_heap.push(node);
    }

    // build all the internal nodes
    while (min_heap.size() > 1) {
        HuffmanNode* left = min_heap.top();
        min_heap.pop();
        HuffmanNode* right = min_heap.top();
        min_heap.pop();

        // an internal node is one with a frequency equals the sum of child frequencies
        HuffmanNode* parent = new HuffmanNode('\0', left->frequency + right->frequency, left, right);
        min_heap.push(parent);
    }
    
    return min_heap.top();
}

symbol *compress(const symbol * const str) {
    return nullptr;
}

symbol *decompress(const symbol * const str) {
    return nullptr;
}