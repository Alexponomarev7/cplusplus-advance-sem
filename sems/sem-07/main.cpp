#include <iostream>
#include <stdint.h>
#include <compare>
#include <vector>
#include <string>

class String {
public:
    // constuctor
    explicit String(char* str) : str_(str)
    {}

    String& operator=(const String& other) & {
        str_ = other.str_;
        return *this;
    }

    char& operator[](size_t index) {
        return str_[index];
    }

    char operator[](size_t index) const {
        return str_[index];
    }

    String& operator+=(const String& other) {
        // this - String*
        // *this - String&
        
        // some code to add other

        return *this;
    }

    int add() {
        return 1;
    }

    // Is ok here?
    // RVO - return value optimization
    // String operator+(const String& other) {
    //     String a(*this); // copy-constructor
    //     a += other;
    //     return a;
    // }

    


private:
    char* str_;
    // const char* m_sStr
};

String operator+(const String& lhs, const String& rhs) {
    String a(lhs); // copy-constructor
    a += rhs;
    return a;
}

String create_string() {
    String s = String("hello"); // Is it RVO?
    return s;
}

struct A {
    int a;
    char b;

    bool operator<(const A& other) const {
        return std::tie(a, b) < std::tie(other.a, other.b);
    }

    bool operator<=(const A& other) const {
        return std::tie(a, b) < std::tie(other.a, other.b);
    }

};


class IntWrapper {
public:
    IntWrapper() = default;
    IntWrapper(const IntWrapper& other) = default;

    IntWrapper& operator++() {
        std::cout << "prefix" << std::endl;
        x_ += 1;
        y_ = 2;
        return *this;
    }

    IntWrapper operator++(int) {
        std::cout << "suffix" << std::endl;

        IntWrapper other(*this);
        x_ += 1;
        y_ = 0;
        return other;
    }



    auto operator<=>(const IntWrapper& other) const = default;



    // auto operator<=>(const IntWrapper& other) const {
    //     if (x_ > other.x_) {
    //         return std::strong_ordering::equal;
    //     }
    //     return std::strong_ordering::greater;
    // }

private:
    int x_ = 0;
    int y_ = 0;
};

int main() {
    IntWrapper x;
    IntWrapper y;

    y++;
    ++x;

    std::cout << ((y <=> x) > 0) << std::endl;

    String a = create_string();
    String b = create_string();

    //(a + b + b) = create_string();

    return 0;
}