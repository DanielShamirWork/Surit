#ifndef HUFFMAN_FILE_H
#define HUFFMAN_FILE_H

#include "../defs.h"
#include "../huffman/huffman_dict.h"

#include <iostream>
#include <fstream>

using namespace std;

#define HUFFMAN_FILE_MAGIC "HUFF" // "HUFF" in little-endian

// huffman file structure:
//  {
//      [HuffmanFileHeader]
//      [dictionary segment]
//      [compressed data segment]
//  }

// HuffmanFileHeader:
//   uint32_t magic: should be HUFFMAN_FILE_MAGIC

// dictionary segment:
//   uint32_t num_entries
//   for each entry:
//     symbol sym
//     uint16_t code_len
//     uint8_t[code_len] code bits

// compressed data segment:
//   sequence of bits representing the compressed data

// Writer class for writing bits to a file using a buffer
// if symbol is not a byte, this class should not be used
class HuffmanFileWriter {
public:
    HuffmanFileWriter(const char* filename, const HuffmanDict & dict);
    ~HuffmanFileWriter();
    
    void write_string(const symbol * const str);

private:
    void write_dict();
    void write_symbol_code(symbol sym);
    void write_bits(const uint8_t * const bits, size_t num_bits);
    void flush_bits(); // flush any remaining bits in the buffer to the file

private:
    ofstream buffer_stream;
    const HuffmanDict &dict;
    uint8_t buffer;
    uint8_t bit_count;
};

class HuffmanFileReader {
    // to be implemented
};

#endif // HUFFMAN_FILE_H