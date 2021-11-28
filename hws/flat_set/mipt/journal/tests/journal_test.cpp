#include <filesystem>
#include <random>
#include <string>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "mipt/journal/journal.h"

namespace mipt {

fs::path tmp_dir() {
    return fs::temp_directory_path() / "journal_test";
}

// Used logging int stucture
enum TestEntry {
    ADD,
    SUB
};

// Your code goes here...

}