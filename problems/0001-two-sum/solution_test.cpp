#include "problems/0001-two-sum/solution.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

namespace {

using TwoSumFn = std::vector<int> (*)(const std::vector<int>&, int);

// The answer may be returned in any order, so compare sorted copies.
std::vector<int> sorted(std::vector<int> v) {
    std::sort(v.begin(), v.end());
    return v;
}

}  // namespace

class TwoSumTest : public ::testing::TestWithParam<TwoSumFn> {};

TEST_P(TwoSumTest, Examples) {
    auto f = GetParam();
    EXPECT_EQ(sorted(f({2, 7, 11, 15}, 9)), (std::vector<int>{0, 1}));
    EXPECT_EQ(sorted(f({3, 2, 4}, 6)), (std::vector<int>{1, 2}));
    EXPECT_EQ(sorted(f({3, 3}, 6)), (std::vector<int>{0, 1}));
}

TEST_P(TwoSumTest, MustNotUseSameElementTwice) {
    // 5 + 5 = 10, but only via two different 5s.
    EXPECT_EQ(sorted(GetParam()({5, 1, 5}, 10)), (std::vector<int>{0, 2}));
}

TEST_P(TwoSumTest, PairAtFarEnds) {
    EXPECT_EQ(sorted(GetParam()({1, 8, 9, 20, 4}, 5)), (std::vector<int>{0, 4}));
}

TEST_P(TwoSumTest, NegativesAndZero) {
    auto f = GetParam();
    EXPECT_EQ(sorted(f({-3, 4, 3, 90}, 0)), (std::vector<int>{0, 2}));
    EXPECT_EQ(sorted(f({0, 4, 3, 0}, 0)), (std::vector<int>{0, 3}));
    EXPECT_EQ(sorted(f({-1, -2, -3, -4, -5}, -8)), (std::vector<int>{2, 4}));
}

TEST_P(TwoSumTest, LargeValues) {
    EXPECT_EQ(sorted(GetParam()({1000000000, 7, -1000000000}, 0)), (std::vector<int>{0, 2}));
}

TEST_P(TwoSumTest, DoesNotModifyInput) {
    const std::vector<int> nums = {4, 1, 3};
    GetParam()(nums, 7);
    EXPECT_EQ(nums, (std::vector<int>{4, 1, 3}));
}

// 20,000 elements; the only pair is the first and last element.
TEST_P(TwoSumTest, LargeInputPairAtEnds) {
    std::vector<int> nums;
    for (int i = 0; i < 20000; ++i) nums.push_back(i * 2 + 10);  // even values >= 10
    nums.front() = 1;
    nums.back() = 2;
    EXPECT_EQ(sorted(GetParam()(nums, 3)), (std::vector<int>{0, 19999}));
}

INSTANTIATE_TEST_SUITE_P(BruteForce, TwoSumTest, ::testing::Values(&twoSumBruteForce));
INSTANTIATE_TEST_SUITE_P(HashMap, TwoSumTest, ::testing::Values(&twoSum));
