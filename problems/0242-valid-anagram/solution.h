#pragma once

#include <algorithm>
#include <string>

// LeetCode 242. Valid Anagram
// Returns true if `t` uses exactly the same letters as `s`, each the same number of times.

// Approach 1: count letters in an int[26] array, +1 for s and -1 for t; anagrams leave every count at 0.
// Time: O(n) - one pass over both strings, then 26 checks.
// Space: O(1) - fixed array of 26 counts.
inline bool isAnagram(const std::string& s, const std::string& t) {
    if (s.size() != t.size()) return false;
    int count[26] = {0};
    for (std::size_t i = 0; i < s.size(); i++) {
        count[s[i] - 'a']++;
        count[t[i] - 'a']--;
    }

    for (const int c : count) {
        if (c != 0) {
            return false;
        }
    }
    return true;
}

// Approach 2: sort copies of both strings and compare.
// Time: O(n log n) - dominated by the sorts.
// Space: O(n) - the sorted copies.
inline bool isAnagramSorted(const std::string& s,const std::string& t) {
    if (s.size() != t.size()) return false;
    std::string s_sorted = s;
    std::string t_sorted = t;
    std::sort(s_sorted.begin(), s_sorted.end());
    std::sort(t_sorted.begin(), t_sorted.end());

    return s_sorted == t_sorted;
}
