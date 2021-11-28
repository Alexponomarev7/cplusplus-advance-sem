#include <iostream>
#include <exception>
#include <cstring>

#include "mipt/set/set.h"
#include "mipt/log/log.h"

void handle_search(bool response) {
    if (response) std::cout << "Exists" << std::endl;
    else std::cout << "Not found" << std::endl;
}

void handle_error(bool response) {
    if (response) std::cout << "OK" << std::endl;
    else std::cout << "Failed" << std::endl;
}

void handle_empty(bool response) {
    if (response) std::cout << "Empty" << std::endl;
    else std::cout << "Non-empty" << std::endl;
}

int main(int argc, char** argv) {
    std::string_view journal_path = "./journal";
    auto optlevel = mipt::OptimizeLevel::NONE;

    for (int i = 1; i < argc; ++i) {
        if (!strcmp(argv[i], "-v")) {
            set_loglevel(InfoLevel::VERBOSE);
        } else if (!strcmp(argv[i], "--path") || !strcmp(argv[i], "-p")) {
            if (i + 1 == argc) {
                std::cerr << "Error while parsing command-line options...\nStop" << std::endl;
                return -1;
            }
            i++;

            journal_path = argv[i];
        } else if (!strcmp(argv[i], "-O")) {
            optlevel = mipt::OptimizeLevel::STRONG;
        } else {
            std::cerr << "Undefined command-line option" << std::endl;
            return -1;
        }
    }

    mipt::FlatSet<int> set("./journal", optlevel);

    std::string query;
    int key;
    while (std::cin >> query) {
        if (query == "?") {
            std::cin >> key;
            handle_search(set.exists(key));
        } else if (query == "+") {
            std::cin >> key;
            handle_error(set.insert(key));
        } else if (query == "-") {
            std::cin >> key;
            handle_error(set.erase(key));
        } else if (query == "size") {
            std::cout << set.size() << std::endl;
        } else if (query == "empty") {
            handle_empty(set.is_empty());
        } else if (query == "exit") {
            std::cout << "Bye" << std::endl;
            return 0;
        } else {
            throw std::runtime_error("unknown instruction");
        }
    }

    return 0;
}