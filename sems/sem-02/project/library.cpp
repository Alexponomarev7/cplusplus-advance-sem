#include <iostream>

#ifdef __OS__
const char* os = __OS__;
#else
const char* os = "undefined";
#endif

void alert() { std::cout << os << std::endl; }
