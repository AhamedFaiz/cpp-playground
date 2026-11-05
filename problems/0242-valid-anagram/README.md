# 242. Valid Anagram

**Source:** [LeetCode 242](https://leetcode.com/problems/valid-anagram/) · **Difficulty:** Easy · **Pattern:** Counting (fixed alphabet) / sorting

## Problem

Given two strings `s` and `t` of lowercase English letters, return `true` if `t` is an **anagram** of `s`: the same letters, each used the **same number of times**, in any order.

| `s` | `t` | Output |
|---|---|---|
| `"anagram"` | `"nagaram"` | `true` |
| `"rat"` | `"car"` | `false` |

## Quick rejection

Strings of **different lengths** can never be anagrams. Checking `size()` first rejects them in O(1).

## Two ideas that don't work

| Idea | Counterexample | Why it fails |
|---|---|---|
| For each letter of `s`, check that `t` contains it | `"aab"` vs `"abb"` | Presence isn't enough; **counts** matter. It's also O(n²), since each "contains" scans `t` |
| Count both strings into one map, check every count is even | `"aa"` vs `"bb"` | Even counts don't say **which string** a letter came from |

Both counterexamples are in the tests.

## Approach 1: one counter, +1 for `s` and −1 for `t`

With only 26 letters, a plain array works as the counter. `ch - 'a'` turns a letter into a slot from 0 to 25. Because the lengths are equal, one loop can handle both strings:

```cpp
if (s.size() != t.size()) return false;
int count[26] = {0};
for (std::size_t i = 0; i < s.size(); i++) {
    count[s[i] - 'a']++;
    count[t[i] - 'a']--;
}
for (const int c : count)
    if (c != 0) return false;
return true;
```

If `t` is an anagram, every +1 is cancelled by a −1, so all 26 counts end at **0**.

**Why the array instead of `unordered_map`?** It has the same Big-O, but no hashing and no allocation. A fixed alphabet makes it the natural choice.

**Why checking only the letters of `s` would also be enough:** the counts always sum to `s.size() − t.size() = 0`. If some letter that appears only in `t` ends at −1, another count must be positive to balance it, and only letters of `s` can go positive, so a check over `s` would still catch it. The array version simply checks all 26 slots.

## Approach 2: sort and compare

Sorting puts each string's letters in a canonical order (`"anagram"` → `"aaagmnr"`), so two strings are anagrams exactly when their **sorted copies are equal**. The inputs are `const`, so the function sorts copies.

## Complexity

| Approach | Time | Extra space |
|---|---|---|
| Presence check (wrong anyway) | O(n²) | O(1) |
| **Counting, `int[26]`** | **O(n)** | **O(1)**: 26 counts, whatever the input size |
| Sort copies and compare | O(n log n): two sorts plus an O(n) comparison | O(n): the copies |

Counting is better on both time and space. Sorting is a reasonable first answer, and it works unchanged for any character set.

**Follow-up (Unicode or arbitrary characters):** the 26-slot array no longer fits. Use an `unordered_map<char32_t, int>` (or similar) with the same +1/−1 logic: still O(n) time, with space O(k) for k distinct characters.

## Edge cases covered by the tests

Both approaches run against every test:

- Different lengths → `false`
- Same letters, different counts (`"aab"`/`"abb"`) and the even-count trap (`"aa"`/`"bb"`)
- Empty strings → `true`; single characters, same and different
- Identical strings and all-same letters
- All 26 letters (exercises every array slot)
- Inputs are not modified
- 50,000-character strings, anagram and non-anagram

## Files

- [`solution.h`](solution.h): both approaches
- [`solution_test.cpp`](solution_test.cpp): parameterised GoogleTest cases
