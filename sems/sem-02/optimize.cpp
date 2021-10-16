#include <iostream>
#include <inttypes.h>

int64_t get_result() {
    int64_t value = 0;

    for (int64_t i = 1; i < 1e9; ++i) {
        value += i;
    }
	return value;
}

int main() {
	std::cout << get_result() << std::endl;

    return 0;
}
