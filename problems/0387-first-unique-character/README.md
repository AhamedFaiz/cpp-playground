# 387. First Unique Character in a String

**Source:** [LeetCode 387](https://leetcode.com/problems/first-unique-character-in-a-string/) · **Difficulty:** Easy · **Pattern:** Hashing / counting

## Problem

Given a string `s` of lowercase English letters, return the **index** of the first character that appears **exactly once**. If there is none, return `-1`.

| Input | Output | Why |
|---|---|---|
| `"leetcode"` | `0` | `l` appears once |
| `"loveleetcode"` | `2` | `l` and `o` repeat; `v` is the first that doesn't |
| `"aabb"` | `-1` | every letter repeats |

## Brute force: O(n²)

For each index `i`, scan the whole string (every `j != i`) for another copy of `s[i]`. The first `i` with no copy is the answer.

It's correct but slow because it **keeps asking the same question**. For a string with 50,000 `a`s, it checks "is `a` repeated?" 50,000 times, scanning up to the whole string each time, even though the answer never changes.

## Key insight

With lowercase letters there are at most **26 different questions** ("is `a` repeated?", "is `b` repeated?", …). Answer each one **once**, up front, by counting every letter. After that, checking any position is a single lookup.

## Solution: two passes

1. **Count:** walk the string once and build `count[letter] = number of occurrences`.
2. **Find:** walk the **string** again from index 0 and return the first `i` with `count[s[i]] == 1`.

The second pass goes over the string, **not the map**: `std::unordered_map` has no order, so only the string can tell us which unique letter comes *first*.

Trace for `"abca"`:

| Pass 1 → `count` | Pass 2 |
|---|---|
| `a: 2, b: 1, c: 1` | `i=0 'a'` → 2 ✗ · `i=1 'b'` → 1 ✓ → return **1** |

```cpp
std::unordered_map<char, int> count;
for (char ch : s) count[ch]++;
for (std::size_t i = 0; i < s.size(); i++)
    if (count[s[i]] == 1) return static_cast<int>(i);
return -1;
```

`count[s[i]]` would insert a missing key, but every character of `s` was already inserted in pass 1, so here it only reads.

## Complexity

| | Brute force | Two-pass counting |
|---|---|---|
| Time | O(n²) | **O(n)**: two linear passes, O(1) average lookups |
| Space | O(1) | **O(1)**: at most 26 keys; O(k) for an alphabet of size k |

On a 100,001-character input (Debug build with sanitizers), the brute force took **~3 minutes**. The two-pass version took **0.08 s**.

## Edge cases covered by the tests

- Empty string → `-1`
- Single character → `0`
- Unique character is the last one → `"aabbc"` → `4`
- Odd repeat counts are still repeats → `"aaab"` → `3`, `"aaa"` → `-1`
- An **earlier** copy makes a later letter non-unique → `"aba"` → `1`
- Long input (100,001 chars) where the unique letter is at the very end

## Variation

Since the alphabet is fixed, a plain array `int count[26]` indexed by `ch - 'a'` can replace the hash map. It has the same Big-O but less overhead (no hashing, no allocation).

## Files

- [`solution.h`](solution.h): the solution
- [`solution_test.cpp`](solution_test.cpp): GoogleTest cases
