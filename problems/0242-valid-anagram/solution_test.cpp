#include "problems/0242-valid-anagram/solution.h"

#include <gtest/gtest.h>

#include <string>

// Every test runs against both approaches.
class ValidAnagramTest
    : public ::testing::TestWithParam<bool (*)(const std::string&, const std::string&)> {};

TEST_P(ValidAnagramTest, Examples) {
    auto f = GetParam();
    EXPECT_TRUE(f("anagram", "nagaram"));
    EXPECT_FALSE(f("rat", "car"));
}

TEST_P(ValidAnagramTest, DifferentLengths) {
    auto f = GetParam();
    EXPECT_FALSE(f("abc", "ab"));
    EXPECT_FALSE(f("a", "aa"));
}

TEST_P(ValidAnagramTest, SameLettersDifferentCounts) {
    EXPECT_FALSE(GetParam()("aab", "abb"));
}

TEST_P(ValidAnagramTest, AllCountsEvenButDifferentLetters) {
    EXPECT_FALSE(GetParam()("aa", "bb"));
}

TEST_P(ValidAnagramTest, SmallestInputs) {
    auto f = GetParam();
    EXPECT_TRUE(f("", ""));
    EXPECT_TRUE(f("x", "x"));
    EXPECT_FALSE(f("x", "y"));
}

TEST_P(ValidAnagramTest, IdenticalAndAllSame) {
    auto f = GetParam();
    EXPECT_TRUE(f("listen", "listen"));
    EXPECT_TRUE(f("zzzz", "zzzz"));
}

TEST_P(ValidAnagramTest, UsesWholeAlphabet) {
    EXPECT_TRUE(GetParam()("abcdefghijklmnopqrstuvwxyz", "zyxwvutsrqponmlkjihgfedcba"));
}

TEST_P(ValidAnagramTest, DoesNotModifyInputs) {
    const std::string s = "cab";
    const std::string t = "bca";
    GetParam()(s, t);
    EXPECT_EQ(s, "cab");
    EXPECT_EQ(t, "bca");
}

TEST_P(ValidAnagramTest, LargeInput) {
    auto f = GetParam();
    std::string s, t;
    for (int i = 0; i < 50000; ++i) {
        s += static_cast<char>('a' + i % 26);
        t += static_cast<char>('z' - i % 26);
    }
    EXPECT_FALSE(f(s, t));  // 50,000 isn't a multiple of 26, so the counts differ
    std::string u(s.rbegin(), s.rend());
    EXPECT_TRUE(f(s, u));
}

INSTANTIATE_TEST_SUITE_P(Counting, ValidAnagramTest, ::testing::Values(&isAnagram));
INSTANTIATE_TEST_SUITE_P(Sorted, ValidAnagramTest, ::testing::Values(&isAnagramSorted));
