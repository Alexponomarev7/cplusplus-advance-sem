#include <iostream>
#include <inttypes.h>

int main() {
    int64_t value = 0;

    for (int64_t i = 1; i < 1e9; ++i) {
        value += i;
    }

    std::cout << value << std::endl;

    return 0;
}
