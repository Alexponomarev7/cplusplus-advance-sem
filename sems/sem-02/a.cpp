#include "b.h"

#ifdef TOKEN
    const char * token = TOKEN;
#else
    const char * token = "hello world";
#endif

extern int x;

int main() {
    alert(token);
    return 0;
}
