#include <gtest/gtest.h>
#include <string>

#include "TokenParser.hpp"

class TestFoo : public ::testing::Test
{
    protected:
        void SetUp() {}
        void TearDown() {}
};


TEST(TokenParserTest, ParseTest) {
    TokenParser parser;
    std::vector<std::string> string_tokens;
    std::vector<uint64_t> digit_tokens;

    parser.SetDigitTokenCallback([&digit_tokens](uint64_t token) {
        digit_tokens.push_back(token);
    });

    parser.SetStringTokenCallback([&string_tokens](const std::string& token) {
        string_tokens.push_back(token);
    });

    parser.Parse("12345 abcdef 4you 1235459852215230223052235626");

    // Check digit tokens
    ASSERT_EQ(digit_tokens.size(), 3);
    EXPECT_EQ(digit_tokens[0], 12345);
    EXPECT_EQ(digit_tokens[1], 12354598522152302230);
    EXPECT_EQ(digit_tokens[2], 52235626);

    // Check string tokens
    ASSERT_EQ(string_tokens.size(), 1);
    EXPECT_EQ(string_tokens[0], "abcdef 4you");
}
TEST(TokenParserTest, SetStartCallbackTest) {
    TokenParser parser;
    std::ostringstream output;

    parser.SetStartCallback([&output]() {
        output << "START\n";
    });

    parser.Parse("12345 abcdef");

    EXPECT_EQ(output.str(), "START\n");
}

TEST(TokenParser, NullCallbacks) {
    TokenParser parser;
    std::string input_str = "123 abc";
    std::stringstream ss(input_str);

    parser.SetStartCallback(nullptr);
    parser.SetEndCallback(nullptr);
    parser.SetDigitTokenCallback(nullptr);
    parser.SetStringTokenCallback(nullptr);

    EXPECT_NO_THROW(parser.Parse(input_str));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
