#pragma once

#include <unordered_set>
#include <algorithm>
#include <vector>

// LeetCode 217. Contains Duplicate
// Returns true if any value appears at least twice in `nums`.

// Approach 1: hash set.
// Time: O(n) - one pass, O(1) average set operations.
// Space: O(n) - the set can hold every value.
inline bool containsDuplicate(const std::vector<int>& nums) {
    std::unordered_set<int> seen;
    for (int num : nums) {
        if (seen.count(num)) {
            return true;
        }
        seen.insert(num);
    }
    return false;
}

// Approach 2: sort, then compare neighbours.
// Time: O(n log n) - dominated by the sort.
// Space: O(n) - sorts a copy so the caller's vector is left untouched.
inline bool containsDuplicateSorted(const std::vector<int>& nums) {
    if (nums.empty()) return false;
    std::vector<int> sortedNums = nums;
    std::sort(sortedNums.begin(), sortedNums.end());
    for (std::size_t i=0; i < sortedNums.size()-1; i++) {
        if (sortedNums[i] == sortedNums[i+1]) {
            return true;
        }
    }
    return false;
}
