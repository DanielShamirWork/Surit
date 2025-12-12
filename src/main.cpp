#include <stdio.h>
#include "defs.h"
#include "freq/freq.h"
#include "huffman/huffman.h"
#include <functional>
#include <string>

using namespace std;

const symbol *str1 = "aaabbbccc";
const symbol *str2 = "abcdef";
const symbol *str3 = "11 22 33 44";

void test_frequencies(const symbol *str) {
    unordered_map<symbol, uint64_t> freqs = frequencies(str);

    printf("string: %s\n", str);
    for (auto it = freqs.begin(); it != freqs.end(); it++) {
        printf("symbol %c -> frequency %lu\n", it->first, it->second);
    }
    printf("\n");
}

void test_build_tree(const symbol *str) {
    HuffmanNode *root = build_tree(str);

    // recursive lambda function (pretty cool!)
    std::function<void(HuffmanNode*, int)> print_node = [&](HuffmanNode *node, int depth) {
        // indent
        string indent(depth, ' ');
        
        printf("%snode {sym: %c, freq: %lu}\n", indent.c_str(), node->sym, node->frequency);
        if (node->left != nullptr) {
            printf("left: ");
            print_node(node->left, depth + 1);
        }
        if (node->right != nullptr) {
            printf("right: ");
            print_node(node->right, depth + 1);
        }
    };

    print_node(root, 0);
    printf("\n");
}

int main(/* int argc, char **argv */) {
    // test_frequencies(str1);
    // test_frequencies(str2);
    // test_frequencies(str3);

    test_build_tree(str1);
    // test_build_tree(str2);
    // test_build_tree(str3);

    return 0;
}