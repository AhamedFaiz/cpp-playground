#pragma once

#include <string>
#include <unordered_map>

// LeetCode 387. First Unique Character in a String
// Returns the index of the first character in `s` that appears exactly once, or -1.
// Time: O(n) - two passes over s, O(1) average map operations.
// Space: O(1) - at most 26 keys (O(k) for an alphabet of size k).
inline int firstUniqChar(const std::string& s) {
    std::unordered_map<char, int> count;

    for (char ch : s) {
        count[ch]++;
    }

    for (std::size_t i = 0; i < s.size(); i++) {
        if (count[s[i]] == 1) {
            return static_cast<int>(i);
        }
    }

    return -1;
}
