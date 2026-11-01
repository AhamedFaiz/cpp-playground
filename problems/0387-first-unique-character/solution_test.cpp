#include "problems/0387-first-unique-character/solution.h"

#include <gtest/gtest.h>

#include <string>

TEST(FirstUniqChar, Examples) {
    EXPECT_EQ(firstUniqChar("leetcode"), 0);
    EXPECT_EQ(firstUniqChar("loveleetcode"), 2);
    EXPECT_EQ(firstUniqChar("aabb"), -1);
    
}

TEST(FirstUniqChar, SingleCharacter) {
    EXPECT_EQ(firstUniqChar("z"), 0);
}

TEST(FirstUniqChar, EmptyString) {
    EXPECT_EQ(firstUniqChar(""), -1);
}

TEST(FirstUniqChar, UniqueCharIsLast) {
    EXPECT_EQ(firstUniqChar("aabbc"), 4);
}

TEST(FirstUniqChar, OddRepeatCountsAreNotUnique) {
    EXPECT_EQ(firstUniqChar("aaab"), 3);
    EXPECT_EQ(firstUniqChar("aaa"), -1);
}

TEST(FirstUniqChar, EarlierCopyMakesLaterCharNotUnique) {
    EXPECT_EQ(firstUniqChar("aba"), 1);
    EXPECT_EQ(firstUniqChar("abcab"), 2);
}

// 100,001 characters; the unique 'q' is at the very end.
TEST(FirstUniqChar, LongInput) {
    std::string s(50000, 'b');
    s += std::string(50000, 'a');
    s += 'q';
    EXPECT_EQ(firstUniqChar(s), 100000);
}
