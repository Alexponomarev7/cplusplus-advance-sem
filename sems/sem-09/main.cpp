#include <iostream>
#include "lib.h"

void read_tokens(TokenPC& pc) {
    std::string token;
    std::cin >> token;
    pc.produce(token);
}

void extract_tokens(TokenPC& pc) {
    std::string token = pc.consume();
    std::cout << token;
}

int main() {
    TokenPC pc;
    read_tokens(pc);
    extract_tokens(pc);

    return 0;
}