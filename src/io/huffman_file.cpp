#include "huffman_file.h"

HuffmanFileWriter::HuffmanFileWriter(const char* filename, const HuffmanDict &dict)
    : buffer_stream(filename, ios::binary), dict(dict), buffer(0), bit_count(0) {
}

HuffmanFileWriter::~HuffmanFileWriter() {
    flush_bits();
    buffer_stream.close();
}

void HuffmanFileWriter::write_string(const symbol * const str) {
    // write the file header, i.e. the magic number
    buffer_stream.write(reinterpret_cast<const char*>(&HUFFMAN_FILE_MAGIC), sizeof(uint32_t));

    write_dict();

    for (size_t i = 0; str[i] != '\0'; i++) {
        write_symbol_code(str[i]);
    }

    flush_bits();
}

void HuffmanFileWriter::write_dict() {
    const vector<symbol> symbols = dict.get_symbols();
    uint32_t num_entries = symbols.size();
    // first write the number of entries
    buffer_stream.write(reinterpret_cast<const char*>(&num_entries), sizeof(uint32_t));

    // then write each entry, which is a symbol followed by its code length (in bits) and code bits
    for (symbol sym : symbols) {
        const uint8_t *code = dict.get_code(sym);
        uint16_t code_len = get_code_length(code);

        buffer_stream.write(reinterpret_cast<const char*>(&sym), sizeof(sym));
        buffer_stream.write(reinterpret_cast<const char*>(&code_len), sizeof(code_len));

        write_bits(code, code_len);
    }
}

void HuffmanFileWriter::write_symbol_code(symbol sym) {
    const uint8_t *code = dict.get_code(sym);
    uint16_t code_len = get_code_length(code);
    write_bits(code, code_len);
}

void HuffmanFileWriter::write_bits(const uint8_t * const bits, size_t num_bits) {
    for (size_t i = 0; i < num_bits; i++) {
        buffer <<= 1;
        buffer |= CODE_TO_BIT(bits[i]) & 0x01; // only change the last bit
        bit_count++;

        if (bit_count == 8) {
            buffer_stream.put(static_cast<char>(buffer)); // write out the full byte
            buffer = 0;
            bit_count = 0;
        }
    }
}

void HuffmanFileWriter::flush_bits() {
    if (bit_count > 0) {
        buffer <<= 8 - bit_count;
        buffer_stream.put(static_cast<char>(buffer));
    }
    buffer = 0;
    bit_count = 0;
}