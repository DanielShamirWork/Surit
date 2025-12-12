#include "huffman.h"

#include "../freq/freq.h"
#include <queue>
#include <functional>

using namespace std;

HuffmanNode *build_tree(const symbol * const str) {
    if (str[0] == '\0') {
        return nullptr; // empty string case
    }

    unordered_map<symbol, uint64_t> freqs = frequencies(str);
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareHuffmanNode> min_heap;

    // create all leaf nodes and insert them into the minimum heap
    for (auto it = freqs.begin(); it != freqs.end(); it++) {
        HuffmanNode* node = new HuffmanNode(it->first, it->second);
        min_heap.push(node);
    }

    // build all the internal nodes
    while (min_heap.size() > 1) {
        // the left child has the smaller frequency (unless they are equal)
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

// this function generates the code for each symbol by traversing the tree recursively
void generate_code_recursive(const HuffmanNode *node, vector<uint8_t> &code, HuffmanDict &dict) {
    if (node == nullptr) {
        return;
    }

    // leaf node
    if (node->left == nullptr && node->right == nullptr) {
        dict.allocate_symbol(node->sym, code);
        return;
    }

    if (node->left != nullptr) {
        code.push_back(BIT_TO_CODE(0));
        generate_code_recursive(node->left, code, dict);
        code.pop_back();
    }

    if (node->right != nullptr) {
        code.push_back(BIT_TO_CODE(1));
        generate_code_recursive(node->right, code, dict);
        code.pop_back();
    }
}

const HuffmanDict generate_huffman_dict(const symbol * const str) {
    HuffmanDict dict;

    if (str[0] == '\0') {
        return dict; // empty string case
    }

    const HuffmanNode * const tree_root = build_tree(str);
    vector<uint8_t> code;

    // Special case for a single unique character
    if (tree_root->left == nullptr && tree_root->right == nullptr) {
        code.push_back(BIT_TO_CODE(0));
        dict.allocate_symbol(tree_root->sym, code);
    } else {
        generate_code_recursive(tree_root, code, dict);
    }

    delete tree_root; // free the tree memory
    return dict;
}