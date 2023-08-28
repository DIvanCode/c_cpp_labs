#include "logger.hpp"

#include <iomanip>
#include <ctime>
#include <iostream>

namespace logger {

void log(const std::string &s) {
    time_t t = std::time(nullptr);
    tm tm = *std::localtime(&t);
    std::cerr << std::put_time(&tm, "%d-%m-%Y %H-%M-%S") << ": " << s << std::endl;
}

} // logger