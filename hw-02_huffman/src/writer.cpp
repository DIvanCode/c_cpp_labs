#include "writer.hpp"

#include "logger.hpp"
#include <iostream>

writer::writer(const std::string &file_name) {
    try {
        logger::log("try to open file " + file_name);
        stream_.open(file_name, std::ios::out | std::ios::binary);
        logger::log("file has been opened successfully");
    } catch (...) {
        logger::log("failed to open file");
    }
}

writer::~writer() {
    close_file();
}

void writer::write(const std::string &data) {
    logger::log("try to write data");

    stream_.write(data.c_str(), (std::streamsize) data.size());
    logger::log("data has been written successfully");

    close_file();
}

void writer::close_file() {
    if (stream_.is_open()) {
        logger::log("try to close file");
        stream_.close();
        logger::log("file closed successfully");
    }
}


writer_exception::writer_exception(std::string message):
        msg_(std::move(message)) {}

const char* writer_exception::what() const noexcept {
    return msg_.c_str();
}