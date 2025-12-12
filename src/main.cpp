#include <stdio.h>
#include "defs.h"
#include "freq/freq.h"
#include "huffman/huffman.h"
#include "io/huffman_file.h"
#include <unordered_map>
#include <functional>
#include <string>

using namespace std;

const symbol *str1 = "aabcbad";

void test_frequencies(const symbol *str) {
    unordered_map<symbol, uint64_t> freqs = frequencies(str);

    printf("string: %s\n", str);
    for (auto it = freqs.begin(); it != freqs.end(); it++) {
        printf("symbol %c -> frequency %lu\n", it->first, it->second);
    }
    printf("\n");
}

void test_build_tree(const symbol *str) {
    printf("string: %s\n", str);
    HuffmanNode *root = build_tree(str);

    // recursive lambda function (pretty cool!)
    std::function<void(HuffmanNode*, int)> print_node = [&](HuffmanNode *node, int depth) {
        // indent
        string indent(depth, '\t');
        
        printf("node {sym: %c, freq: %lu}\n", node->sym, node->frequency);
        if (node->left != nullptr) {
            printf("%sleft: ", indent.c_str());
            print_node(node->left, depth + 1);
        }
        if (node->right != nullptr) {
            printf("%sright: ", indent.c_str());
            print_node(node->right, depth + 1);
        }
    };

    print_node(root, 0);
    printf("\n");
}

void test_generate_huffman_dict(const symbol *str) {
    printf("string: %s\n", str);
    HuffmanNode *root = build_tree(str);
    HuffmanDict dict = generate_huffman_dict(root);

    printf("dict:\n");
    for (symbol sym : dict.get_symbols()) {
        const uint8_t *code = dict.get_code(sym);
        printf("symbol %c -> code: ", sym);
        for (size_t i = 0; code[i] != 0; i++) {
            printf("%u", CODE_TO_BIT(code[i])); // convert back to 0/1
        }
        printf("\n");
    }
    printf("\n");
}

void test_write_file(const symbol *str, char *filename = "output.huff") {
    printf("string: %s\n", str);
    HuffmanNode *root = build_tree(str);
    HuffmanDict dict = generate_huffman_dict(root);

    HuffmanFileWriter writer(filename);

    for (size_t i = 0; str[i] != '\0'; i++) {
        const uint8_t *code = dict.get_code(str[i]);
        writer.write_bits(code);
    }
    writer.flush_bits();

    printf("written to output.huff\n\n");
}

int main(/* int argc, char **argv */) {
    // test_frequencies(str1);

    // test_build_tree(str1);

    test_generate_huffman_dict(str1);

    // test_write_file(str1, "str1.huff");

    return 0;
}