# 217. Contains Duplicate

**Source:** [LeetCode 217](https://leetcode.com/problems/contains-duplicate/) · **Difficulty:** Easy · **Pattern:** Hashing (seen-set) / sorting

## Problem

Given an integer array `nums`, return `true` if **any value appears at least twice**, and `false` if every element is distinct.

| Input | Output |
|---|---|
| `[1, 2, 3, 1]` | `true` |
| `[1, 2, 3, 4]` | `false` |
| `[1, 1, 1, 3, 3, 4, 3, 2, 4, 2]` | `true` |

## Brute force: O(n²)

Compare every pair `(i, j)` with `j > i`. Checking each pair once is enough because `(i, j)` and `(j, i)` are the same comparison. It needs O(1) extra space but is far too slow for 10⁵ elements.

## Approach 1: hash set

Walk the array, keeping a set of values **seen so far**. If the current value is already in the set, that's a duplicate, so return `true`. Otherwise add it. If the loop finishes, return `false`.

A **set** is enough (rather than a map) because the only question is "have I seen it?". No count or index per value is needed.

Unlike [387](../0387-first-unique-character), "seen so far" works here: the answer is `true` as soon as *any* pair is found, so the rest of the input doesn't matter.

```cpp
std::unordered_set<int> seen;
for (int num : nums) {
    if (seen.count(num)) return true;
    seen.insert(num);
}
return false;
```

## Approach 2: sort, then compare neighbours

After sorting, equal values sit **next to each other**, so a single pass comparing `nums[i]` with `nums[i + 1]` finds any duplicate.

The input is `const`, so the function sorts a **copy**. Sorting the caller's vector would silently reorder their data. The `empty()` check comes first because `size() - 1` on an empty vector wraps around to a huge unsigned value.

## Complexity and trade-offs

| Approach | Time | Extra space | Modifies input? |
|---|---|---|---|
| Brute force | O(n²) | O(1) | no |
| **Hash set** | **O(n)** | O(n): the set can hold every value | no |
| Sort a copy (this solution) | O(n log n) | O(n): the copy | no |
| Sort in place | O(n log n) | O(1)\* | **yes** |

\*Ignoring the sort's own small internal overhead.

- **Hash set:** the default choice. It's the fastest, and it trades memory for speed.
- **Sort in place:** worth it only when memory is tight **and** the input may be modified. Sorting a copy costs O(n) memory anyway, so it has no advantage over the set.

## Edge cases covered by the tests

Both approaches run against every test:

- Empty array and single element → `false`
- All values the same → `true`
- Duplicate at the far ends (first and last) and adjacent
- Negatives, zero, `INT_MIN` / `INT_MAX`
- The caller's vector is not modified
- 100,000 distinct values (`false`), then one repeat appended at the end (`true`)

## Files

- [`solution.h`](solution.h): both approaches
- [`solution_test.cpp`](solution_test.cpp): parameterised GoogleTest cases
