#include "problems/0217-contains-duplicate/solution.h"

#include <gtest/gtest.h>

#include <climits>
#include <vector>

// Every test runs against both approaches.
class ContainsDuplicateTest : public ::testing::TestWithParam<bool (*)(const std::vector<int>&)> {};

TEST_P(ContainsDuplicateTest, Examples) {
    auto f = GetParam();
    EXPECT_TRUE(f({1, 2, 3, 1}));
    EXPECT_FALSE(f({1, 2, 3, 4}));
    EXPECT_TRUE(f({1, 1, 1, 3, 3, 4, 3, 2, 4, 2}));
}

TEST_P(ContainsDuplicateTest, SmallestInputs) {
    auto f = GetParam();
    EXPECT_FALSE(f({}));
    EXPECT_FALSE(f({5}));
}

TEST_P(ContainsDuplicateTest, AllSame) {
    EXPECT_TRUE(GetParam()({7, 7, 7}));
}

TEST_P(ContainsDuplicateTest, DuplicateAtFarEnds) {
    EXPECT_TRUE(GetParam()({9, 1, 2, 3, 9}));
}

TEST_P(ContainsDuplicateTest, DuplicateAdjacent) {
    EXPECT_TRUE(GetParam()({1, 2, 2, 3}));
}

TEST_P(ContainsDuplicateTest, NegativesZeroAndExtremes) {
    auto f = GetParam();
    EXPECT_TRUE(f({-1, 0, -1}));
    EXPECT_FALSE(f({INT_MIN, 0, INT_MAX}));
    EXPECT_TRUE(f({INT_MAX, INT_MIN, INT_MAX}));
}

TEST_P(ContainsDuplicateTest, DoesNotModifyInput) {
    const std::vector<int> nums = {3, 1, 2};
    GetParam()(nums);
    EXPECT_EQ(nums, (std::vector<int>{3, 1, 2}));
}

// 100,000 distinct values, then the same values plus one repeat at the very end.
TEST_P(ContainsDuplicateTest, LargeInput) {
    auto f = GetParam();
    std::vector<int> nums;
    for (int i = 0; i < 100000; ++i) nums.push_back(i * 7 - 350000);
    EXPECT_FALSE(f(nums));
    nums.push_back(nums.front());
    EXPECT_TRUE(f(nums));
}

INSTANTIATE_TEST_SUITE_P(HashSet, ContainsDuplicateTest, ::testing::Values(&containsDuplicate));
INSTANTIATE_TEST_SUITE_P(Sorted, ContainsDuplicateTest, ::testing::Values(&containsDuplicateSorted));
