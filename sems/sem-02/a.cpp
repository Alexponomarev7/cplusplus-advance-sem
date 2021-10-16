#include "b.h"
#include <vector>
#include <string_view>
#include <string>
#include <optional>

#ifdef TOKEN
    const char * token = TOKEN;
#else
    const char * token = "hello world";
#endif

int x = 5;

int main() {
    alert(token);
	std::string y = "124";
	std::string_view x = y;

	std::optional<int> n = 5;

	return 0;
}
