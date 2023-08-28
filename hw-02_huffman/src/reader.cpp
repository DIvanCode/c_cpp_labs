#include "reader.hpp"

#include "logger.hpp"
#include <iostream>
#include <vector>

reader::reader(const std::string &file_name) {
    try {
        logger::log("try to open file " + file_name);
        stream_.open(file_name, std::ios::in | std::ios::binary);
        logger::log("file has been opened successfully");
    } catch (...) {
        logger::log("failed to open file");
    }
}

reader::~reader() {
    close_file();
}

std::string reader::read() {
    logger::log("try to read data");

    std::streamsize length = calc_buffer_length();
    std::vector<char> buffer(length, 0);

    stream_.read(buffer.data(), length);

    logger::log("data has been read successfully");

    close_file();

    return {buffer.begin(), buffer.end()};
}

std::streamsize reader::calc_buffer_length() {
    stream_.seekg(0, std::ifstream::end);
    std::streamsize length = stream_.tellg();
    stream_.seekg(0, std::ifstream::beg);

    return length;
}

void reader::close_file() {
    if (stream_.is_open()) {
        logger::log("try to close file");
        stream_.close();
        logger::log("file closed successfully");
    }
}


reader_exception::reader_exception(std::string message):
    msg_(std::move(message)) {}

const char* reader_exception::what() const noexcept {
    return msg_.c_str();
}