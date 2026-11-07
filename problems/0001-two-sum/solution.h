#pragma once

#include <unordered_map>
#include <vector>

// LeetCode 1. Two Sum
// Returns the indices of the two elements of `nums` that add up to `target`.
// Exactly one answer exists; the same element may not be used twice.

// Approach 1: brute force, check every pair.
// Time: O(n^2) - every pair once.
// Space: O(1).
inline std::vector<int> twoSumBruteForce(const std::vector<int>& nums, int target) {
    for (std::size_t i = 0; i < nums.size() ; i++) {
        for (std::size_t j = i+1; j < nums.size(); j++) {
            if (nums[i] + nums[j] == target) {
                return {static_cast<int>(i),static_cast<int>(j)};
            }
        }
    }
    return {};
}

// Approach 2: one pass with a value -> index hash map.
// Time: O(n) - one pass, O(1) average map operations.
// Space: O(n) - the map can hold every value.
inline std::vector<int> twoSum(const std::vector<int>& nums, int target) {
    std::unordered_map<int, int> seen;
    for (std::size_t i = 0; i < nums.size(); i++) {
        if (auto match = seen.find(target - nums[i]); match != seen.end()) {
            return {match->second, static_cast<int>(i)};
        }
        seen[nums[i]] = static_cast<int>(i);
    }
    return {};
}
