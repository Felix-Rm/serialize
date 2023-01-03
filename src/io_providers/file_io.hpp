#pragma once

#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>

namespace serialize {
struct file_reader {
    std::ifstream ifstream;

    explicit file_reader(const char* filename)
        : ifstream(filename) {
    }

    explicit file_reader(const std::string& filename)
        : ifstream(filename) {
    }

    explicit operator bool() const {
        return ifstream.is_open() && ifstream.good();
    }

    void read(void* buffer, std::size_t len) {
        ifstream.read((char*)buffer, len);
    }
};

struct file_writer {
    std::ofstream ofstream;

    explicit file_writer(const char* filename)
        : ofstream(filename) {
    }

    explicit file_writer(const std::string& filename)
        : ofstream(filename) {
    }

    explicit operator bool() const {
        return ofstream.is_open() && ofstream.good();
    }

    void write(const void* buffer, std::size_t len) {
        ofstream.write((const char*)buffer, len);
    }
};

}  // namespace serialize