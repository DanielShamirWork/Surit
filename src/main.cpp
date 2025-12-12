#include <stdio.h>
#include "defs.h"
#include "freq/freq.h"

const symbol *str1 = "aaabbbccc";
const symbol *str2 = "abcdef";
const symbol *str3 = "11 22 33 44";

void test_str(const symbol *str) {
    unordered_map<symbol, uint64_t> freqs = frequencies(str);

    printf("string: %s\n", str);
    for (auto it = freqs.begin(); it != freqs.end(); it++) {
        printf("symbol %c -> frequency %lu\n", it->first, it->second);
    }
    printf("\n");
}

int main(int argc, char **argv) {
    test_str(str1);
    test_str(str2);
    test_str(str3);
    return 0;
}