#include <stdio.h>
#include "defs.h"
#include "freq/freq.h"
#include "huffman/huffman.h"
#include "io/huffman_file.h"
#include <unordered_map>
#include <functional>
#include <string>
#include <filesystem>

using namespace std;

void test_frequencies(const symbol *str) {
    unordered_map<symbol, uint64_t> freqs = frequencies(str);

    printf("Frequencey test on string: %s\n", str);
    for (auto it = freqs.begin(); it != freqs.end(); it++) {
        printf("symbol %c -> frequency %lu\n", it->first, it->second);
    }
    printf("\n");
}

void test_build_tree(const symbol *str) {
    printf("Build tree test on string: %s\n", str);
    HuffmanNode *root = build_tree(str);

    // recursive lambda function (pretty cool!)
    std::function<void(HuffmanNode*, int)> print_node = [&](HuffmanNode *node, int depth) {
        if (node == nullptr) {
            return;
        }
        
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
    printf("Generate Huffman dict test on string: %s\n", str);
    HuffmanDict dict = generate_huffman_dict(str);

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
    printf("Write file test on string: %s\n", str);
    HuffmanDict dict = generate_huffman_dict(str);

    filesystem::remove(filename); // remove existing file if any
    HuffmanFileWriter writer(filename, dict);

    writer.write_string(str);

    printf("written to %s\n", filename);
    printf("\n");
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <string>\n", argv[0]);
        return 1;
    }

    const symbol *str = (const symbol *)argv[1];
    test_frequencies(str);

    test_build_tree(str);

    test_generate_huffman_dict(str);

    test_write_file(str, "output.huff");

    return 0;
}