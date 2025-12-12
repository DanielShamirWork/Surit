#ifndef HUFFMAN_FILE_H
#define HUFFMAN_FILE_H

#include "../defs.h"
#include "../huffman/huffman_dict.h"

#include <iostream>
#include <fstream>

using namespace std;

// Writer class for writing bits to a file using a buffer
// if symbol is not a byte, this class should not be used
class HuffmanFileWriter {
public:
    HuffmanFileWriter(const char* filename);
    ~HuffmanFileWriter();

    // void write_tree(const )
    void write_bits(const uint8_t* bits);
    void flush_bits();

private:
    ofstream buffer_stream;
    uint8_t buffer;
    uint8_t bit_count;
};

#endif // HUFFMAN_FILE_H