#pragma once

#include <fstream>

class writer {
public:
    writer() = delete;

    explicit writer(const std::string &file_name);
    ~writer();

    void write(const std::string &data);

private:
    std::ofstream stream_;

    void close_file();
};


class writer_exception : public std::exception {
public:
    explicit writer_exception(std::string message);
    const char* what() const noexcept override;
private:
    std::string msg_;
};