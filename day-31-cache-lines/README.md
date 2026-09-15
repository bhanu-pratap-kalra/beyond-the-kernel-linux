# Beyond the Kernel | Modern C++ & Linux | Day 31 - Cache Lines - The CPU Doesn't Fetch One Variable at a Time

On Day 30, we looked at L1, L2 and L3 caches.

Now comes the detail that makes cache behaviour much more interesting:

**The CPU usually doesn't fetch just the variable you asked for. It fetches a whole cache line.**

On many modern CPUs, a cache line is commonly **64 bytes**.

So if you have:

```cpp
int my_ints[16]; // Assuming int is 4 bytes: 16 * 4 = 64 bytes
```

one cache line can potentially hold all 16 integers.

So when you read:

```cpp
my_ints[0];
```

the CPU may effectively bring something like this into cache:

```text
[0][1][2][3][4][5][6][7][8][9][10][11][12][13][14][15]
<-------------------- one cache line -------------------->
```

That's why this is usually very cache-friendly:

```cpp
for (int my_int : my_ints)
{
    my_sum += my_int;
}
```

You ask for one value, but several upcoming values may already be sitting in cache waiting for you.

## Now Compare That With Pointer Chasing

```text
Node A -> Node B -> Node C -> Node D
```

Each node may live on a completely different cache line.

So instead of:

```text
1 cache line
      ↓
lots of useful data
```

we may get:

```text
many cache lines
      ↓
only a small amount of useful data from each
```

That is one reason why `std::vector` traversal can be dramatically more cache-friendly than `std::list` traversal, even though both traversals are **O(n)**.

Big-O tells us how work grows with input size.

It does not tell us how efficiently the CPU accesses memory.

## Another Example: Object Size

```cpp
struct BigObject
{
    double a, b, c, d;
};
```

Assuming a `double` is 8 bytes, that's roughly:

```text
4 * 8 = 32 bytes
```

A 64-byte cache line could potentially contain two of these objects:

```text
|------ BigObject 1 ------|------ BigObject 2 ------|
<------------------- ~64 bytes ---------------------->
```

But what if the object grows beyond 64 bytes?

Now a single object can span multiple cache lines:

```text
Cache Line 1

[------------- BigObject 1 (partial) ----------------]

Cache Line 2

[BigObject 1 remainder ------------------------------]
```

Accessing one object may now require touching more than one cache line.

So **object size matters too**.

## Remember Day 2?

We already saw the opposite kind of cache-line problem with `alignas()` and false sharing.

Two independent variables accidentally sharing the same cache line can cause different CPU cores to invalidate each other's cached copies.

So cache lines can create two very different performance problems:

```text
Too little useful data per cache line
              ↓
          Cache Waste


Too much unrelated shared data in one cache line
              ↓
         False Sharing
```

## Hot Data vs Cold Data

There's another interesting connection.

Imagine:

```cpp
struct BigObject
{
    int a;          // hot
    char b[512];    // cold
    int c;          // hot
};
```

Suppose your program frequently uses `a` and `c`, but rarely needs `b`.

Processing `a` and `c` may still bring parts of the large cold field into cache even though you don't currently need it.

Sometimes separating hot and cold data can help:

```cpp
struct HotData
{
    int a;
    int c;
};

struct ColdData
{
    char b[512];
};
```

Now frequently accessed data can be packed together more efficiently.

## The Important Mindset

The cache doesn't know which individual bytes you care about.

**It brings the cache line.**

Your data layout determines how much of that cache line is actually useful.

This is where many C++ concepts start connecting:

- `std::vector` vs `std::list`
- contiguous memory
- object size
- `struct` layout
- hot vs cold data
- false sharing
- `alignas()`
- memory pools
- hardware prefetching
- SIMD

Performance is not only about:

> **Which algorithm am I using?**

It is also about:

> **When the CPU fetches a cache line, how much useful work can I get from it?**

Next:

**Spatial vs Temporal Locality** — why nearby data and recently used data have a much better chance of already being where the CPU wants them.

#Cpp #ModernCpp #Linux #SystemsProgramming #CPUCache #CacheLines #PerformanceEngineering #LowLatency
