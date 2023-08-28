#pragma once

#include <fstream>

class reader {
public:
    reader() = delete;

    explicit reader(const std::string &file_name);
    ~reader();

    std::string read();

private:
    std::ifstream stream_;

    std::streamsize calc_buffer_length();
    void close_file();
};


class reader_exception : public std::exception {
public:
    explicit reader_exception(std::string message);
    const char* what() const noexcept override;
private:
    std::string msg_;
};