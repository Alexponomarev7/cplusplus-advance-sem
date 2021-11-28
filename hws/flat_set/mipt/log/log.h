#pragma once

#include <iostream>

enum InfoLevel {
    DEFAULT,
    VERBOSE
};

extern InfoLevel gInfoLevel;

#define INFO() std::cerr << "[INFO] "
#define INFOV() if (gInfoLevel == InfoLevel::VERBOSE) std::cerr << "[INFO_V]"

inline void set_loglevel(InfoLevel level) {
    gInfoLevel = level;
}