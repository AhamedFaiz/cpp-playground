# 1. Two Sum

**Source:** [LeetCode 1](https://leetcode.com/problems/two-sum/) · **Difficulty:** Easy · **Pattern:** Hashing (complement lookup)

## Problem

Given an integer array `nums` and an integer `target`, return the **indices** of the two numbers that add up to `target`. Exactly one valid answer exists, and the same element may not be used twice. The indices may be returned in any order.

| `nums` | `target` | Output |
|---|---|---|
| `[2, 7, 11, 15]` | `9` | `[0, 1]` |
| `[3, 2, 4]` | `6` | `[1, 2]` |
| `[3, 3]` | `6` | `[0, 1]` |

## Brute force: O(n²)

Check every pair `(i, j)` with `j > i` (each pair once, since `(i, j)` and `(j, i)` are the same pair).

## Key insight: the inner loop is a search

For a fixed `i`, the inner loop looks for a `j` with

```
nums[i] + nums[j] = target   ⟺   nums[j] = target − nums[i]
```

So it is only **searching for one value**, the *complement* `target − nums[i]`, with an O(n) scan, repeated n times. A hash map answers "have I seen this value, and where?" in O(1) on average.

It must be a **map** (value → index), not a set, because the answer needs the **index** of the earlier element.

## Solution: one pass, check before insert

```cpp
std::unordered_map<int, int> seen;              // value -> index
for (std::size_t i = 0; i < nums.size(); i++) {
    if (auto match = seen.find(target - nums[i]); match != seen.end())
        return {match->second, static_cast<int>(i)};
    seen[nums[i]] = static_cast<int>(i);
}
return {};
```

**Why looking only backwards finds every pair:** every pair has an earlier and a later element. When the loop reaches the later one, the earlier one is already in the map. For `[2, 7, 11, 15]`, target `9`:

| `i` | `nums[i]` | complement | in `seen`? | then |
|---|---|---|---|---|
| 0 | 2 | 7 | no (map empty) | insert `2 → 0` |
| 1 | 7 | 2 | **yes → 0** | return `[0, 1]` |

**Why check *before* insert:** in `[3, 2, 4]` with target `6`, the complement of `3` is `3` itself. Inserting first would find the element's own index and return `[0, 0]`. Checking first means the current element is never in the map when we look it up.

**Lookup with `find`, not `[]`:** `seen[x]` would *insert* a missing key. `find` returns an iterator to the `(value, index)` pair, or `end()` if it's absent.

**Duplicate values:** `[3, 3]` → the second `3` finds the first before it could overwrite it. An overwrite only happens after a failed lookup, and the problem has exactly one answer, so no needed index is ever lost.

**Overflow check:** LeetCode guarantees `nums[i]` and `target` are in `[−10⁹, 10⁹]`, so `target − nums[i]` is at most `2 × 10⁹`, below `INT_MAX ≈ 2.147 × 10⁹`. With wider constraints, the subtraction would need `long long` (signed overflow is undefined behaviour in C++).

## Complexity

| Approach | Time | Extra space |
|---|---|---|
| Brute force | O(n²) | O(1) |
| **One-pass hash map** | **O(n)**: one pass, O(1) average lookups | O(n): up to n entries |

## Edge cases covered by the tests

Both approaches run against every test:

- The same-element trap: `[3, 2, 4]` (target 6) and `[5, 1, 5]` (target 10)
- Duplicate values forming the answer: `[3, 3]`
- Pair at the far ends (first and last)
- Negatives, zero (`[0, 4, 3, 0]`, target 0) and ±10⁹ values
- The input is not modified
- 20,000 elements where the only pair is the first and last element

## Files

- [`solution.h`](solution.h): brute force and one-pass hash map
- [`solution_test.cpp`](solution_test.cpp): parameterised GoogleTest cases
