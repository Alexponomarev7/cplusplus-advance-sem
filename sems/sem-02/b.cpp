#include <iostream>

extern int x;

void alert(const char* message) {
    std::cout << "ALERT: " << x << " " << message << '\n';
}
