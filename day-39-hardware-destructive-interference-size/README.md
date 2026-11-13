# Beyond the Kernel | Modern C++ & Linux | Day 39 - `std::hardware_destructive_interference_size`

On Day 38, we looked at **false sharing** and used:

```cpp
struct alignas(64) PerThreadCounterAlign64
{
    std::atomic<int> counter;
};
```

That works as a good mental model.

But one question remains:

> **Why 64?**

Because 64-byte cache lines are common?

That is still an assumption.

C++17 gives us a better way to express the intent:

```cpp
struct alignas(std::hardware_destructive_interference_size)
PerThreadCounterAlignasHDIS
{
    std::atomic<int> counter;
};
```

The idea is simple:

> **Keep independently written objects far enough apart to reduce destructive cache interference.**

## Things Got Interesting on My Own Setup

I checked the values in my environment:

```text
Ubuntu / Docker L1 cache line               → 64
macOS host cache line                       → 128
std::hardware_destructive_interference_size → 256
```

**Three different numbers.**

Why?

Because they are not necessarily describing exactly the same thing.

- **64** → what the Linux guest exposes as its L1 data-cache line size
- **128** → what the macOS host reports as its cache-line size on Apple Silicon
- **256** → the C++ implementation's chosen destructive-interference separation

## Then I Benchmarked It

I compared:

```cpp
alignas(64)
```

against:

```cpp
alignas(std::hardware_destructive_interference_size)
```

which, in this build, effectively became:

```cpp
alignas(256)
```

In my test, **both performed almost the same**.

Why?

Because:

> **More alignment does not automatically mean more performance.**

If 64 bytes is already enough to remove the false-sharing bottleneck for that particular workload, increasing the spacing to 256 bytes does not automatically make the counter update faster.

Conceptually:

```text
alignas(64)
      ↓
enough separation in this test
      ↓
false-sharing bottleneck removed
```

while:

```text
alignas(256)
      ↓
even more separation
      ↓
nothing additional to fix
      ↓
similar performance
```

But this does **not** mean that 64, 128 and 256 are equivalent.

It only tells us that:

> **For this benchmark, the extra separation did not produce an additional performance benefit.**

## Some Fun Facts

- `alignas(256)` may perform the same as `alignas(64)` once false sharing is already removed.
- Similar results with `alignas(64)` do **not** prove false sharing was definitely eliminated.
- If `std::hardware_destructive_interference_size` gives `256` but `128` would be enough, the extra spacing may waste memory.
- Hardcoding `64` is less portable than using `std::hardware_destructive_interference_size`.

## The Important Takeaway

> **`std::hardware_destructive_interference_size` is not a magic performance number.**

It is a better way to express the intent of avoiding destructive interference than simply hardcoding a value such as:

```cpp
alignas(64)
```

And one lesson keeps coming back in performance engineering:

> **Understand the hardware assumption. Then measure the workload.**

Next:

**Day 40 - NUMA Basics**

#Cpp #ModernCpp #Linux #FalseSharing #CPUCache #MemoryAlignment #PerformanceEngineering #LowLatency
