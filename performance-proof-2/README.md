# Beyond the Kernel | Modern C++ & Linux | Performance Proof #2 - Cache-Friendly vs Cache-Unfriendly C++

For the last few weeks, we have talked about cache lines, locality, false sharing, data layout and hardware prefetching.

This time, I wanted to stop explaining and simply **measure**.

All tests below were compiled with:

```text
-O2
```

## 1. False Sharing - 100,000 Increments Per Thread

Two threads.

Two independent counters.

Without separation:

```text
Thread 1 → 8,560,500 ns
Thread 2 → 8,555,580 ns
```

With:

```cpp
alignas(64)
```

the result was:

```text
Thread 1 → 1,743,420 ns
Thread 2 → 1,747,670 ns
```

With:

```cpp
std::hardware_destructive_interference_size
```

the result was:

```text
Thread 1 → 1,756,330 ns
Thread 2 → 1,813,080 ns
```

Almost **5× improvement** simply by changing where the counters live in memory.

Same work.

Different cache-line behaviour.

## 2. Hot / Cold Data - 100,000 Elements Touched

The hot loop only needs a small counter.

When that counter lives beside 128 bytes of cold data:

```text
Hot + Cold Together → 644,167 ns
```

After separating the hot fields:

```text
Hot Data Split → 77,417 ns
```

That is roughly **8× faster**.

The CPU is now pulling much more useful data per cache line.

## 3. Array of Structures vs Structure of Arrays - 100,000 Elements Touched

Same logical data.

The benchmark only reads two variables.

```text
Array of Structures  → 778,583 ns
Structure of Arrays →  58,750 ns
```

**SoA was ~13× faster.**

Why?

### Array of Structures

```text
[x y z cold][x y z cold][x y z cold]
```

### Structure of Arrays

```text
[x x x x x ...]
[z z z z z ...]
```

When we only need `x` and `z`, SoA packs the useful data much more densely.

## 4. Sequential vs Strided Access

At around 100K elements:

```text
Sequential → 77,667 ns
Strided    → 80,791 ns
```

Almost no difference.

But increasing the working set changed the picture.

At:

```text
10,000,384 elements
```

the result became:

```text
Sequential →  7,247,500 ns
Strided    → 13,261,800 ns
```

Sequential access was roughly **2× faster**.

As the working set grew, the difference in locality and access pattern became much more visible.

## The Bigger Picture

Across all of these experiments, the theme is the same:

```text
Same or similar logical work
        ↓
Different memory layout / access pattern
        ↓
Different interaction with the CPU cache
        ↓
Very different runtime
```

The takeaway is simple:

> **Fast C++ is not only about choosing the right algorithm.**

It is also about:

> **Giving the CPU data in a form it can process efficiently.**

The code and benchmarks are now going into my new repo:

**`low-latency-cpp-performance-proofs`**

More performance proofs coming.

#Cpp #ModernCpp #Linux #PerformanceEngineering #CPUCache #LowLatency #FalseSharing #DataOrientedDesign #Benchmarking
