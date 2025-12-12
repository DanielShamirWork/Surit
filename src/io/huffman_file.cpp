#include "huffman_file.h"

HuffmanFileWriter::HuffmanFileWriter(const char* filename)
    : buffer_stream(filename, ios::binary), buffer(0), bit_count(0) {
}

HuffmanFileWriter::~HuffmanFileWriter() {
    flush_bits();
    buffer_stream.close();
}

void HuffmanFileWriter::write_code(const uint8_t* code) {
    for (size_t i = 0; code[i] != 0; i++) {
        buffer <<= 1;
        buffer |= CODE_TO_BIT(code[i]) & 0x01; // only change the last bit
        bit_count++;

        if (bit_count == 8) {
            buffer_stream.put(static_cast<char>(buffer)); // write out the full byte
            buffer = 0;
            bit_count = 0;
        }
    }
}

void HuffmanFileWriter::flush_bits() {
}