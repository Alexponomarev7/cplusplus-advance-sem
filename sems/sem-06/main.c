#include <stdio.h>

int main() {
    int x;

    char* test = "hello";
    char* test1 = "printf";
    test[1] = 'a';
    printf("%s", test);

    return 0;
}