#include "lib.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <algorithm>
#include <string>
#include <cctype>
#include <vector>

using testing::Return;

TEST(TestPC, test_simple) {
    TokenPC pc;
    pc.produce("hello");
    ASSERT_EQ(pc.consume(), "hello");
}

class TestWithFunction : public ::testing::Test {
public:
    void SetUp() {
        pc_.produce("Sample_String");
    }

    void TearDown() {
        ASSERT_EQ(pc_.size(), 0);
    }

public:
    TokenPC pc_;
};

TEST_F(TestWithFunction, upper_case) {
    pc_.set_transform([](std::string token) {
        std::transform(token.begin(), token.end(), token.begin(), [](char c) {
            return std::toupper(c);
        });
        return token;
    });

    ASSERT_EQ(pc_.consume(), "SAMPLE_STRING");
}

class TestUpperFixture : public ::testing::TestWithParam<std::string> {
protected:
    TestUpperFixture() {
        pc_.set_transform([](std::string token) {
            std::transform(token.begin(), token.end(), token.begin(), [](char c) {
                return std::toupper(c);
            });
            return token;
        });
    }

protected:
    TokenPC pc_;
};


TEST_P(TestUpperFixture, different_tokens) {
    std::string token = GetParam();
    pc_.produce(token);

    std::transform(token.begin(), token.end(), token.begin(), [](char c) {
        return std::toupper(c);
    });

    ASSERT_EQ(pc_.consume(), token);
}

INSTANTIATE_TEST_SUITE_P(UpperTests, TestUpperFixture,
    ::testing::Values(
        "hello_world", "sample_string", "NuMs145"
    )
);

class MockHeap : public Heap {
public:
    MOCK_METHOD(void, insert, (int x), (override));
    MOCK_METHOD(int, get_max, (), (override));
};

TEST(HeapTests, simple) {
    std::vector<int> ints = {2, 1, 3};
    MockHeap heap;
    EXPECT_CALL(heap, get_max())
        .Times(3)
        .WillOnce(Return(3))
        .WillOnce(Return(2))
        .WillOnce(Return(1));

    EXPECT_CALL(heap, insert(2));
    EXPECT_CALL(heap, insert(1));
    EXPECT_CALL(heap, insert(3));

    auto expected = std::vector<int>{3, 2, 1};
    ASSERT_EQ(heap_sort(ints, heap), expected);
}