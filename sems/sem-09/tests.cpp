#include "lib.h"
#include "gtest/gtest.h"

#include <algorithm>
#include <string>
#include <cctype>


TEST(TestPC, DISABLED_test_simple) {
    TokenPC pc;
    pc.produce("hello");
    ASSERT_EQ(pc.consume(), "hello1");
}






























// class TestWithFunction : public ::testing::Test {
// protected:
//     void SetUp() {
//         pc_.produce("Sample_String");
//     }

//     void TearDown() {
//         ASSERT_EQ(pc_.size(), 0);
//     }

// protected:
//     TokenPC pc_;
// };

// TEST_F(TestWithFunction, upper_case) {
//     pc_.set_transform([](std::string token) {
//         std::transform(token.begin(), token.end(), token.begin(), [](char c) {
//             return std::toupper(c);
//         });
//         return token;
//     });

//     ASSERT_EQ(pc_.consume(), "SAMPLE_STRING");
// }

// class TestUpperFixture :public ::testing::TestWithParam<std::string> {
// protected:
//     TestUpperFixture() {
//         pc_.set_transform([](std::string token) {
//             std::transform(token.begin(), token.end(), token.begin(), [](char c) {
//                 return std::toupper(c);
//             });
//             return token;
//         });
//     }

// protected:
//     TokenPC pc_;
// };


// TEST_P(TestUpperFixture, different_tokens) {
//     std::string token = GetParam();
//     pc_.produce(token);

//     std::transform(token.begin(), token.end(), token.begin(), [](char c) {
//         return std::toupper(c);
//     });

//     ASSERT_EQ(pc_.consume(), token);
// }

// INSTANTIATE_TEST_SUITE_P(UpperTests,TestUpperFixture,
//     ::testing::Values(
//         "hello_world", "sample_string", "NuMs145"
//     )
// );
