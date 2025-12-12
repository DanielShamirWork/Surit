#include "huffman_file.h"

HuffmanFileWriter::HuffmanFileWriter(const char* filename)
    : buffer_stream(filename, ios::binary), buffer(0), bit_count(0) {
}

HuffmanFileWriter::~HuffmanFileWriter() {
    flush_bits();
    buffer_stream.close();
}

void HuffmanFileWriter::write_bits(const uint8_t* bits) {
    for (size_t i = 0; bits[i] != 0; i++) {
        buffer <<= 1;
        buffer |= bits[i] & 0x01; // only change the last bit
        bit_count++;

        if (bit_count == 8) {
            // write out the full byte
            buffer_stream.put(static_cast<char>(buffer));
            buffer = 0;
            bit_count = 0;
        }
    }
}

void HuffmanFileWriter::flush_bits() {
}