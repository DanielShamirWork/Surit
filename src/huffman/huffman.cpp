#include "huffman.h"

#include "../freq/freq.h"
#include <queue>
#include <stack>
#include <functional>

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

const HuffmanDict generate_huffman_dict(const HuffmanNode * const tree_root) {
    HuffmanDict dict;
    stack<const HuffmanNode *> node_stack;
    stack<uint8_t> code_stack;
    vector<uint8_t> code;

    // DFS iteration over the tree
    node_stack.push(tree_root);
    while (!node_stack.empty()) {
        const HuffmanNode * const node = node_stack.top();
        node_stack.pop();

        if (code_stack.size() > 0) {
            code.push_back(code_stack.top());
            code_stack.pop();
        }
        
        if (node->right != nullptr) {
            code_stack.push(BIT_TO_CODE(1));
            node_stack.push(node->right);
        }
        if (node->left != nullptr) {
            code_stack.push(BIT_TO_CODE(0));
            node_stack.push(node->left);
        }
        if (node->left == nullptr && node->right == nullptr) {
            dict.allocate_symbol(node->sym, code);
            code.pop_back(); // don't forget to erase the last code
        }
    }

    return dict;
}

symbol *compress(const symbol * const str) {
    return nullptr;
}

symbol *decompress(const symbol * const str) {
    return nullptr;
}